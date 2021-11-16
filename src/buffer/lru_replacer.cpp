/**
 * LRU implementation
 */
#include "buffer/lru_replacer.h"
#include "page/page.h"

namespace scudb {

template <typename T> void LRUReplacer<T>::add(NodePtr node) {
  if (node == nullptr) {
    return;
  }
  node->prev = nullptr;
  node->next = head;

  if (head != nullptr) {
    head->prev = node;
  }
  head = node;
  if (tail == nullptr) {
    tail = node;
  }
}

template <typename T> void LRUReplacer<T>::remove(NodePtr node) {
  if (head == tail) {
    head = nullptr;
    tail = nullptr;
  } else if (node == head) {
    node->next->prev = nullptr;
    head = node->next;
  } else if (node == tail) {
    node->prev->next = nullptr;
    tail = node->prev;
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
  node->prev = nullptr;
  node->next = nullptr;
}

template <typename T> LRUReplacer<T>::LRUReplacer() = default;

template <typename T> LRUReplacer<T>::~LRUReplacer() = default;

/*
 * Insert value into LRU
 */
template <typename T> void LRUReplacer<T>::Insert(const T &value) {
  std::lock_guard<std::mutex> guard(mutex);

  if (lruMap.count(value)) {
    auto node = lruMap[value];
    remove(node);
    add(node);
  } else {
    auto newNode = std::make_shared<Node>(value);
    lruMap[value] = newNode;
    add(newNode);
  }
}

/* If LRU is non-empty, pop the head member from LRU to argument "value", and
 * return true. If LRU is empty, return false
 */
template <typename T> bool LRUReplacer<T>::Victim(T &value) {
  std::lock_guard<std::mutex> guard(mutex);

  if (Size()) {
    value = tail->val;
    remove(tail);
    lruMap.erase(value);
    return true;
  }
  return false;
}

/*
 * Remove value from LRU. If removal is successful, return true, otherwise
 * return false
 */
template <typename T> bool LRUReplacer<T>::Erase(const T &value) {
  std::lock_guard<std::mutex> guard(mutex);

  if (lruMap.count(value)) {
    auto node = lruMap[value];
    lruMap.erase(value);
    remove(node);
    return true;
  }
  return false;
}

template <typename T> size_t LRUReplacer<T>::Size() { return lruMap.size(); }

template <typename T> std::string LRUReplacer<T>::ToString(bool more) const {
  std::ostringstream stream;
  stream << "lru replacer:  \n";

  NodePtr node = head;
  while (node != nullptr) {
    stream << node->val << " ";
    node = node->next;
  }

  stream << "\n";

  if (more) {
    stream << "unordered_map: \n";

    for (auto [key, val] : lruMap) {
      stream << key << ": " << val << " ";
    }
    stream << "\n";
  }

  return stream.str();
}

// test only
template class LRUReplacer<int>;
template class LRUReplacer<Page *>;

} // namespace scudb
