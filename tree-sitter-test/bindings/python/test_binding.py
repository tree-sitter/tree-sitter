from unittest import TestCase

import tree_sitter as ts
import tree_sitter_test as binding


class TestLanguage(TestCase):
    def setUp(self):
        self.parser = ts.Parser()

    def test_can_load_grammar(self):
        try:
            language = ts.Language(binding.language(), "test")
            self.parser.set_language(language)
        except Exception as exc:
            self.fail(f"Error loading Test grammar: {exc}")
