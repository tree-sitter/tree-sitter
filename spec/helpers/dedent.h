#include "compiler/util/string_helpers.h"
#include <string>

static std::string dedent(std::string input) {
  size_t indent_level = input.find_first_not_of("\n ") - input.find_first_not_of("\n");
  std::string whitespace = "\n" + std::string(indent_level, ' ');
  tree_sitter::util::str_replace(&input, whitespace, "\n");
  return input.substr(
    input.find_first_not_of("\n "),
    input.find_last_not_of("\n ") + 1
  );
}
