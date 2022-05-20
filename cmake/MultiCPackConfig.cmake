include("release/CPackConfig.cmake")

set(CPACK_INSTALL_CMAKE_PROJECTS
        "debug;tree-sitter;ALL;/"
        "release;tree-sitter;ALL;/"
)
