const std = @import("std");

const cpp_source = [_][]const u8{
    "main.cpp",
    "board.cpp",
    "precompute.cpp",
    "misc.cpp",
    "magic_search.cpp",
    "search.cpp",
    "evaluate.cpp",
    "tests.cpp",
    "uci.cpp",
    "gui/gui.cpp",
    "screen.cpp",
    "book.cpp",
    "opening.cpp",
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "velocity_chess",
        .target = target,
        .optimize = optimize,
    });

    exe.addCSourceFiles(. {
        .root = b.path("src/"),
        .files = &cpp_source,
    });

    exe.installHeadersDirectory(b.path("src/"), "", .{
        .include_extensions = &.{"h"},
    });

    exe.linkLibCpp();

    exe.linkSystemLibrary("sfml-graphics");

    b.installArtifact(exe);
}
