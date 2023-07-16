const std = @import("std");

pub fn build(b: *std.Build) void {
    var lib = b.addStaticLibrary(.{
        .name = "tree-sitter",
        .target = b.standardTargetOptions(.{}),
        .optimize = b.standardOptimizeOption(.{}),
    });

    lib.linkLibC();
    lib.addCSourceFile("lib/src/lib.c", &.{});
    lib.addIncludePath("lib/include");
    lib.addIncludePath("lib/src");

    b.installArtifact(lib);
}
