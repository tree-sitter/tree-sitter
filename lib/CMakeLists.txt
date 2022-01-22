add_library(tree_sitter ./src/lib.c)
target_include_directories(tree_sitter PRIVATE src)
target_include_directories(tree_sitter PUBLIC include)

target_link_libraries(tree_sitter PRIVATE project_options project_warnings)