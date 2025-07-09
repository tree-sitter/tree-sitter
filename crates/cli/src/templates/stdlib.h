#pragma once

#include <stdint.h>

#define NULL ((void*)0)

void* malloc(size_t size);
void* calloc(size_t nmemb, size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);

void abort(void);
