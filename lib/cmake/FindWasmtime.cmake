include(FindPackageHandleStandardArgs)

find_path(WASMTIME_INCLUDE_DIR wasmtime.h
          PATHS ENV DEP_WASMTIME_C_API_INCLUDE
          REQUIRED)

find_library(WASMTIME_LIBRARY wasmtime
             REQUIRED)

if(WASMTIME_INCLUDE_DIR AND EXISTS "${WASMTIME_INCLUDE_DIR}/wasmtime.h")
  file(STRINGS ${WASMTIME_INCLUDE_DIR}/wasmtime.h WASMTIME_VERSION REGEX "#define WASMTIME_VERSION")
  string(REGEX MATCH "[0-9]+\.[0-9]\.[0-9]" WASMTIME_VERSION ${WASMTIME_VERSION})
endif()

find_package_handle_standard_args(Wasmtime
  REQUIRED_VARS WASMTIME_INCLUDE_DIR WASMTIME_LIBRARY
  VERSION_VAR WASMTIME_VERSION)

add_library(wasmtime INTERFACE)
target_include_directories(wasmtime SYSTEM BEFORE INTERFACE ${WASMTIME_INCLUDE_DIR})
target_link_libraries(wasmtime INTERFACE ${WASMTIME_LIBRARY})

mark_as_advanced(WASMTIME_INCLUDE_DIR WASMTIME_LIBRARY)
