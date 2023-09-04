cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(tree_sitter)

set(TREE_SITTER_LIB ${CMAKE_SOURCE_DIR}/lib)

include_directories(${TREE_SITTER_LIB}/include ${CMAKE_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} STATIC ${TREE_SITTER_LIB}/src/lib.c)
