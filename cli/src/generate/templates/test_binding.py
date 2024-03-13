from unittest import TestCase

import tree_sitter, tree_sitter_LOWER_PARSER_NAME


class TestLanguage(TestCase):
    def test_can_load_grammar(self):
        try:
            tree_sitter.Language(tree_sitter_LOWER_PARSER_NAME.language())
        except Exception as exc:
            self.fail(f"Error loading CAMEL_PARSER_NAME grammar: {exc}")
