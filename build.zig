const std = @import("std");

pub fn build(b: *std.Build) void {
    var lib = b.addStaticLibrary(.{
        .name = "tree-sitter",
        .target = b.standardTargetOptions(.{}),
        .optimize = b.standardOptimizeOption(.{}),
    });

    lib.linkLibC();
    lib.addCSourceFile(.{ .file = b.path("lib/src/lib.c"), .flags = &.{"-std=c11"} });
    lib.addIncludePath(b.path("lib/include"));
    lib.addIncludePath(b.path("lib/src"));

    lib.installHeadersDirectory(b.path("lib/include"), ".", .{});

    b.installArtifact(lib);
}
