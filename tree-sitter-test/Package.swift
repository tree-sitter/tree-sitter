// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterTest",
    platforms: [.macOS(.v10_13), .iOS(.v11)],
    products: [
        .library(name: "TreeSitterTest", targets: ["TreeSitterTest"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterTest",
            dependencies: [],
            path: ".",
            exclude: [
                "Cargo.toml",
                "Makefile",
                "binding.gyp",
                "bindings/c",
                "bindings/go",
                "bindings/node",
                "bindings/python",
                "bindings/rust",
                "prebuilds",
                "node_modules",
                "grammar.js",
                "package.json",
                "package-lock.json",
                "pyproject.toml",
                "setup.py",
                "test",
                "examples",
                "ftplugin",
                "ftdetect",
                "plugin",
                ".editorconfig",
                ".github",
                ".gitignore",
                ".gitattributes",
            ],
            sources: [
                "src/parser.c",
                "src/scanner.c"
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterTestTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterTest",
            ],
            path: "bindings/swift/TreeSitterTestTests"
        )
    ],
    cLanguageStandard: .c11
)
