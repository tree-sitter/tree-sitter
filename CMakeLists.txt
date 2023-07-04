# To use, run these commands:
# cmake -S ./ -B ./build -G "Ninja Multi-Config" -DCMAKE_BUILD_TYPE=Release
# cmake --build ./build --config Release
# cmake --install ./build --prefix <install-location>

cmake_minimum_required(VERSION 3.20)

include(FetchContent)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

# Add project_options from https://github.com/aminya/project_options
# Change the version in the following URL to update the package
# (watch the releases of the repository for future updates)
set(PROJECT_OPTIONS_VERSION "v0.29.0")
FetchContent_Declare(
  _project_options
  URL https://github.com/aminya/project_options/archive/refs/tags/${PROJECT_OPTIONS_VERSION}.zip
)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# Set the project name and language
project(
  tree-sitter
  LANGUAGES C CXX
  VERSION 0.20.7)

# Initialize project_options variable related to this project This overwrites
# `project_options` and sets `project_warnings` uncomment the options to enable
# them:
project_options(
  PREFIX "tree-sitter"
  ENABLE_CACHE
  # ENABLE_CPPCHECK
  # ENABLE_CLANG_TIDY
  # ENABLE_VS_ANALYSIS
  # ENABLE_GCC_ANALYZER
  # ENABLE_COVERAGE
  # ENABLE_DOXYGEN
  # ENABLE_INTERPROCEDURAL_OPTIMIZATION
  # ENABLE_NATIVE_OPTIMIZATION
  # ENABLE_SANITIZER_ADDRESS
  # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
  # ENABLE_SANITIZER_THREAD
  # ENABLE_SANITIZER_MEMORY
  # ENABLE_CONTROL_FLOW_PROTECTION
  # ENABLE_STACK_PROTECTION
  # ENABLE_OVERFLOW_PROTECTION
  # ENABLE_ELF_PROTECTION
  # ENABLE_RUNTIME_SYMBOLS_RESOLUTION
  # ENABLE_COMPILE_COMMANDS_SYMLINK
  # ENABLE_PCH
  # PCH_HEADERS
  # WARNINGS_AS_ERRORS
  # ENABLE_BUILD_WITH_TIME_TRACE
  # LINKER "lld"
)

add_library(tree_sitter ./lib/src/lib.c)
target_include_directories(tree_sitter PRIVATE ./lib/src)

set(INCLUDE_DIR "./lib/include")
target_include_directories(
  tree_sitter
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}>"
         "$<INSTALL_INTERFACE:./${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(tree_sitter PRIVATE project_options project_warnings)

package_project(PUBLIC_INCLUDES ${INCLUDE_DIR})
