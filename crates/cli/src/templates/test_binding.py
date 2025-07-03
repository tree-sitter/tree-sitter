from unittest import TestCase

from tree_sitter import Language, Parser
import tree_sitter_LOWER_PARSER_NAME


class TestLanguage(TestCase):
    def test_can_load_grammar(self):
        language = Language(tree_sitter_LOWER_PARSER_NAME.language())
        _ = Parser(language)
