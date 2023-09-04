cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(tree_sitter)

add_library(${PROJECT_NAME} STATIC ${CMAKE_SOURCE_DIR}/src/lib.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
