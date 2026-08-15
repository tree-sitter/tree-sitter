#ifndef BULK_MEMORY_THRESHOLD
#define BULK_MEMORY_THRESHOLD 32
#endif

#include "./libc/string/memchr.c"
#undef ALIGN
#undef HASZERO
#undef HIGHS
#undef ONES
#undef SS

#include "./libc/string/memcmp.c"
#include "./libc/string/memcpy.c"
#undef LS
#undef RS

#include "./libc/string/memmove.c"
#undef WS

#include "./libc/string/memset.c"
#include "./libc/string/strchrnul.c"
#undef ALIGN
#undef HASZERO
#undef HIGHS
#undef ONES

#include "./libc/string/strchr.c"
#include "./libc/string/strcmp.c"
#include "./libc/string/strlen.c"
#undef ALIGN
#undef HASZERO
#undef HIGHS
#undef ONES

#include "./libc/string/strncat.c"
#include "./libc/string/strncmp.c"
#include "./libc/string/stpncpy.c"
#undef ALIGN
#undef HASZERO
#undef HIGHS
#undef ONES

#include "./libc/string/strncpy.c"
#include "./libc/string/wcschr.c"
#include "./libc/string/wcslen.c"

#include "./libc/ctype/isblank.c"
#include "./libc/ctype/iswalnum.c"

#define table tree_sitter_iswalpha_table
#include "./libc/ctype/iswalpha.c"
#undef table

#include "./libc/ctype/iswblank.c"
#include "./libc/ctype/iswdigit.c"
#include "./libc/ctype/iswlower.c"

#define table tree_sitter_iswpunct_table
#include "./libc/ctype/iswpunct.c"
#undef table

#include "./libc/ctype/iswspace.c"
#include "./libc/ctype/iswupper.c"
#include "./libc/ctype/iswxdigit.c"
#include "./libc/ctype/towctrans.c"
