#ifndef COMPILER_UTIL_RESULT_H_
#define COMPILER_UTIL_RESULT_H_

#include <string>

namespace tree_sitter {
namespace util {

template <typename Value>
struct Result {
  Value value;
  std::string error;

  inline Result() : error("Empty") {}
  inline Result(const Value &v) : value(v) {}
  inline Result(Value &&v) : value(std::move(v)) {}
  inline Result(const std::string &message) : error(message) {}
  inline Result(const char *message) : error(message) {}
  inline bool ok() const { return error.empty(); }
};

}  // namespace util
}  // namespace tree_sitter

#endif  // COMPILER_UTIL_RESULT_H_
