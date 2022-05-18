get_filename_component(LIBRARY_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
set(LIBRARY_NAME "${PROJECT_NAME}_${LIBRARY_NAME}")

set(Header_Files
        "ptypes.h"
        "umachine.h"
        "urename.h"
        "utf.h"
        "utf16.h"
        "utf8.h"
        )
source_group("Header Files" FILES "${Header_Files}")

add_library("${LIBRARY_NAME}" INTERFACE "${Header_Files}")

target_link_libraries("${LIBRARY_NAME}" PRIVATE "${PROJECT_NAME}_compiler_flags")

include(GNUInstallDirs)
target_include_directories(
        "${LIBRARY_NAME}"
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

#=========#
# Install #
#=========#

install(FILES ${Header_Files} "${_export_file}"
        TYPE "INCLUDE")
