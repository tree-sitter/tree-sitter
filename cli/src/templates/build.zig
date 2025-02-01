const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const shared = b.option(bool, "build-shared", "Build a shared library") orelse true;
    const reuse_alloc = b.option(bool, "reuse-allocator", "Reuse the library allocator") orelse false;

    const lib: *std.Build.Step.Compile = if (shared) b.addSharedLibrary(.{
        .name = "tree-sitter-PARSER_NAME",
        .pic = true,
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    }) else b.addStaticLibrary(.{
        .name = "tree-sitter-PARSER_NAME",
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

    lib.addCSourceFile(.{
        .file = b.path("src/parser.c"),
        .flags = &.{"-std=c11"},
    });
    if (hasScanner(b.build_root.handle)) {
        lib.addCSourceFile(.{
            .file = b.path("src/scanner.c"),
            .flags = &.{"-std=c11"},
        });
    }

    if (reuse_alloc) {
        lib.root_module.addCMacro("TREE_SITTER_REUSE_ALLOCATOR", "");
    }
    if (optimize == .Debug) {
        lib.root_module.addCMacro("TREE_SITTER_DEBUG", "");
    }

    lib.addIncludePath(b.path("src"));

    b.installArtifact(lib);
    b.installFile("src/node-types.json", "node-types.json");
    b.installDirectory(.{ .source_dir = b.path("queries"), .install_dir = .prefix, .install_subdir = "queries", .include_extensions = &.{"scm"} });

    const module = b.addModule("tree-sitter-PARSER_NAME", .{
        .root_source_file = b.path("bindings/zig/root.zig"),
        .target = target,
        .optimize = optimize,
    });
    module.linkLibrary(lib);

    const ts_dep = b.dependency("tree-sitter", .{});
    const ts_mod = ts_dep.module("tree-sitter");
    module.addImport("tree-sitter", ts_mod);

    // ╭─────────────────╮
    // │      Tests      │
    // ╰─────────────────╯

    const tests = b.addTest(.{
        .root_source_file = b.path("bindings/zig/root.zig"),
        .target = target,
        .optimize = optimize,
    });
    tests.linkLibrary(lib);
    tests.root_module.addImport("tree-sitter", ts_mod);

    const run_tests = b.addRunArtifact(tests);

    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_tests.step);
}

inline fn hasScanner(dir: std.fs.Dir) bool {
    dir.access("src/scanner.c", .{}) catch return false;
    return true;
}
