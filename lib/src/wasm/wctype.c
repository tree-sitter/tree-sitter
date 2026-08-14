#include <wctype.h>

int iswlower(wint_t wch) {
    return (unsigned)wch - L'a' < 26;
}

int iswupper(wint_t wch) {
    return (unsigned)wch - L'A' < 26;
}

int iswpunct(wint_t wch) {
  return (wch >= 33 && wch <= 47) ||
         (wch >= 58 && wch <= 64) ||
         (wch >= 91 && wch <= 96) ||
         (wch >= 123 && wch <= 126);
}

wint_t towlower(wint_t wch) {
  return iswupper(wch) ? wch + (L'a' - L'A') : wch;
}

wint_t towupper(wint_t wch) {
  return iswlower(wch) ? wch - (L'a' - L'A') : wch;
}
