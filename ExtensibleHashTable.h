#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

class ExtensibleHashTable{

    ExtensibleHashTable();

    ExtensibleHashTable(int key_per_bucket);

    bool find(int key);

    void insert(int key);

    bool remove(int key);

    void print();
};



#endif