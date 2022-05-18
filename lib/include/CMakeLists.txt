set(LIBRARY_NAME "${PROJECT_NAME}")

set(Header_Files "tree_sitter/api.h" "tree_sitter/parser.h")
source_group("Header Files" FILES "${Header_Files}")

add_library("${LIBRARY_NAME}" INTERFACE "${Header_Files}")

target_link_libraries("${LIBRARY_NAME}" INTERFACE "${PROJECT_NAME}_compiler_flags")

include(GNUInstallDirs)
target_include_directories(
        "${LIBRARY_NAME}"
        INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

#=========#
# Install #
#=========#

install(FILES ${Header_Files} TYPE "INCLUDE")
