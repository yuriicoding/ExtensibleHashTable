#include "ExtensibleHashTable.h"
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

void testConstructors() {
    // Test 1: Default construction
    ExtensibleHashTable ht1(4);
    assert(ht1.getGlobal() == 1); // assuming initial global depth starts at 1

    // Test 2: Construction with a specific bucket size
    ExtensibleHashTable ht2(10);
    assert(ht2.getGlobal() == 1);

    // Test 3: Copy constructor
    ht1.insert(1);
    ht1.insert(2);
    ExtensibleHashTable ht3(ht1);
    assert(ht3.find(1) && ht3.find(2));

    std::cout << "Constructor tests passed." << std::endl;
}

void testAssignmentOperator() {
    // Assignment to an empty hash table
    ExtensibleHashTable ht1(2), ht2(2);
    ht1.insert(1);
    ht1.insert(2);
    ht2 = ht1;
    assert(ht2.find(1) && ht2.find(2));

    // Self-assignment
    ht1 = ht1;
    assert(ht1.find(1) && ht1.find(2));

    std::cout << "Assignment operator tests passed." << std::endl;
}

void testInsert() {
    // Insert into an empty hash table
    ExtensibleHashTable ht(4);
    ht.insert(5);
    assert(ht.find(5));

    // Trigger a split
    ht.insert(1);
    ht.insert(3);
    ht.insert(9);
    ht.insert(17); // Assuming this triggers a split
    assert(ht.find(17) && ht.getGlobal() > 1);

    // Multiple directory doublings
    for (int i = 2; i < 100; i += 9) {
        ht.insert(i);
    }
    assert(ht.getGlobal() > 1);

    std::cout << "Insert tests passed." << std::endl;
}

void testFind() {
    ExtensibleHashTable ht(4);
    ht.insert(10);
    assert(ht.find(10));
    assert(!ht.find(11));

    std::cout << "Find tests passed." << std::endl;
}

void testRemove() {
    ExtensibleHashTable ht(4);
    ht.insert(20);
    ht.insert(21);
    assert(ht.remove(20));
    assert(!ht.find(20));
    assert(!ht.remove(100)); // Trying to remove a non-existent key

    std::cout << "Remove tests passed." << std::endl;
}

void testDoubleSplitAndDuplicates() {
    // Test specific for double splits and duplicate handling
    ExtensibleHashTable ht(2);
    ht.insert(3);
    ht.insert(3);
    try
    {
        ht.insert(3); // This should not be allowed more than the bucket size
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    ht.insert(11);
    ht.insert(19); // This should cause double splits

    assert(ht.getGlobal() > 1);
    assert(ht.find(3) && ht.find(11) && ht.find(19));
    assert(ht.remove(3) && !ht.remove(3)); // Removing all 3's

    std::cout << "Double split and duplicate tests passed." << std::endl;
}



int main() {

    testConstructors();
    testAssignmentOperator();
    testInsert();
    testFind();
    testRemove();
    testDoubleSplitAndDuplicates();
    std::cout << "Automatic tests passed." << std::endl;

    cout << endl << "------------------------------------------------------" << endl << endl;

    ExtensibleHashTable hashTable(2);

    //Special test for double split, that happens after 30 is inserted
    hashTable.insert(1);
    hashTable.insert(5);
    hashTable.insert(13);
    hashTable.insert(29);
    hashTable.insert(28);
    hashTable.insert(20);
    hashTable.insert(30);
    cout << "Global depth: " << hashTable.getGlobal() << endl;
    hashTable.print();

    cout << endl << "------------------------------------------------------" << endl << endl;

    //Assignment operator test
    ExtensibleHashTable otherTable(2);
    otherTable = hashTable;

    otherTable.remove(30);
    hashTable.print();
    otherTable.print();

    cout << endl << "------------------------------------------------------" << endl << endl;

    //Copy constructor test
    ExtensibleHashTable anotherTable(hashTable);

    anotherTable.remove(28);
    hashTable.print();
    anotherTable.print();



    return 0;
}
