// The Tree-sitter runtime library can be built by compiling this
// one source file.
//
// The following directories must be added to the include path:
//   - src
//   - include
//   - externals/utf8proc

#include "runtime/get_changed_ranges.c"
#include "runtime/language.c"
#include "runtime/lexer.c"
#include "runtime/node.c"
#include "runtime/parser.c"
#include "runtime/stack.c"
#include "runtime/subtree.c"
#include "runtime/tree_cursor.c"
#include "runtime/tree.c"
#include "runtime/utf16.c"
#include "utf8proc.c"
