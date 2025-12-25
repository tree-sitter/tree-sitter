#include <wctype.h>

int iswlower(wint_t wch) {
    return (unsigned)wch - L'a' < 26;
}

int iswupper(wint_t wch) {
    return (unsigned)wch - L'A' < 26;
}
