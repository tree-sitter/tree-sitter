// swift-tools-version: 5.6
import PackageDescription

let package = Package(
    name: "TreeSitter",
    products: [
        .library(
            name: "TreeSitter",
            targets: ["TreeSitter"]
        ),
    ],
    dependencies: [ ],
    targets: [
        .target(
            name: "TreeSitter",
            dependencies: [],
            path: "lib",
            exclude: [
               "src/lib.c",
               "binding_web",
               "binding_rust",
            ]
        ),
    ]
)

