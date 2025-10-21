import XCTest
import PARSER_CLASS_NAME

final class PARSER_CLASS_NAMETests: XCTestCase {
    func testCanLoadGrammar() throws {
        // just building validates the module creation, and linking validates the binary
        XCTAssertNotNil(tree_sitter_LOWER_PARSER_NAME())
    }
}
