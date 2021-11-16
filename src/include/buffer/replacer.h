/**
 * replacer.h
 *
 * Abstract class for replacer, your LRU should implement those methods
 */
#pragma once

#include <cstdlib>
#include <string>
namespace scudb {

template <typename T> class Replacer {
public:
  Replacer() {}
  virtual ~Replacer() {}
  virtual void Insert(const T &value) = 0;
  virtual bool Victim(T &value) = 0;
  virtual bool Erase(const T &value) = 0;
  virtual size_t Size() = 0;
  [[nodiscard]] virtual std::string ToString(bool more) const = 0;
};

} // namespace scudb
