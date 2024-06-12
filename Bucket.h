#ifndef BUCKET_H
#define BUCKET_H

#include <vector>
using namespace std;

class Bucket {
public:
    Bucket(int bucketSize);

    bool isFull() const;
    bool isEmpty() const;
    bool contains(int key) const;
    void insertKey(int key);
    bool removeKey(int key);
    void clearBucket();
    int getLocalDepth() const;
    int getBucketSize() const;
    void increaseDepth();
    vector<int> getKeys() const;

private:
    vector<int> keys;
    int localDepth;
    int bucketSize;
};


#endif