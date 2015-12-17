#include "tree_sitter/compiler.h"
#include "helpers.h"

namespace tree_sitter_examples {

extern const Grammar anonymous_tokens = Grammar({
  { "program", choice({
    str("\n"),
    str("\r"),
    pattern("\\d"),
    str("\"hello\"") }) },
}).extra_tokens({
  pattern("\\s"),
});

}  // namespace tree_sitter_examples
