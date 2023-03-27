cmake_minimum_required(VERSION 3.18)
project(tree-sitter LANGUAGES C)

set(CMAKE_C_STANDARD 99)

include_directories(lib/include)

add_library(tree-sitter SHARED
        lib/src/alloc.c
        lib/src/get_changed_ranges.c
        lib/src/language.c
        lib/src/lexer.c
        lib/src/node.c
        lib/src/parser.c
        lib/src/query.c
        lib/src/stack.c
        lib/src/subtree.c
        lib/src/tree_cursor.c
        lib/src/tree.c
        )

# Don't add the `lib` prefix on Windows.
if (WIN32)
    set_target_properties(tree-sitter PROPERTIES PREFIX "")
endif(WIN32)
