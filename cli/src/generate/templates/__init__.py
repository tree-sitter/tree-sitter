"""CAMEL_PARSER_NAME grammar for tree-sitter"""

from importlib.resources import files as _files

from ._binding import language

# NOTE: uncomment these to include any queries that this grammar contains:

# HIGHLIGHTS_QUERY = _files(f"{__package__}.queries").joinpath("highlights.scm").read_text()
# INJECTIONS_QUERY = _files(f"{__package__}.queries").joinpath("injections.scm").read_text()
# LOCALS_QUERY = _files(f"{__package__}.queries").joinpath("locals.scm").read_text()
# TAGS_QUERY = _files(f"{__package__}.queries").joinpath("tags.scm").read_text()

__all__ = [
    "language",
    # "HIGHLIGHTS_QUERY",
    # "INJECTIONS_QUERY",
    # "LOCALS_QUERY",
    # "TAGS_QUERY",
]
