from typing import Final
from typing_extensions import CapsuleType

HIGHLIGHTS_QUERY: Final[str] | None
INJECTIONS_QUERY: Final[str] | None
LOCALS_QUERY: Final[str] | None
TAGS_QUERY: Final[str] | None

def language() -> CapsuleType: ...
