#ifndef BUCKET_H
#define BUCKET_H

#include <vector>

class Bucket {
public:
    Bucket(int bucketSize);

    bool isFull() const;
    bool isEmpty() const;
    bool contains(int key) const;
    void insert(int key);
    bool removeKey(int key);
    void clearBucket();
    int getLocalDepth() const;
    void increaseDepth();
    void decreaseDepth();
    std::vector<int> getKeys() const;

private:
    std::vector<int> keys;
    int localDepth;
    int bucketSize;
};


#endif