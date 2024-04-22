load("@tree-sitter//:rules.bzl", map = "in_pkg_srcs")

cc_library(
    name = "utf",
    hdrs = map(["utf.h"]),
)

cc_library(
    name = "ptypes",
    hdrs = map(["ptypes.h"]),
)

cc_library(
    name = "umachine",
    hdrs = map(["umachine.h"]),
)

cc_library(
    name = "urename",
    hdrs = map(["urename.h"]),
)

cc_library(
    name = "utf8",
    hdrs = map(["utf8.h"]),
    visibility = ["@tree-sitter//lib/src:__pkg__"],
    deps = [
        ":umachine",
        ":utf",
    ],
)

cc_library(
    name = "utf16",
    hdrs = map(["utf16.h"]),
    visibility = ["@tree-sitter//lib/src:__pkg__"],
    deps = [
        ":umachine",
        ":utf",
    ],
)
