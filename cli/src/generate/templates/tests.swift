import XCTest
import SwiftTreeSitter
import TreeSitterCAMEL_PARSER_NAME

final class TreeSitterCAMEL_PARSER_NAMETests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_LOWER_PARSER_NAME())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading CAMEL_PARSER_NAME grammar")
    }
}
