add_library(tree_sitter ./src/lib.c)
target_include_directories(tree_sitter PRIVATE ./src)

target_include_interface_directories(tree_sitter "./include")
target_link_libraries(tree_sitter PRIVATE tree_sitter_project_options tree_sitter_project_warnings)
