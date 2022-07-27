include(ExternalProject)
find_program(TS_CLI NAMES tree-sitter tree-sitter-cli)

set(PARSERS_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/parsers")
function(AddTSParser)
  cmake_parse_arguments(_PARSER
    ""
    ""
    "LANGUAGE;GIT_REPOSITORY;GIT_TAG;GIT_SHALLOW"
    ${ARGN})

  if(NOT _PARSER_GIT_REPOSITORY)
    set(_PARSER_GIT_REPOSITORY "https://github.com/tree-sitter/tree-sitter-${_PARSER_LANGUAGE}.git")
  endif()

  set(NAME tree-sitter-${_PARSER_LANGUAGE})
  ExternalProject_Add(${NAME}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/parsers
    GIT_REPOSITORY ${_PARSER_GIT_REPOSITORY}
    GIT_TAG ${_PARSER_GIT_TAG}
    GIT_SHALLOW ${_PARSER_GIT_SHALLOW}
    PATCH_COMMAND ${TS_CLI} generate
    COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeLists.txt.in ./CMakeLists.txt
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX=${PARSERS_INSTALL_PREFIX}
    UPDATE_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
  )
endfunction()

install(
  DIRECTORY ${PARSERS_INSTALL_PREFIX}/lib/
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/parsers
)

AddTSParser(LANGUAGE c)
AddTSParser(LANGUAGE python)
AddTSParser(LANGUAGE bash)
AddTSParser(LANGUAGE json)
AddTSParser(LANGUAGE html)
AddTSParser(
  LANGUAGE lua
  GIT_REPOSITORY https://github.com/MunifTanjim/tree-sitter-lua
  GIT_TAG main
)
AddTSParser(
  LANGUAGE cmake
  GIT_REPOSITORY https://github.com/uyha/tree-sitter-cmake
)
# AddTSParser(LANGUAGE cpp) # `tree-sitter generate` is failing because tree-sitter-c is required..
