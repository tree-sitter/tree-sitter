cmake_minimum_required(VERSION 3.10)
project(
  tree-sitter
  VERSION 0.6.3
  DESCRIPTION "An incremental parsing system for programming tools"
  HOMEPAGE_URL "https://tree-sitter.github.io")

set(TS_SOVERSION_MAJOR 0)
set(TS_SOVERSION_MINOR 0)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(TS_PARSERS_LIST "Build shared libraries" ON)

file(GLOB TS_SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM TS_SRC_FILES "${PROJECT_SOURCE_DIR}/src/lib.c") # skip amalgamation

add_library(tree-sitter ${TS_SRC_FILES})
target_include_directories(tree-sitter PRIVATE ${PROJECT_SOURCE_DIR}/include
                                               ${PROJECT_SOURCE_DIR}/src)
set_target_properties(
  tree-sitter
  PROPERTIES C_STANDARD 99
             C_STANDARD_REQUIRED ON
             POSITION_INDEPENDENT_CODE ON
             SOVERSION ${TS_SOVERSION_MAJOR}.${TS_SOVERSION_MINOR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/share/pkgconfig/tree-sitter.pc.in
               ${CMAKE_CURRENT_BINARY_DIR}/tree-sitter.pc @ONLY)

include(GNUInstallDirs)
install(
  TARGETS tree-sitter
  EXPORT treesitterConfig
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${PROJECT_SOURCE_DIR}/include/tree_sitter/api.h
              ${PROJECT_SOURCE_DIR}/include/tree_sitter/parser.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tree_sitter)
install(EXPORT treesitterConfig
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tree-sitter)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tree-sitter.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(TSParsers)
