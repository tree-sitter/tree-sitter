#pragma once

#include <stdint.h>

int iswalnum(wint_t);
int iswalpha(wint_t);
int iswblank(wint_t);
int iswdigit(wint_t);
int iswlower(wint_t);
int iswspace(wint_t);
int iswupper(wint_t);
int iswxdigit(wint_t);

wint_t towlower(wint_t);
wint_t towupper(wint_t);
