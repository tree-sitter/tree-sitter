def _tree_sitter_configure_impl(ctx):
    """Configures the tree-sitter overlay repository.

    Args:
      ctx: repository_ctx
        Repository context.
        See https://bazel.build/rules/lib/builtins/repository_ctx.
    """
    pwd = ctx.path(Label("@tree-sitter-raw//:WORKSPACE")).dirname
    if ctx.path("{pwd}/Makefile".format(pwd = pwd)).exists:
        root_path = pwd
        path_within_bazel = ctx.path("{pwd}/bazel".format(pwd = pwd))
    else:
        root_path = pwd.dirname
        path_within_bazel = pwd

    ctx.symlink("{root_path}/lib".format(root_path = root_path), "srclib")

    for src, dst in (
        ("build_config", "build_config"),
        ("BUILD.tree-sitter", "BUILD"),
        ("deps.bzl", "deps.bzl"),
        ("lib", "lib"),
        ("repositories.bzl", "repositories.bzl"),
        ("rules.bzl", "rules.bzl"),
    ):
        ctx.symlink("{path_within_bazel}/{src}".format(path_within_bazel = path_within_bazel, src = src), dst)

tree_sitter_configure = repository_rule(
    implementation = _tree_sitter_configure_impl,
    local = True,
    configure = True,
)
