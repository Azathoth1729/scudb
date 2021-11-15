#include <list>

#include "hash/extendible_hash.h"
#include "page/page.h"

namespace scudb {

template <typename K, typename V> bool ExtendibleHash<K, V>::Bucket::isFull() {
  return vals.size() == maxSize;
}

template <typename K, typename V> bool ExtendibleHash<K, V>::Bucket::isEmpty() {
  return vals.size() == 0;
}

template <typename K, typename V> int ExtendibleHash<K, V>::Bucket::getDepth() {
  return localDepth;
}

template <typename K, typename V>
bool ExtendibleHash<K, V>::Bucket::find(K key) {
  return vals.find(key) != vals.end();
}

template <typename K, typename V>
bool ExtendibleHash<K, V>::Bucket::remove(K key) {
  if (this->find(key)) {
    vals.erase(key);
    return true;
  } else {
    return false;
  }
}

template <typename K, typename V>
bool ExtendibleHash<K, V>::Bucket::insert(K key, V value) {
  if (isFull()) {
    return false;
  }
  vals[key] = value;
  return true;
}

template <typename K, typename V> void ExtendibleHash<K, V>::Bucket::clear() {
  vals.clear();
}

/*
 * constructor
 * array_size: fixed array bucketSize for each bucket
 */
template <typename K, typename V>
ExtendibleHash<K, V>::ExtendibleHash(size_t bucketSize)
    : globalDepth(1), bucketMaxSize{bucketSize} {
  for (int i = 0; i < 1 << globalDepth; i++) {
    hashTable.push_back(std::make_shared<Bucket>(1, bucketMaxSize));
  }
}

/*
 * helper function to calculate the hashing address of input key
 */
template <typename K, typename V>
size_t ExtendibleHash<K, V>::HashKey(const K &key) const {
  return std::hash<K>{}(key);
}

/*
 * helper function to get the bucketId
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::getHashIndex(const K &key) const {
  return HashKey(key) & ((1 << globalDepth) - 1);
}

/*
 * helper function to return global depth of hash table
 * NOTE: you must implement this function in order to pass test
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetGlobalDepth() const {
  return globalDepth;
}

/*
 * helper function to return local depth of one specific bucket
 * NOTE: you must implement this function in order to pass test
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetLocalDepth(int bucket_id) const {
  return hashTable[bucket_id]->getDepth();
}

template <typename K, typename V> int ExtendibleHash<K, V>::getSize() const {
  return size;
}

/*
 * helper function to return current number of bucket in hash table
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetNumBuckets() const {
  return 1 << globalDepth;
}

/*
 * lookup function to find value associate with input key
 */
template <typename K, typename V>
bool ExtendibleHash<K, V>::Find(const K &key, V &value) {
  std::lock_guard<std::recursive_mutex> guard(mutex);

  int index = getHashIndex(key);
  std::shared_ptr<Bucket> bucket = hashTable[index];

  if (bucket->vals.find(key) != bucket->vals.end()) {
    value = bucket->vals[key];
    return true;
  }
  return false;
}

/*
 * delete <key,value> entry in hash table
 * Shrink & Combination is not required for this project
 */
template <typename K, typename V>
bool ExtendibleHash<K, V>::Remove(const K &key) {
  std::lock_guard<std::recursive_mutex> guard(mutex);

  int index = getHashIndex(key);
  if (hashTable[index]->remove(key)) {
    size--;
    return true;
  }

  return false;
}

template <typename K, typename V> void ExtendibleHash<K, V>::grow() {
  for (int i = 0; i < 1 << globalDepth; i++) {
    hashTable.push_back(hashTable[i]);
  }
  globalDepth++;
}

template <typename K, typename V>
void ExtendibleHash<K, V>::split(const std::shared_ptr<Bucket> &targetBucket) {

  int oldIndex = targetBucket->getDepth();

  // If oldIndex == globalDepth, double the size of hashTable and globalDepth++
  if (oldIndex == globalDepth) {
    grow();
  }
  int maskIndex = 1 << oldIndex;

  auto firstBucket = std::make_shared<Bucket>(oldIndex + 1, bucketMaxSize);
  auto secondBucket = std::make_shared<Bucket>(oldIndex + 1, bucketMaxSize);

  /*
   * After hashTable grow, we need to rehash all vals that belongs to the split
   * bucket, and divided into the two new buckets according to their highest
   * position of their hash values
   */
  for (const auto &item : targetBucket->vals) {
    size_t newIndex = getHashIndex(item.first);
    if (newIndex & maskIndex) {
      firstBucket->vals.insert(item);
    } else {
      secondBucket->vals.insert(item);
    }
  }

  /* Whether hashtable is doubled or not, the two new bucket will be pointed by
   * two hashkey which only differ from the highest position of their hash
   * values
   */
  for (size_t i = 0; i < hashTable.size(); i++) {
    if (hashTable[i] == targetBucket) {
      if (i & maskIndex) {
        hashTable[i] = firstBucket;
      } else {
        hashTable[i] = secondBucket;
      }
    }
  }
}

/*
 * insert <key,value> entry in hash table
 * Split & Redistribute bucket when there is overflow and if necessary increase
 * global depth
 */
template <typename K, typename V>
void ExtendibleHash<K, V>::Insert(const K &key, const V &value) {
  std::lock_guard<std::recursive_mutex> guard(mutex);

  int index = getHashIndex(key);
  auto targetBucket = hashTable[index];
  if (targetBucket->isFull()) {
    split(targetBucket);
    Insert(key, value);
  } else {
    targetBucket->insert(key, value);
    size++;
  }
}

template <typename K, typename V> V ExtendibleHash<K, V>::Get(const K &key) {
  std::lock_guard<std::recursive_mutex> guard(mutex);
  V val;
  Find(key, val);
  return val;
}

template class ExtendibleHash<page_id_t, Page *>;
template class ExtendibleHash<Page *, std::list<Page *>::iterator>;
// test purpose
template class ExtendibleHash<int, std::string>;
template class ExtendibleHash<int, std::list<int>::iterator>;
template class ExtendibleHash<int, int>;
} // namespace scudb
