_DEFAULT_ROOT_LABEL = Label("@tree-sitter")

def in_srcs(filepaths, root = _DEFAULT_ROOT_LABEL):
    """Maps the input paths to their corresponding paths under the tree-sitter
    source repository.

    Args:
      filepaths: list[str]
        Paths from the root directory of the tree-sitter source repository.
      root: Label
        The tree-sitter source repository name.

    Returns: list[Label]
      The corresponding paths lying under the tree-sitter source repository.
    """
    return [Label("@{root}//:{filepath}".format(root = root.name, filepath = filepath)) for filepath in filepaths]

def in_pkg_srcs(filepaths, root = _DEFAULT_ROOT_LABEL):
    """Maps the input paths to their corresponding paths under the tree-sitter
    source repository by preserving the package directories.

    Acts like `in_srcs`, except that the caller package is used to construct
    the paths that lie under the tree-sitter source repository.

    For example, a rule defined in `lib/src/BUILD.bazel` may use `in_pkg_srcs`
    using the following inputs:
    ```starlark
    load("//:rules.bzl", "in_pkg_srcs")

    cc_library(
        name = "lib",
        srcs = in_pkg_srcs(["lib.c"]),
        hdrs = in_pkg_srcs(["lib.h"]),
    )
    ```

    The rule belongs to the Bazel package `lib/src`, thus `in_pkg_srcs` will
    use that package to build the output path:
      `lib.c` becomes `lib/src/lib.c`
      `lib.h` becomes `lib/src/lib.h`.

    This rule is useful to preserve the original source code layout and split
    definitions across multiple files.

    Args:
      filepaths: list[str]
        Paths from the current package directory of the tree-sitter source repository.
      root: Label
        The tree-sitter source repository name.

    Returns: list[Label]
      The corresponding paths lying under the tree-sitter source repository.
    """
    package_name = native.package_name()
    return in_srcs(["src{package_name}/{filepath}".format(
        package_name = package_name,
        filepath = filepath,
    ) for filepath in filepaths], root)

def use_defines_features():
    """Returns some values for `defines`, depending on enabled features.

    See `@tree-sitter//features` sub-packages for supported features.
    See [`cc_library::defines`](https://bazel.build/reference/be/c-cpp#cc_library.defines).

    Returns: list[str]
      List of defines depending on which features has been enabled.
    """
    return select({
        "@tree-sitter//build_config/hide_symbols:enabled": ["TREE_SITTER_HIDE_SYMBOLS"],
        "//conditions:default": [],
    }) + select({
        "@tree-sitter//build_config/wasm:enabled": ["TREE_SITTER_FEATURE_WASM"],
        "//conditions:default": [],
    })
