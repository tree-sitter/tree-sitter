package tree_sitter_test_test

import (
	"testing"

	tree_sitter "github.com/smacker/go-tree-sitter"
	"github.com/tree-sitter-grammars/tree-sitter-test"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_test.Language())
	if language == nil {
		t.Errorf("Error loading Test grammar")
	}
}
