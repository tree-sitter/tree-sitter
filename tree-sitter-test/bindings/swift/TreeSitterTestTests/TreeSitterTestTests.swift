import XCTest
import SwiftTreeSitter
import TreeSitterTest

final class TreeSitterTestTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_test())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Test grammar")
    }
}
