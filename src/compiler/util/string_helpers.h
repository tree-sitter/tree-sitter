#ifndef COMPILER_UTIL_STRING_HELPERS_H_
#define COMPILER_UTIL_STRING_HELPERS_H_

#include <string>
#include <vector>
#include <set>

namespace tree_sitter {
namespace util {

void str_replace(std::string *input, const std::string &search,
                 const std::string &replace);
std::string escape_string(std::string input);
std::string escape_char(uint32_t character);

}  // namespace util
}  // namespace tree_sitter

#endif  // COMPILER_UTIL_STRING_HELPERS_H_
