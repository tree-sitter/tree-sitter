load("@bazel_skylib//rules:common_settings.bzl", "bool_flag")

bool_flag(
    name = "wasm",
    build_setting_default = False,
    visibility = ["//visibility:public"],
)

bool_flag(
    name = "hide_symbols",
    build_setting_default = True,
    visibility = ["//visibility:public"],
)

config_setting(
    name = "implementation_deps_enabled",
    values = {"experimental_cc_implementation_deps": "1"},
    visibility = ["@tree-sitter//:__pkg__"],
)
