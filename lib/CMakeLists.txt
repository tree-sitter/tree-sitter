cmake_minimum_required(VERSION 3.13)

project(tree-sitter
        VERSION "0.25.0"
        DESCRIPTION "An incremental parsing system for programming tools"
        HOMEPAGE_URL "https://tree-sitter.github.io/tree-sitter/"
        LANGUAGES C)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(TREE_SITTER_FEATURE_WASM "Enable the Wasm feature" OFF)
option(AMALGAMATED "Build using an amalgamated source" OFF)

if(AMALGAMATED)
  set(TS_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/lib.c")
else()
  file(GLOB TS_SOURCE_FILES src/*.c)
  list(REMOVE_ITEM TS_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/lib.c")
endif()

add_library(tree-sitter ${TS_SOURCE_FILES})

target_include_directories(tree-sitter PRIVATE src src/wasm include)

if(NOT MSVC)
  target_compile_options(tree-sitter PRIVATE -Wall -Wextra -Wshadow -Wno-unused-parameter -pedantic)
endif()

if(TREE_SITTER_FEATURE_WASM)
  if(NOT DEFINED CACHE{WASMTIME_INCLUDE_DIR})
    message(CHECK_START "Looking for wasmtime headers")
    find_path(WASMTIME_INCLUDE_DIR wasmtime.h
              PATHS ENV DEP_WASMTIME_C_API_INCLUDE)
    if(NOT WASMTIME_INCLUDE_DIR)
      unset(WASMTIME_INCLUDE_DIR CACHE)
      message(FATAL_ERROR "Could not find wasmtime headers.\nDid you forget to set CMAKE_INCLUDE_PATH?")
    endif()
    message(CHECK_PASS "found")
  endif()

  if(NOT DEFINED CACHE{WASMTIME_LIBRARY})
    message(CHECK_START "Looking for wasmtime library")
    if(BUILD_SHARED_LIBS)
      find_library(WASMTIME_LIBRARY wasmtime)
    elseif(MSVC)
      find_library(WASMTIME_LIBRARY wasmtime.lib)
    else()
      find_library(WASMTIME_LIBRARY libwasmtime.a)
    endif()
    if(NOT WASMTIME_LIBRARY)
      unset(WASMTIME_LIBRARY CACHE)
      message(FATAL_ERROR "Could not find wasmtime library.\nDid you forget to set CMAKE_LIBRARY_PATH?")
    endif()
    message(CHECK_PASS "found")
  endif()

  target_compile_definitions(tree-sitter PUBLIC TREE_SITTER_FEATURE_WASM)
  target_include_directories(tree-sitter SYSTEM PRIVATE "${WASMTIME_INCLUDE_DIR}")
  target_link_libraries(tree-sitter PUBLIC "${WASMTIME_LIBRARY}")
  set_property(TARGET tree-sitter PROPERTY C_STANDARD_REQUIRED ON)

  if(NOT BUILD_SHARED_LIBS)
    if(WIN32)
      target_compile_definitions(tree-sitter PRIVATE WASM_API_EXTERN= WASI_API_EXTERN=)
      target_link_libraries(tree-sitter INTERFACE ws2_32 advapi32 userenv ntdll shell32 ole32 bcrypt)
    elseif(NOT APPLE)
      target_link_libraries(tree-sitter INTERFACE pthread dl m)
    endif()
  endif()
endif()

set_target_properties(tree-sitter
                      PROPERTIES
                      C_STANDARD 11
                      C_VISIBILITY_PRESET hidden
                      POSITION_INDEPENDENT_CODE ON
                      SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
                      DEFINE_SYMBOL "")

target_compile_definitions(tree-sitter PRIVATE _POSIX_C_SOURCE=200112L _DEFAULT_SOURCE)

configure_file(tree-sitter.pc.in "${CMAKE_CURRENT_BINARY_DIR}/tree-sitter.pc" @ONLY)

include(GNUInstallDirs)

install(FILES include/tree_sitter/api.h
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/tree_sitter")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/tree-sitter.pc"
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig")
install(TARGETS tree-sitter
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
