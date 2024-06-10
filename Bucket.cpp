#include "Bucket.h"
#include <algorithm>

Bucket::Bucket(int size) : localDepth(0), bucketSize(size) {}

Bucket::~Bucket() {
    clear();
}

bool Bucket::isFull() const {
    return keys.size() >= bucketSize;
}

bool Bucket::isEmpty() const {
    return keys.empty();
}

bool Bucket::contains(int key) const {
    return std::find(keys.begin(), keys.end(), key) != keys.end();
}

void Bucket::insert(int key) {
    if (!isFull()) {
        keys.push_back(key);
    }
}

bool Bucket::remove(int key) {
    auto it = std::remove(keys.begin(), keys.end(), key);
    bool found = it != keys.end();
    keys.erase(it, keys.end());
    return found;
}

void Bucket::clear() {
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

std::vector<int> Bucket::getKeys() const {
    return keys;
}