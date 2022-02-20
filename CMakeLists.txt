# To use, run these commands:
# cmake -S ./ -B ./build -G "Ninja Multi-Config" -DCMAKE_BUILD_TYPE=Release 
# cmake --build ./build --config Release
# cmake --install ./build --prefix <install-location>

cmake_minimum_required(VERSION 3.16)

# Add project_options v0.17.0
# https://github.com/cpp-best-practices/project_options
include(FetchContent)
FetchContent_Declare(
  _project_options
  URL https://github.com/cpp-best-practices/project_options/archive/refs/tags/v0.17.0.zip
)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# Set the project name and language
project(tree-sitter LANGUAGES C CXX VERSION 0.20.3)

# Initialize project_options variable related to this project This overwrites
# `project_options` and sets `project_warnings` uncomment the options to enable
# them:
project_options(
      ENABLE_CACHE
      ENABLE_CPPCHECK
      ENABLE_CLANG_TIDY
      # ENABLE_INTERPROCEDURAL_OPTIMIZATION
      # ENABLE_NATIVE_OPTIMIZATION
      # ENABLE_DOXYGEN
      # ENABLE_COVERAGE
      # ENABLE_SANITIZER_ADDRESS
      # ENABLE_SANITIZER_LEAK
      # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
      # ENABLE_SANITIZER_THREAD
      # ENABLE_SANITIZER_MEMORY
      # ENABLE_PCH
      # PCH_HEADERS
      # WARNINGS_AS_ERRORS
      # ENABLE_INCLUDE_WHAT_YOU_USE
      # ENABLE_USER_LINKER
      # ENABLE_BUILD_WITH_TIME_TRACE
      # ENABLE_UNITY
      # ENABLE_CONAN
      # CONAN_OPTIONS
)

add_library(tree_sitter ./lib/src/lib.c)
target_include_directories(tree_sitter PRIVATE ./lib/src)

set(INCLUDE_DIR "./lib/include")
target_include_directories(tree_sitter PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}>"
                                            "$<INSTALL_INTERFACE:./${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(tree_sitter PRIVATE project_options project_warnings)


package_project(PUBLIC_INCLUDES ${INCLUDE_DIR})