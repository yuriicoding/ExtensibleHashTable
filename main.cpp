#include "ExtensibleHashTable.h"
#include <iostream>

#include "ExtensibleHashTable.h"
#include <iostream>
#include <vector>

int main() {
    ExtensibleHashTable hashTable(4);  // Initialize with bucket size of 4

    // Test Insertions
    std::cout << "Inserting values..." << std::endl;
    for (int i = 0; i < 20; ++i) {
        hashTable.insert(i * 5);
    }

    // Print current state of the hash table
    hashTable.print();
    std::cout << "----------------------------------------" << std::endl;

    // Test Find
    std::cout << "Testing find operation:" << std::endl;
    std::vector<int> testKeys = {0, 5, 30, 95, 100};  // 100 should not be found
    for (int key : testKeys) {
        std::cout << "Finding " << key << ": " << (hashTable.find(key) ? "Found" : "Not Found") << std::endl;
    }

    // Test Removals
    std::cout << "Testing remove operation:" << std::endl;
    std::vector<int> removeKeys = {0, 25, 95, 100};  // Remove a mix of existing and non-existing keys
    for (int key : removeKeys) {
        std::cout << "Removing " << key << ": " << (hashTable.remove(key) ? "Removed" : "Not Found") << std::endl;
    }

    // Print state after removals
    hashTable.print();
    std::cout << "----------------------------------------" << std::endl;

    // Test inserting after removals to see if freed space is reused
    std::cout << "Inserting 101 and 102..." << std::endl;
    hashTable.insert(101);
    hashTable.insert(102);
    hashTable.print();

    // Edge Case Testing
    std::cout << "Edge cases testing:" << std::endl;
    try {
        // Inserting duplicates
        hashTable.insert(10);
        hashTable.insert(10);
        std::cout << "Inserted duplicate 10." << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught runtime error as expected with message: " << e.what() << std::endl;
    }

    hashTable.print();

    return 0;
}
