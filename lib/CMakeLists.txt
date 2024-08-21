cmake_minimum_required(VERSION 3.13)

project(tree-sitter
        VERSION "0.23.0"
        DESCRIPTION "An incremental parsing system for programming tools"
        HOMEPAGE_URL "https://tree-sitter.github.io/tree-sitter/"
        LANGUAGES C)

if(NOT MSVC)
  set(CMAKE_C_FLAGS "-O3 -Wall -Wextra -Wshadow -Wno-unused-parameter -pedantic")
endif(NOT MSVC)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(TREE_SITTER_FEATURE_WASM "Enable the Wasm feature" OFF)

file(GLOB TS_SOURCE_FILES src/*.c)
list(REMOVE_ITEM TS_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/lib.c")

add_library(tree-sitter ${TS_SOURCE_FILES})

target_include_directories(tree-sitter PRIVATE src src/wasm include)

if(TREE_SITTER_FEATURE_WASM)
  if(NOT DEFINED CACHE{WASMTIME_INCLUDE_DIR})
    message(CHECK_START "Looking for wasmtime headers")
    find_path(WASMTIME_INCLUDE_DIR wasmtime.h
              PATHS ENV DEP_WASMTIME_C_API_INCLUDE
              REQUIRED)
    message(CHECK_PASS "found")
  endif(NOT DEFINED CACHE{WASMTIME_INCLUDE_DIR})

  if(NOT DEFINED CACHE{WASMTIME_LIBRARY})
    message(CHECK_START "Looking for wasmtime library")
    find_library(WASMTIME_LIBRARY wasmtime
                 REQUIRED)
    message(CHECK_PASS "found")
  endif(NOT DEFINED CACHE{WASMTIME_LIBRARY})

  target_compile_definitions(tree-sitter PUBLIC TREE_SITTER_FEATURE_WASM)
  target_include_directories(tree-sitter SYSTEM PRIVATE "${WASMTIME_INCLUDE_DIR}")
  target_link_libraries(tree-sitter PRIVATE "${WASMTIME_LIBRARY}")
  set_property(TARGET tree-sitter PROPERTY C_STANDARD_REQUIRED ON)
endif(TREE_SITTER_FEATURE_WASM)

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
