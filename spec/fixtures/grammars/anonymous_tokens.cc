#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

extern const Grammar anonymous_tokens{{
  { "program", choice({
    str("\n"),
    str("\r"),
    pattern("\\d"),
    str("\"hello\"") }) },
}, {
  pattern("\\s"),
}, {}};

}  // namespace tree_sitter_examples
