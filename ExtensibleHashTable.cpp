#include "ExtensibleHashTable.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <bitset>
#include <algorithm>
using namespace std;

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
    bucketSize = other.bucketSize;
    globalDepth = other.globalDepth;
    directory.resize(other.directory.size());
    for (size_t i = 0; i < directory.size(); ++i) {
        directory[i] = new Bucket(*other.directory[i]);
    }
};



ExtensibleHashTable& ExtensibleHashTable::operator=(const ExtensibleHashTable& other) {
    if (this != &other) {

        clearDirectory();
        
        directory.clear();

        bucketSize = other.bucketSize;
        globalDepth = other.globalDepth;
        directory.resize(other.directory.size());
        for (size_t i = 0; i < directory.size(); ++i) {
            directory[i] = new Bucket(*other.directory[i]);
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
    int current_local_depth = directory[index]->getLocalDepth();

    //how many bits of index to use, to find first bucket, where split starts
    int localDepthPower = 1 << (current_local_depth);
    
    //bucket where split starts
    int startIndex = index & (localDepthPower - 1);

    Bucket* newBucket = new Bucket(bucketSize);

    for (int i = 0; i < current_local_depth; ++i){
        newBucket->increaseDepth();
    }

    //increase depth once for current bucket
    directory[index]->increaseDepth();

    directory[startIndex + localDepthPower] = newBucket;

    for (int i = startIndex; i < directory.size(); i += localDepthPower * 2) {
        directory[i + localDepthPower] = newBucket;
    }

    vector<int> oldKeys = directory[startIndex]->getKeys();
    directory[startIndex]->clearBucket();

    for (int key : oldKeys) {
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
            for (size_t j = 0; j < keys.size(); ++j) {
                if (j > 0) cout << ", ";
                cout << keys[j];
            }
            cout << "] (" << directory[i]->getLocalDepth() << ")\n";


            for (size_t j = i; j < directory.size(); ++j) {
                if (directory[j] == directory[i]) {
                    printed[j] = true;
                }
            }
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

            for (size_t k = keys.size(); k < bucketSize; ++k) {
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