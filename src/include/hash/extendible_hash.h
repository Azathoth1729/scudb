/*
 * extendible_hash.h : implementation of in-memory hash table using extendible
 * hashing
 *
 * Functionality: The buffer pool manager must maintain a page table to be able
 * to quickly map a PageId to its corresponding memory location; or alternately
 * report that the PageId does not match any currently-buffered page.
 */

#pragma once

#include <cstdlib>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "hash/hash_table.h"

namespace scudb {

template <typename K, typename V>
class ExtendibleHash : public HashTable<K, V> {
  class Bucket {
    int localDepth;
    size_t maxSize{};

  public:
    std::map<K, V> vals;
    // constructor
    explicit Bucket(int d, int s) : localDepth(d), maxSize(s){};

    bool find(K key);
    bool remove(K key);
    bool insert(K key, V value);

    bool isFull();
    bool isEmpty();
    int getDepth();
    void clear();
  };

  using Buckets = std::vector<Bucket *>;

public:
  // constructor
  explicit ExtendibleHash(size_t size);
  // helper function to generate hash addressing
  size_t HashKey(const K &key) const;
  // helper function to get global & local depth
  int GetGlobalDepth() const;
  int GetLocalDepth(int bucket_id) const;
  int GetNumBuckets() const;
  // lookup and modifier
  bool Find(const K &key, V &value) override;
  bool Remove(const K &key) override;
  void Insert(const K &key, const V &value) override;

private:
  int globalDepth;
  Buckets hashTable;
  size_t bucketMaxSize;
  std::mutex mutex;

  // When localDepth == globalDepth, double the size of hashTable via directly
  // push_back the same size pointer.
  void grow();
  void split(Bucket *targetBucket);
  int getHashIndex(const K &key) const;
};

} // namespace scudb
