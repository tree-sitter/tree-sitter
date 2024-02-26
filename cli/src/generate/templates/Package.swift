// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterCAMEL_PARSER_NAME",
    platforms: [.macOS(.v10_13), .iOS(.v11)],
    products: [
        .library(name: "TreeSitterCAMEL_PARSER_NAME", targets: ["TreeSitterCAMEL_PARSER_NAME"]),
    ],
    dependencies: [],
    targets: [
        .target(name: "TreeSitterCAMEL_PARSER_NAME",
                path: ".",
                sources: [
                    "src/parser.c",
                    // NOTE: if your language has an external scanner, add it here.
                ],
                resources: [
                    .copy("queries")
                ],
                publicHeadersPath: "bindings/swift",
                cSettings: [.headerSearchPath("src")])
    ]
)
