#include "Hashmap.h"
#include <stdexcept>

Hashmap::Hashmap() {
  //Initialize buckets[i] = NULL for each i (0 <= i < BUCKETS)
  for (unsigned i = 0; i < BUCKETS; i++) {
    buckets[i] = nullptr;
  }
  //Initialize size
  mapSize = 0;
}
Hashmap::~Hashmap() {
  
}
unsigned int Hashmap::hash(string key) const {
  unsigned hashed = 0;
  unsigned numPrimes = 6;
  unsigned primeNums[numPrimes] = {2,3,5,7,11,13};
  for (char& c : key) {
    unsigned currentPrime = primeNums[c % numPrimes];
    hashed += currentPrime * c;
  }
  //cout << "Result of key " << key << ": " << hashed%BUCKETS << endl;
  return hashed % BUCKETS;
}
void Hashmap::insert(string key, int value) {
  Node*& currentNode = buckets[hash(key)];
  if (currentNode != nullptr) {
    while (currentNode->next != nullptr) {
      currentNode = currentNode->next;
    }
  } else {
    currentNode = new Node();
    currentNode->value = value;
    currentNode->key = key;
    mapSize++;
    return;
  }
  currentNode->next = new Node();
  currentNode->next->value = value;
  currentNode->next->key = key;
  mapSize++;
  //cout << "inserted " << value << " at key " << key << " in bucket " << hash(key) << endl;
}
bool Hashmap::contains(string key) const {
  return buckets[hash(key)] != nullptr;
}
int Hashmap::get(string key) const {
  Node* currentNode = buckets[hash(key)];
  if (currentNode == nullptr) {
    cout << "invalid for " << key << " at bucket " << hash(key) << endl;
    throw(std::invalid_argument("No value found for key"));
  }
  while (currentNode->key != key) {
    currentNode = currentNode->next;
    if (currentNode == nullptr) {
      throw(std::invalid_argument("No value found for key"));
    }
  }
  return currentNode->value;
}
int& Hashmap::operator [](string key) {
  Node* currentNode = buckets[hash(key)];
  if (currentNode == nullptr) {
    cout << "invalid for " << key << " at bucket " << hash(key) << endl;
    throw(std::invalid_argument("No value found for key"));
  }
  while (currentNode->key != key) {
    currentNode = currentNode->next;
    if (currentNode == nullptr) {
      throw(std::invalid_argument("No value found for key"));
    }
  }
  return currentNode->value;
}
bool Hashmap::remove(string key) {
  return false;
}
void Hashmap::clear() {
  
}
string Hashmap::toString() const {
  int index = 0;
  Node* currentNode = buckets[index];
  stringstream ss("[0]");
  if (size() == 0) {
    return ss.str();
  }
  while (index != size()) {
    ss << '[' << index << "] ";
    do {
      ss << currentNode->key << " => " << currentNode->value;
      if (currentNode->next != nullptr) {
        ss << ", ";
      }
      currentNode = currentNode->next;
    } while (currentNode != nullptr);
    ss << endl;
    index++;
    currentNode = buckets[index];
  }
  return ss.str();
}
int Hashmap::size() const {
  return mapSize;
}
string Hashmap::toSortedString() const {
  return "Not functional";
}