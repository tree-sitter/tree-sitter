load("@tree-sitter//:rules.bzl", "use_defines_features", map = "in_pkg_srcs")

cc_library(
    name = "api",
    hdrs = map(["api.h"]),
    defines = use_defines_features(),
    strip_include_prefix = "/srclib/include/",
    visibility = ["//visibility:public"],
)
