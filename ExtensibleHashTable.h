#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include "Bucket.h"
#include <vector>
#include <iostream>

class ExtensibleHashTable {
public:
    ExtensibleHashTable(int bucketSize = 4);
    ExtensibleHashTable(const ExtensibleHashTable& other);
    ExtensibleHashTable& operator=(const ExtensibleHashTable& other);
    ~ExtensibleHashTable();

    bool find(int key) const;
    void insert(int key);
    bool remove(int key);
    void print() const;
    int getGlobal() const;

private:
    std::vector<Bucket*> directory;
    int globalDepth;
    int bucketSize;

    int hash(int key) const;
    void splitBucket(int bucketIndex);
    void doubleDirectory();
};


#endif