cmake_minimum_required(VERSION 3.13)

project(tree-sitter
        VERSION "0.23.0"
        DESCRIPTION "An incremental parsing system for programming tools"
        HOMEPAGE_URL "https://tree-sitter.github.io/tree-sitter/"
        LANGUAGES C)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(TREE_SITTER_FEATURE_WASM "Enable the Wasm feature" OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_library(tree-sitter src/lib.c)

target_include_directories(tree-sitter PRIVATE src src/wasm include)
if(NOT MSVC)
  target_compile_options(tree-sitter PRIVATE -O3 -Wall -Wextra -Wshadow -Wno-unused-parameter -pedantic)
endif()

if(TREE_SITTER_FEATURE_WASM)
  find_package(Wasmtime)
  target_link_libraries(tree-sitter PRIVATE wasmtime)

  target_compile_definitions(tree-sitter PUBLIC TREE_SITTER_FEATURE_WASM)
  set_target_properties(tree-sitter PROPERTIES C_STANDARD_REQUIRED ON)
endif()

set_target_properties(tree-sitter
                      PROPERTIES
                      C_STANDARD 11
                      C_VISIBILITY_PRESET hidden
                      POSITION_INDEPENDENT_CODE ON
                      SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

configure_file(tree-sitter.pc.in "${CMAKE_CURRENT_BINARY_DIR}/tree-sitter.pc" @ONLY)

include(GNUInstallDirs)

install(FILES include/tree_sitter/api.h
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/tree_sitter")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/tree-sitter.pc"
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig")
install(TARGETS tree-sitter
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
