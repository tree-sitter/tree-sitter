// swift-tools-version:5.6

import Foundation
import PackageDescription

var sources = ["src/parser.c"]
if FileManager.default.fileExists(atPath: Context.packageDirectory + "/src/scanner.c") {
    sources.append("src/scanner.c")
}

let package = Package(
    name: "PARSER_CLASS_NAME",
    products: [
        .library(name: "PARSER_CLASS_NAME", targets: ["PARSER_CLASS_NAME"]),
    ],
    targets: [
        .target(
            name: "PARSER_CLASS_NAME",
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
                "PARSER_CLASS_NAME",
            ],
            path: "bindings/swift/PARSER_CLASS_NAMETests"
        )
    ],
    cLanguageStandard: .c11
)
