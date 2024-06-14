#include "ExtensibleHashTable.h"
#include <stdexcept>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

ExtensibleHashTable::ExtensibleHashTable()
    : globalDepth(1), bucketSize(4) {
    directory.resize(2);
    directory[0] = new Bucket(bucketSize);
    directory[1] = new Bucket(bucketSize);

};


ExtensibleHashTable::ExtensibleHashTable(int bucketSize)
    : globalDepth(1), bucketSize(bucketSize) {
    directory.resize(2);
    directory[0] = new Bucket(bucketSize);
    directory[1] = new Bucket(bucketSize);

};



ExtensibleHashTable::~ExtensibleHashTable() {
    clearDirectory();
};



void ExtensibleHashTable::clearDirectory(){
    vector<bool> deleted(directory.size(), false);
    for (size_t i = 0; i < directory.size(); ++i) {
        if (!deleted[i]) {

            for (size_t j = i; j < directory.size(); ++j) {
                if (directory[j] == directory[i]) {
                    deleted[j] = true;
                }
            }
            delete directory[i];
        }
    }
}



ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable& other) {

    directory.resize(other.directory.size(), nullptr);
    globalDepth = other.globalDepth;
    bucketSize = other.bucketSize;

    vector<Bucket*> newBuckets(other.directory.size(), nullptr);


    for (size_t i = 0; i < other.directory.size(); ++i) {
        if (other.directory[i]) {

            bool alreadyCopied = false;
            for (size_t j = 0; j < i; ++j) {
                if (other.directory[i] == other.directory[j] && newBuckets[j] != nullptr) {
                    newBuckets[i] = newBuckets[j];
                    alreadyCopied = true;
                    break;
                }
            }

            if (!alreadyCopied) {
                newBuckets[i] = new Bucket(*other.directory[i]);
            }
        }
        directory[i] = newBuckets[i];
    }
}




ExtensibleHashTable& ExtensibleHashTable::operator=(const ExtensibleHashTable& other) {
    if (this != &other) {

        clearDirectory();
        
        directory.clear();

        directory.resize(other.directory.size(), nullptr);
        globalDepth = other.globalDepth;
        bucketSize = other.bucketSize;

        vector<Bucket*> newBuckets(other.directory.size(), nullptr);


        for (size_t i = 0; i < other.directory.size(); ++i) {
            if (other.directory[i]) {

                bool alreadyCopied = false;
                for (size_t j = 0; j < i; ++j) {
                    if (other.directory[i] == other.directory[j] && newBuckets[j] != nullptr) {
                        newBuckets[i] = newBuckets[j];
                        alreadyCopied = true;
                        break;
                    }
                }
                
                if (!alreadyCopied) {
                    newBuckets[i] = new Bucket(*other.directory[i]);
                }
            }
            directory[i] = newBuckets[i];
        }
    }
    return *this;
}



int ExtensibleHashTable::hash(int key) const {
    return key & ((1 << globalDepth) - 1);
}



void ExtensibleHashTable::insert(int key) {
    int index = hash(key);
    Bucket* targetBucket = directory[index];

    if (targetBucket->calculateOccurence(key) == bucketSize){
        throw runtime_error("Trying to insert number of duplicate keys greater than size of the bucket! Aborting insertion!");
    }
    else{
        if (!targetBucket->isFull()) {
            targetBucket->insertKey(key);
            return;
        }

        if (targetBucket->getLocalDepth() == globalDepth) {
            doubleDirectory();
        }
        splitBucket(index);

        insert(key); //retry insersion recursively
    }  
}



void ExtensibleHashTable::doubleDirectory() {
    int currentSize = directory.size();
    directory.resize(currentSize * 2);
    for (int i = 0; i < currentSize; ++i) {
        directory[currentSize + i] = directory[i];
    }
    ++globalDepth;
}



void ExtensibleHashTable::splitBucket(int index) {

    //splitting directory local depth
    int indexLocalDepth = directory[index]->getLocalDepth();

    //how many bits of index to use, to find first bucket, where split starts
    int localDepthPower = 1 << (indexLocalDepth);
    
    //bucket where split starts
    int startIndex = index & (localDepthPower - 1);

    Bucket* newBucket = new Bucket(bucketSize);

    for (int i = 0; i < indexLocalDepth; ++i){
        newBucket->increaseDepth();
    }

    //increase depth once for current bucket
    directory[index]->increaseDepth();

    directory[startIndex + localDepthPower] = newBucket;

    for (size_t i = startIndex; i < directory.size(); i += localDepthPower * 2) {
        directory[i + localDepthPower] = newBucket;
    }

    vector<int> oldKeys = directory[startIndex]->getKeys();
    directory[startIndex]->clearBucket();

    
    for (size_t i = 0; i < oldKeys.size(); ++i) {
        int key = oldKeys[i];
        int newIndex = hash(key);
        directory[newIndex]->insertKey(key);
    }
}



bool ExtensibleHashTable::find(int key) const {
    int index = hash(key);
    return directory[index]->contains(key);
}



bool ExtensibleHashTable::remove(int key) {
    int index = hash(key);
    return directory[index]->removeKey(key);
}



int ExtensibleHashTable::getGlobal() const{
    return globalDepth;
}



void ExtensibleHashTable::print() const {
    vector<bool> printed(directory.size(), false);
    for (size_t i = 0; i < directory.size(); ++i) {
        if (!printed[i]) {

            cout << i << ": " << directory[i] << " --> [";
            vector<int> keys = directory[i]->getKeys();
            size_t j;
            for (j = 0; j < keys.size(); ++j) {
                if (j > 0) cout << ", ";
                cout << keys[j];
            }

            for (int k = keys.size(); k < bucketSize; ++k) {
                if (k == 0) cout << " - ";
                else cout << ", - ";
            }
            cout << "] (" << directory[i]->getLocalDepth() << ")\n";


            for (size_t j = i; j < directory.size(); ++j) {
                if (directory[j] == directory[i]) {
                    printed[j] = true;
                }
            }
        }
        else {
            cout << i << ": " << directory[i] << " --> \n";
        }
    }
}



void ExtensibleHashTable::printCheck() const {
    vector<bool> printed(directory.size(), false);
    for (size_t i = 0; i < directory.size(); ++i) {
        if (!printed[i]) {

            cout << bitset<8>(i) << ": " << directory[i] << " --> [";
            vector<int> keys = directory[i]->getKeys();
            size_t j;
            for (j = 0; j < keys.size(); ++j) {
                if (j > 0) cout << ", ";
                cout << bitset<8>(keys[j]);
            }

            for (int k = keys.size(); k < bucketSize; ++k) {
                if (k == 0) cout << " - ";
                else cout << ", - ";
            }
            cout << "] (" << directory[i]->getLocalDepth() << ")\n";


            for (size_t j = i; j < directory.size(); ++j) {
                if (directory[j] == directory[i]) {
                    printed[j] = true;
                }
            }
        }
        else {
            cout << bitset<8>(i) << ": " << directory[i] << " --> \n";
        }
    }
}