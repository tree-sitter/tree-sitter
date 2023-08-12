add_library(tree_sitter ./src/lib.c)
target_include_directories(tree_sitter PRIVATE ./src)

set(TREE_SITTER_INCLUDE_DIR "./include")
target_include_directories(
  tree_sitter
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${TREE_SITTER_INCLUDE_DIR}>"
         "$<INSTALL_INTERFACE:./${CMAKE_INSTALL_INCLUDEDIR}>")

if(TARGET tree_sitter_project_options)
    target_link_libraries(tree_sitter PRIVATE tree_sitter_project_options tree_sitter_project_warnings)
endif()
