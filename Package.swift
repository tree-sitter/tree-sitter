// swift-tools-version: 5.8
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "TreeSitter",
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "TreeSitter",
            targets: ["TreeSitter"]),
    ],
    targets: [
        .target(name: "TreeSitter",
                path: "lib",
                exclude: [
                    "binding_rust",
                    "binding_web",
                    "node_modules",
                    "Cargo.toml",
                    "README.md",
                    "src/unicode/README.md",
                    "src/unicode/LICENSE",
                    "src/unicode/ICU_SHA",
                    "src/get_changed_ranges.c",
                    "src/tree_cursor.c",
                    "src/stack.c",
                    "src/node.c",
                    "src/lexer.c",
                    "src/parser.c",
                    "src/language.c",
                    "src/alloc.c",
                    "src/subtree.c",
                    "src/tree.c",
                    "src/query.c"
                ],
                sources: ["src/lib.c"]),
    ],
    cLanguageStandard: .c11
)
