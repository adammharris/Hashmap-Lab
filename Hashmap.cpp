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
  unsigned primeNums[] = {2,3,5,7,11,13};
  for (char& c : key) {
    unsigned currentPrime = primeNums[c % numPrimes];
    hashed += currentPrime * c;
  }
  return hashed % BUCKETS;
}
void Hashmap::insert(string key, int value) {
  Node*& initial = buckets[hash(key)];
  if (initial != nullptr) {
      if (initial->key == key) {
          initial->value = value;
          return;
      }
      Node* currentNode = initial;
      while (currentNode->next != nullptr) {
          if (currentNode->next->key == key) {
              currentNode->next->value = value;
              return;
          }
          currentNode = currentNode->next;
      }
    currentNode->next = new Node();
    currentNode->next->value = value;
    currentNode->next->key = key;
    mapSize++;
    return;
  }
  initial = new Node();
  initial->value = value;
  initial->key = key;
  mapSize++;
  return;
}
bool Hashmap::contains(string key) const {
    Node* currentNode = buckets[hash(key)];
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}
Hashmap::Node* Hashmap::at(const std::string& key) const {
    Node* looper = buckets[hash(key)];
    if (looper == nullptr) {
        throw(std::invalid_argument("No value found for key"));
    }
    while (looper->key != key) {
        looper = looper->next;
        if (looper == nullptr) {
            throw(std::invalid_argument("No value found for key"));
        }
    }
    return looper;
}
int Hashmap::get(string key) const {
  return at(key)->value;
}
int& Hashmap::operator [](string key) {
  return at(key)->value;
}
bool Hashmap::remove(string key) {
  return false;
}
void Hashmap::clear() {
  
}
string Hashmap::toString() const {
  int index = 0;
  Node* currentNode = buckets[index];
  std::stringstream ss;
  if (size() == 0) {
      ss << "[0]" << endl;
    return ss.str();
  }
  while (index != BUCKETS) {
    ss << '[' << index << "]";
    while (currentNode != nullptr) {
        ss << ' ' << currentNode->key << " => " << currentNode->value;
        if (currentNode->next != nullptr) {
            ss << ", ";
        }
        currentNode = currentNode->next;
    }
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