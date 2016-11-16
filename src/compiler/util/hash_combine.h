#ifndef COMPILER_UTIL_HASH_COMBINE_H_
#define COMPILER_UTIL_HASH_COMBINE_H_

#include <functional>

namespace tree_sitter {
namespace util {

template <class T>
inline void hash_combine(std::size_t *seed, const T &new_value) {
  std::hash<T> hasher;
  *seed ^= hasher(new_value) + 0x9e3779b9 + (*seed << 6) + (*seed >> 2);
}

template <class T>
inline void symmetric_hash_combine(std::size_t *seed, const T &new_value) {
  std::hash<T> hasher;
  *seed ^= hasher(new_value);
}

}  // namespace util
}  // namespace tree_sitter

#endif  // COMPILER_UTIL_HASH_COMBINE_H_
