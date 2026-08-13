#include <stdint.h>

int iswalpha(int32_t character) {
  return
    (character >= 'A' && character <= 'Z') ||
    (character >= 'a' && character <= 'z');
}

int iswdigit(int32_t character) {
  return character >= '0' && character <= '9';
}

int iswspace(int32_t character) {
  return
    character == ' ' ||
    character == '\t' ||
    character == '\n' ||
    character == '\r' ||
    character == '\f' ||
    character == '\v';
}
