#include "ExtensibleHashTable.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

ExtensibleHashTable::ExtensibleHashTable(int bucketSize)
    : globalDepth(1), bucketSize(bucketSize) {
    directory.resize(2);
    directory[0] = new Bucket(bucketSize);
    directory[1] = new Bucket(bucketSize);
    directory[0]->increaseDepth();
    directory[1]->increaseDepth();
}

ExtensibleHashTable::~ExtensibleHashTable() {
    for (auto bucket : directory) {
        delete bucket;
    }
}

ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable& other) {
    bucketSize = other.bucketSize;
    globalDepth = other.globalDepth;
    directory.resize(other.directory.size());
    for (size_t i = 0; i < directory.size(); ++i) {
        directory[i] = new Bucket(*other.directory[i]);
    }
}

ExtensibleHashTable& ExtensibleHashTable::operator=(const ExtensibleHashTable& other) {
    if (this != &other) {
        for (auto bucket : directory) {
            delete bucket;
        }
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
        targetBucket->insert(key);
        return;
    }

    if (targetBucket->getLocalDepth() == globalDepth) {
        doubleDirectory();
    }
    splitBucket(index);
    insert(key); // Retry insertion
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
    int localDepthPower = 1 << directory[index]->getLocalDepth();
    int startIndex = index & (localDepthPower - 1);
    //int splitIndex = startIndex + localDepthPower;

    Bucket* newBucket = new Bucket(bucketSize);
    newBucket->increaseDepth();
    directory[index]->increaseDepth();

    for (int i = startIndex; i < directory.size(); i += localDepthPower * 2) {
        directory[i + localDepthPower] = newBucket;
    }

    std::vector<int> oldKeys = directory[startIndex]->getKeys();
    directory[startIndex]->clear();

    for (int key : oldKeys) {
        int newIndex = hash(key);
        directory[newIndex]->insert(key);
    }
}

bool ExtensibleHashTable::find(int key) const {
    int index = hash(key);
    return directory[index]->contains(key);
}

bool ExtensibleHashTable::remove(int key) {
    int index = hash(key);
    return directory[index]->remove(key);
}

void ExtensibleHashTable::print() const {
    std::vector<bool> printed(directory.size(), false);
    for (size_t i = 0; i < directory.size(); ++i) {
        if (!printed[i]) {
            std::cout << i << ": " << static_cast<void*>(directory[i]) << " --> [";
            std::vector<int> keys = directory[i]->getKeys();
            for (size_t j = 0; j < keys.size(); ++j) {
                if (j > 0) std::cout << ", ";
                std::cout << keys[j];
            }
            std::cout << "] (" << directory[i]->getLocalDepth() << ")\n";
            for (size_t j = i; j < directory.size(); ++j) {
                if (directory[j] == directory[i]) {
                    printed[j] = true;
                }
            }
        }
    }
}