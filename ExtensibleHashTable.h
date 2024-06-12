#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include "Bucket.h"
#include <vector>
#include <iostream>
using namespace std;

class ExtensibleHashTable {
private:
    vector<Bucket*> directory;
    int globalDepth;
    int bucketSize;

    int hash(int key) const;
    void splitBucket(int bucketIndex);
    void doubleDirectory();
    void clearDirectory();
    
public:
    ExtensibleHashTable(int bucketSize = 4);
    ExtensibleHashTable(const ExtensibleHashTable& other);
    ExtensibleHashTable& operator=(const ExtensibleHashTable& other);
    ~ExtensibleHashTable();

    bool find(int key) const;
    void insert(int key);
    bool remove(int key);
    void print() const;

    void printCheck() const;
    int getGlobal() const;


};


#endif