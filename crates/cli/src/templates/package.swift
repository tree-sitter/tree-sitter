// swift-tools-version:5.6

import Foundation
import PackageDescription

let dir = Context.packageDirectory
var sources = ["src/parser.c"]
if FileManager.default.fileExists(atPath: "\(dir)/src/scanner.c") {
    sources.append("src/scanner.c")
}

let package = Package(
    name: "PARSER_CLASS_NAME",
    products: [
        .library(name: "PARSER_CLASS_NAME", targets: ["PARSER_CLASS_NAME"]),
    ],
    dependencies: [
        .package(url: "https://github.com/tree-sitter/swift-tree-sitter", from: "0.10.0"),
    ],
    targets: [
        .target(
            name: "PARSER_CLASS_NAME",
            dependencies: [],
            path: ".",
            sources: sources,
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "PARSER_CLASS_NAMETests",
            dependencies: [
                .product(name: "SwiftTreeSitter", package: "swift-tree-sitter"),
                "PARSER_CLASS_NAME",
            ],
            path: "bindings/swift/PARSER_CLASS_NAMETests"
        )
    ],
    cLanguageStandard: .c11
)
