set(LIBRARY_NAME "tree-sitter")

set(Header_Files
        "alloc.h"
        "array.h"
        "atomic.h"
        "clock.h"
        "error_costs.h"
        "get_changed_ranges.h"
        "host.h"
        "language.h"
        "length.h"
        "lexer.h"
        "point.h"
        "reduce_action.h"
        "reusable_node.h"
        "stack.h"
        "subtree.h"
        "tree.h"
        "tree_cursor.h"
        "unicode.h"
        )
source_group("Header Files" FILES "${Header_Files}")

set(Source_Files
        "alloc.c"
        "get_changed_ranges.c"
        "language.c"
        "lexer.c"
        "lib.c"
        "node.c"
        "parser.c"
        "query.c"
        "stack.c"
        "subtree.c"
        "tree.c"
        "tree_cursor.c"
        )
source_group("Source Files" FILES "${Source_Files}")

add_library("${LIBRARY_NAME}" "${Header_Files}" "${Source_Files}")

target_link_libraries("${LIBRARY_NAME}" PRIVATE "${PROJECT_NAME}" "${PROJECT_NAME}_compiler_flags")

include(GenerateExportHeader)
set(_export_file "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h")
generate_export_header("${LIBRARY_NAME}" EXPORT_FILE_NAME "${_export_file}")

include(GNUInstallDirs)
target_include_directories(
        "${LIBRARY_NAME}"
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if (MSVC)
    target_compile_definitions("${LIBRARY_NAME}" PRIVATE _CRT_SECURE_NO_WARNINGS)
endif (MSVC)

#=========#
# Install #
#=========#

# setup the version numbering
set_property(TARGET "${LIBRARY_NAME}" PROPERTY VERSION "1.0.0")
set_property(TARGET "${LIBRARY_NAME}" PROPERTY SOVERSION "1")

install(FILES ${Header_Files} "${_export_file}"
        TYPE "INCLUDE")

#====================#
# Package to install #
#====================#

set(installable_libs "${PROJECT_NAME}" "${LIBRARY_NAME}" "${PROJECT_NAME}_compiler_flags")
if (TARGET "${DEPENDANT_LIBRARY}")
    list(APPEND installable_libs "${DEPENDANT_LIBRARY}")
endif ()
install(TARGETS ${installable_libs}
        EXPORT "${LIBRARY_NAME}Targets"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(EXPORT "${LIBRARY_NAME}Targets" DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}")
