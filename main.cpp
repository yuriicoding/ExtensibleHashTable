#include "ExtensibleHashTable.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ExtensibleHashTable hashTable(2);  // Initialize with bucket size of 4

    //Special test for double split, that happens after 30 is inserted
    hashTable.insert(1);
    cout << "Global depth: " << hashTable.getGlobal() << endl;
    hashTable.printCheck();
    hashTable.insert(5);
    cout << "Global depth: " << hashTable.getGlobal() << endl;
    hashTable.printCheck();
    hashTable.insert(13);
    cout << "Global depth: " << hashTable.getGlobal() << endl;
    hashTable.printCheck();
    hashTable.insert(29);
    cout << "Global depth: " << hashTable.getGlobal() << endl;
    hashTable.printCheck();
    hashTable.insert(28);
    cout << "Global depth: " << hashTable.getGlobal() << endl;
    hashTable.printCheck();
    hashTable.insert(20);
    cout << "Global depth: " << hashTable.getGlobal() << endl;
    hashTable.printCheck();
    hashTable.insert(30);
    cout << "Global depth: " << hashTable.getGlobal() << endl;
    hashTable.printCheck();


    // Test Insertions
    //cout << "Inserting values..." << endl;
    // for (int i = 0; i < 5; ++i) {
    //     hashTable.insert(i);
    // }
    // // Print current state of the hash table
    // hashTable.print();
    // cout << "----------------------------------------" << endl;

    // // Test Find
    // cout << "Testing find operation:" << endl;
    // vector<int> testKeys = {0, 5, 30, 95, 100};  // 100 should not be found
    // for (int key : testKeys) {
    //     cout << "Finding " << key << ": " << (hashTable.find(key) ? "Found" : "Not Found") << endl;
    // }

    // // Test Removals
    // cout << "Testing remove operation:" << endl;
    // vector<int> removeKeys = {0, 25, 95, 100};  // Remove a mix of existing and non-existing keys
    // for (int key : removeKeys) {
    //     cout << "Removing " << key << ": " << (hashTable.remove(key) ? "Removed" : "Not Found") << endl;
    // }

    // // Print state after removals
    // hashTable.print();
    // cout << "----------------------------------------" << endl;

    // // Test inserting after removals to see if freed space is reused
    // cout << "Inserting 101 and 102..." << endl;
    // cout << "Global depth: " << hashTable.getGlobal() << endl;
    // cout << "----------------------------------------" << endl;
    // hashTable.insert(101);
    // cout << "Global depth: " << hashTable.getGlobal() << endl;
    // hashTable.print();
    // cout << "----------------------------------------" << endl;
    // hashTable.insert(102);
    // cout << "Global depth: " << hashTable.getGlobal() << endl;
    // hashTable.print();
    // cout << "----------------------------------------" << endl;

    // // Edge Case Testing
    // cout << "Edge cases testing:" << endl;
    // try {
    //     // Inserting duplicates
    //     hashTable.insert(10);
    //     hashTable.insert(10);
    //     cout << "Inserted duplicate 10." << endl;
    // } catch (const runtime_error& e) {
    //     cout << "Caught runtime error as expected with message: " << e.what() << endl;
    // }

    // hashTable.printCheck();

    return 0;
}
