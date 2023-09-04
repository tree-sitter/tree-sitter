cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(tree_sitter)

add_library(${PROJECT_NAME} STATIC src/lib.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)
