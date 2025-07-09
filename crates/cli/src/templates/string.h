#pragma once

#include <stdint.h>

void* memchr(const void*, int, size_t);
int memcmp(const void*, const void*, size_t);
void* memcpy(void*, const void*, size_t);
void *memmove(void*, const void*, size_t);
void *memset(void*, int, size_t);
int strcmp(const char*, const char*);
size_t strlen(const char*);
char* strncat(char*, const char*, size_t);
int strncmp(const char*, const char*, size_t);
char* strncpy(char*, const char*, size_t);
