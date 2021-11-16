/**
 * lru_replacer.h
 *
 * Functionality: The buffer pool manager must maintain a LRU list to collect
 * all the pages that are unpinned and ready to be swapped. The simplest way to
 * implement LRU is a FIFO queue, but remember to dequeue or enqueue pages when
 * a page changes from unpinned to pinned, or vice-versa.
 */

#pragma once

#include "buffer/replacer.h"
#include "hash/extendible_hash.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
namespace scudb {

template <class T> class LRUReplacer : public Replacer<T> {
  friend class BufferPoolManager;

  struct Node {

    T val;
    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> next;

    Node() = default;
    explicit Node(T v) : val(v){};
  };
  using NodePtr = std::shared_ptr<Node>;

public:
  // do not change public interface
  LRUReplacer();

  ~LRUReplacer();

  void Insert(const T &value);

  bool Victim(T &value);

  bool Erase(const T &value);

  size_t Size();

  NodePtr head;
  NodePtr tail;

  [[nodiscard]] std::string ToString(bool more = false) const;

private:
  std::mutex mutex;
  std::unordered_map<T, NodePtr> lruMap;

  // add node as first node of the linked list
  void add(NodePtr node);
  // remove node of the linked list
  void remove(NodePtr node);
};

} // namespace scudb
