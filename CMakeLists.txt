cmake_minimum_required(VERSION 3.18)
project(tree-sitter LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(SONAME_MAJOR 0)
set(SONAME_MINOR 0)

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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
# We don't add `-std=gnu99` here as CMake sets this automatically for GNU-compatible compilers.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

# Don't add the `lib` prefix on Windows.
if(WIN32)
    set_target_properties(tree-sitter PROPERTIES PREFIX "")
endif()

if(APPLE)
    set_target_properties(tree-sitter PROPERTIES SUFFIX ".${SONAME_MAJOR}.${SONAME_MINOR}.dylib")
elseif(UNIX)
    set_target_properties(tree-sitter PROPERTIES SUFFIX ".so.${SONAME_MAJOR}.${SONAME_MINOR}")
endif()
