include("release/CPackConfig.cmake")

set(CPACK_INSTALL_CMAKE_PROJECTS
        "debug;tree_sitter;ALL;/"
        "release;tree_sitter;ALL;/"
)
