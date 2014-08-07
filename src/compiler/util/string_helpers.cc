#include "compiler/util/string_helpers.h"
#include <vector>
#include <stdio.h>

namespace tree_sitter {
namespace util {

using std::string;
using std::vector;
using std::set;

void str_replace(string *input, const string &search, const string &replace) {
  size_t pos = 0;
  while (1) {
    pos = input->find(search, pos);
    if (pos == string::npos)
      break;
    input->erase(pos, search.length());
    input->insert(pos, replace);
    pos += replace.length();
  }
}

string escape_string(string input) {
  str_replace(&input, "\"", "\\\"");
  str_replace(&input, "\n", "\\n");
  return input;
}

string escape_char(char character) {
  switch (character) {
    case '"':
      return "'\\\"'";
    case '\'':
      return "'\\''";
    case '\n':
      return "'\\n'";
    case '\r':
      return "'\\r'";
    case '\t':
      return "'\\t'";
    case '\\':
      return "'\\\\'";
    default:
      if (character >= ' ' && character <= '~') {
        return string("'") + character + "'";
      } else {
        char buffer[5];
        sprintf(buffer, "%d", int(character));
        return string(buffer);
      }
  }
}

}  // namespace util
}  // namespace tree_sitter
