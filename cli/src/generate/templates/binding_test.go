package tree_sitter_PARSER_NAME_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_PARSER_NAME "github.com/tree-sitter/tree-sitter-PARSER_NAME/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_PARSER_NAME.Language())
	if language == nil {
		t.Errorf("Error loading CAMEL_PARSER_NAME grammar")
	}
}
