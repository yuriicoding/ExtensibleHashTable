#include "Bucket.h"
#include <algorithm>
using namespace std;

Bucket::Bucket(int size) : localDepth(1), bucketSize(size) {}

bool Bucket::isFull() const {
    return keys.size() >= bucketSize;
}

bool Bucket::isEmpty() const {
    return keys.empty();
}

bool Bucket::contains(int key) const {
    return find(keys.begin(), keys.end(), key) != keys.end();
}

void Bucket::insert(int key) {
    if (!isFull()) {
        keys.push_back(key);
    }
}

bool Bucket::removeKey(int key) {

    //could use auto!
    vector<int>::iterator it = remove(keys.begin(), keys.end(), key);

    bool found;
    if (it != keys.end()){
        found = true;
    }
    else{
        found = false;
    }
    keys.erase(it, keys.end());

    return found;
}

void Bucket::clearBucket() {
    keys.clear();
}

int Bucket::getLocalDepth() const {
    return localDepth;
}

void Bucket::increaseDepth() {
    ++localDepth;
}

void Bucket::decreaseDepth() {
    if (localDepth > 0) --localDepth;
}

vector<int> Bucket::getKeys() const {
    return keys;
}