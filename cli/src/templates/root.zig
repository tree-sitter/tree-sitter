const testing = @import("std").testing;

const ts = @import("tree-sitter");
const Language = ts.Language;
const Parser = ts.Parser;

pub extern fn tree_sitter_PARSER_NAME() callconv(.C) *const Language;

pub export fn language() *const Language {
    return tree_sitter_PARSER_NAME();
}

test "can load grammar" {
    const parser = Parser.create();
    defer parser.destroy();
    try testing.expectEqual(parser.setLanguage(language()), void{});
    try testing.expectEqual(parser.getLanguage(), tree_sitter_PARSER_NAME());
}

