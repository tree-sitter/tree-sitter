# Configure with: 
# cmake -S ./ -B ./build -G "Ninja Multi-Config" -DCMAKE_BUILD_TYPE=Release
# Build with: 
# cmake --build ./build --config Release

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Add project_options v0.16.0
# https://github.com/cpp-best-practices/project_options
include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/cpp-best-practices/project_options/archive/refs/tags/v0.16.0.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# Set the project name and language
project(tree-sitter LANGUAGES C CXX)

# Initialize project_options variable related to this project
# This overwrites `project_options` and sets `project_warnings`
# uncomment the options to enable them:
project_options(
      ENABLE_CACHE
      ENABLE_CPPCHECK
      ENABLE_CLANG_TIDY
      # WARNINGS_AS_ERRORS
      # ENABLE_IPO
      # ENABLE_USER_LINKER
      # ENABLE_SANITIZER_ADDRESS
      # ENABLE_SANITIZER_LEAK
      # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
      # ENABLE_SANITIZER_THREAD
      # ENABLE_SANITIZER_MEMORY
)

# add lib directory to the project
add_subdirectory(lib)