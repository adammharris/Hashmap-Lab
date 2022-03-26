#include "Hashmap.h"
//#include <stdexcept>

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
Hashmap::Node* Hashmap::pParentOf(const std::string key) const {
    Node* looper = buckets[hash(key)];
    if (looper == nullptr) {
        throw(std::invalid_argument("No value found for key"));
    }
    while (looper->key != key) {
        looper = looper->next;
        if (looper == nullptr) {
            throw(std::invalid_argument("No value found for key"));
        }
        if (looper->next != nullptr) {
            if (looper->next->key == key) {
                return looper;
            }
        }
    }
    return looper;
}
Hashmap::Node* Hashmap::at(const std::string key) const {
    Node* possibleParent = pParentOf(key);
    if (possibleParent->key == key) { // not parent
        return possibleParent;
    } else { // is parent
        return possibleParent->next;
    }
}
int Hashmap::get(string key) const {
  return at(key)->value;
}
int& Hashmap::operator [](string key) {
  try {
      return at(key)->value;
  } catch (std::invalid_argument ia) {
      insert(key, 0);
      return at(key)->value;
  }
}
bool Hashmap::remove(string key) {
    Node* parent;
    try {
        parent = pParentOf(key);
    } catch (std::invalid_argument ia) {
        return false;
    }
    if (parent->key == key) { // Check in case root needs removal
        Node* child = parent->next;
        buckets[hash(key)] = child; // Can I prevent calling hash again?
        mapSize--;
        delete parent;
        return true;
    }
    Node* replace = parent->next->next;
    delete parent->next;
    parent->next = replace;
    mapSize--;
    return true;
}
void Hashmap::clear() {
  for (unsigned i = 0; i < BUCKETS; i++) {
      while (buckets[i] != nullptr) {
          remove(buckets[i]->key);
      }
  }
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