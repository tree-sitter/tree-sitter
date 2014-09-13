/*
 *  Copyright (c) 2009 Public Software Group e. V., Berlin, Germany
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */


/*
 *  File name:    utf8proc.h
 *
 *  Description:
 *  Header files for libutf8proc, which is a mapping tool for UTF-8 strings
 *  with following features:
 *  - decomposing and composing of strings
 *  - replacing compatibility characters with their equivalents
 *  - stripping of "default ignorable characters"
 *    like SOFT-HYPHEN or ZERO-WIDTH-SPACE
 *  - folding of certain characters for string comparison
 *    (e.g. HYPHEN U+2010 and MINUS U+2212 to ASCII "-")
 *    (see "LUMP" option)
 *  - optional rejection of strings containing non-assigned code points
 *  - stripping of control characters
 *  - stripping of character marks (accents, etc.)
 *  - transformation of LF, CRLF, CR and NEL to line-feed (LF)
 *    or to the unicode chararacters for paragraph separation (PS)
 *    or line separation (LS).
 *  - unicode case folding (for case insensitive string comparisons)
 *  - rejection of illegal UTF-8 data
 *    (i.e. UTF-8 encoded UTF-16 surrogates)
 *  - support for korean hangul characters
 *  Unicode Version 5.0.0 is supported.
 */


#ifndef UTF8PROC_H
#define UTF8PROC_H


#include <stdlib.h>
#include <sys/types.h>
#ifdef _MSC_VER
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
#ifdef _WIN64
#define ssize_t __int64
#else
#define ssize_t int
#endif
typedef unsigned char bool;
enum {false, true};
#else
#include <stdbool.h>
#include <inttypes.h>
#endif
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SSIZE_MAX
#define SSIZE_MAX ((size_t)SIZE_MAX/2)
#endif

#define UTF8PROC_NULLTERM  (1<<0)
#define UTF8PROC_STABLE    (1<<1)
#define UTF8PROC_COMPAT    (1<<2)
#define UTF8PROC_COMPOSE   (1<<3)
#define UTF8PROC_DECOMPOSE (1<<4)
#define UTF8PROC_IGNORE    (1<<5)
#define UTF8PROC_REJECTNA  (1<<6)
#define UTF8PROC_NLF2LS    (1<<7)
#define UTF8PROC_NLF2PS    (1<<8)
#define UTF8PROC_NLF2LF    (UTF8PROC_NLF2LS | UTF8PROC_NLF2PS)
#define UTF8PROC_STRIPCC   (1<<9)
#define UTF8PROC_CASEFOLD  (1<<10)
#define UTF8PROC_CHARBOUND (1<<11)
#define UTF8PROC_LUMP      (1<<12)
#define UTF8PROC_STRIPMARK (1<<13)
/*
 *  Flags being regarded by several functions in the library:
 *  NULLTERM:  The given UTF-8 input is NULL terminated.
 *  STABLE:    Unicode Versioning Stability has to be respected.
 *  COMPAT:    Compatiblity decomposition
 *             (i.e. formatting information is lost)
 *  COMPOSE:   Return a result with composed characters.
 *  DECOMPOSE: Return a result with decomposed characters.
 *  IGNORE:    Strip "default ignorable characters"
 *  REJECTNA:  Return an error, if the input contains unassigned
 *             code points.
 *  NLF2LS:    Indicating that NLF-sequences (LF, CRLF, CR, NEL) are
 *             representing a line break, and should be converted to the
 *             unicode character for line separation (LS).
 *  NLF2PS:    Indicating that NLF-sequences are representing a paragraph
 *             break, and should be converted to the unicode character for
 *             paragraph separation (PS).
 *  NLF2LF:    Indicating that the meaning of NLF-sequences is unknown.
 *  STRIPCC:   Strips and/or convers control characters.
 *             NLF-sequences are transformed into space, except if one of
 *             the NLF2LS/PS/LF options is given.
 *             HorizontalTab (HT) and FormFeed (FF) are treated as a
 *             NLF-sequence in this case.
 *             All other control characters are simply removed.
 *  CASEFOLD:  Performs unicode case folding, to be able to do a
 *             case-insensitive string comparison.
 *  CHARBOUND: Inserts 0xFF bytes at the beginning of each sequence which
 *             is representing a single grapheme cluster (see UAX#29).
 *  LUMP:      Lumps certain characters together
 *             (e.g. HYPHEN U+2010 and MINUS U+2212 to ASCII "-").
 *             (See lump.txt for details.)
 *             If NLF2LF is set, this includes a transformation of
 *             paragraph and line separators to ASCII line-feed (LF).
 *  STRIPMARK: Strips all character markings
 *             (non-spacing, spacing and enclosing) (i.e. accents)
 *             NOTE: this option works only with COMPOSE or DECOMPOSE
 */

#define UTF8PROC_ERROR_NOMEM -1
#define UTF8PROC_ERROR_OVERFLOW -2
#define UTF8PROC_ERROR_INVALIDUTF8 -3
#define UTF8PROC_ERROR_NOTASSIGNED -4
#define UTF8PROC_ERROR_INVALIDOPTS -5
/*
 *  Error codes being returned by almost all functions:
 *  ERROR_NOMEM:       Memory could not be allocated.
 *  ERROR_OVERFLOW:    The given string is too long to be processed.
 *  ERROR_INVALIDUTF8: The given string is not a legal UTF-8 string.
 *  ERROR_NOTASSIGNED: The REJECTNA flag was set,
 *                     and an unassigned code point was found.
 *  ERROR_INVALIDOPTS: Invalid options have been used.
 */

typedef int16_t utf8proc_propval_t;
typedef struct utf8proc_property_struct {
  utf8proc_propval_t category;
  utf8proc_propval_t combining_class;
  utf8proc_propval_t bidi_class;
  utf8proc_propval_t decomp_type;
  const int32_t *decomp_mapping;
  unsigned bidi_mirrored:1;
  int32_t uppercase_mapping;
  int32_t lowercase_mapping;
  int32_t titlecase_mapping;
  int32_t comb1st_index;
  int32_t comb2nd_index;
  unsigned comp_exclusion:1;
  unsigned ignorable:1;
  unsigned control_boundary:1;
  unsigned extend:1;
  const int32_t *casefold_mapping;
} utf8proc_property_t;

#define UTF8PROC_CATEGORY_LU  1
#define UTF8PROC_CATEGORY_LL  2
#define UTF8PROC_CATEGORY_LT  3
#define UTF8PROC_CATEGORY_LM  4
#define UTF8PROC_CATEGORY_LO  5
#define UTF8PROC_CATEGORY_MN  6
#define UTF8PROC_CATEGORY_MC  7
#define UTF8PROC_CATEGORY_ME  8
#define UTF8PROC_CATEGORY_ND  9
#define UTF8PROC_CATEGORY_NL 10
#define UTF8PROC_CATEGORY_NO 11
#define UTF8PROC_CATEGORY_PC 12
#define UTF8PROC_CATEGORY_PD 13
#define UTF8PROC_CATEGORY_PS 14
#define UTF8PROC_CATEGORY_PE 15
#define UTF8PROC_CATEGORY_PI 16
#define UTF8PROC_CATEGORY_PF 17
#define UTF8PROC_CATEGORY_PO 18
#define UTF8PROC_CATEGORY_SM 19
#define UTF8PROC_CATEGORY_SC 20
#define UTF8PROC_CATEGORY_SK 21
#define UTF8PROC_CATEGORY_SO 22
#define UTF8PROC_CATEGORY_ZS 23
#define UTF8PROC_CATEGORY_ZL 24
#define UTF8PROC_CATEGORY_ZP 25
#define UTF8PROC_CATEGORY_CC 26
#define UTF8PROC_CATEGORY_CF 27
#define UTF8PROC_CATEGORY_CS 28
#define UTF8PROC_CATEGORY_CO 29
#define UTF8PROC_CATEGORY_CN 30
#define UTF8PROC_BIDI_CLASS_L    1
#define UTF8PROC_BIDI_CLASS_LRE  2
#define UTF8PROC_BIDI_CLASS_LRO  3
#define UTF8PROC_BIDI_CLASS_R    4
#define UTF8PROC_BIDI_CLASS_AL   5
#define UTF8PROC_BIDI_CLASS_RLE  6
#define UTF8PROC_BIDI_CLASS_RLO  7
#define UTF8PROC_BIDI_CLASS_PDF  8
#define UTF8PROC_BIDI_CLASS_EN   9
#define UTF8PROC_BIDI_CLASS_ES  10
#define UTF8PROC_BIDI_CLASS_ET  11
#define UTF8PROC_BIDI_CLASS_AN  12
#define UTF8PROC_BIDI_CLASS_CS  13
#define UTF8PROC_BIDI_CLASS_NSM 14
#define UTF8PROC_BIDI_CLASS_BN  15
#define UTF8PROC_BIDI_CLASS_B   16
#define UTF8PROC_BIDI_CLASS_S   17
#define UTF8PROC_BIDI_CLASS_WS  18
#define UTF8PROC_BIDI_CLASS_ON  19
#define UTF8PROC_DECOMP_TYPE_FONT      1
#define UTF8PROC_DECOMP_TYPE_NOBREAK   2
#define UTF8PROC_DECOMP_TYPE_INITIAL   3
#define UTF8PROC_DECOMP_TYPE_MEDIAL    4
#define UTF8PROC_DECOMP_TYPE_FINAL     5
#define UTF8PROC_DECOMP_TYPE_ISOLATED  6
#define UTF8PROC_DECOMP_TYPE_CIRCLE    7
#define UTF8PROC_DECOMP_TYPE_SUPER     8
#define UTF8PROC_DECOMP_TYPE_SUB       9
#define UTF8PROC_DECOMP_TYPE_VERTICAL 10
#define UTF8PROC_DECOMP_TYPE_WIDE     11
#define UTF8PROC_DECOMP_TYPE_NARROW   12
#define UTF8PROC_DECOMP_TYPE_SMALL    13
#define UTF8PROC_DECOMP_TYPE_SQUARE   14
#define UTF8PROC_DECOMP_TYPE_FRACTION 15
#define UTF8PROC_DECOMP_TYPE_COMPAT   16

extern const int8_t utf8proc_utf8class[256];

const char *utf8proc_version(void);

const char *utf8proc_errmsg(ssize_t errcode);
/*
 *  Returns a static error string for the given error code.
 */

ssize_t utf8proc_iterate(const uint8_t *str, ssize_t strlen, int32_t *dst);
/*
 *  Reads a single char from the UTF-8 sequence being pointed to by 'str'.
 *  The maximum number of bytes read is 'strlen', unless 'strlen' is
 *  negative.
 *  If a valid unicode char could be read, it is stored in the variable
 *  being pointed to by 'dst', otherwise that variable will be set to -1.
 *  In case of success the number of bytes read is returned, otherwise a
 *  negative error code is returned.
 */

bool utf8proc_codepoint_valid(int32_t uc);
/*
 *  Returns 1, if the given unicode code-point is valid, otherwise 0.
 */

ssize_t utf8proc_encode_char(int32_t uc, uint8_t *dst);
/*
 *  Encodes the unicode char with the code point 'uc' as an UTF-8 string in
 *  the byte array being pointed to by 'dst'. This array has to be at least
 *  4 bytes long.
 *  In case of success the number of bytes written is returned,
 *  otherwise 0.
 *  This function does not check if 'uc' is a valid unicode code point.
 */

const utf8proc_property_t *utf8proc_get_property(int32_t uc);
/*
 *  Returns a pointer to a (constant) struct containing information about
 *  the unicode char with the given code point 'uc'.
 *  If the character is not existent a pointer to a special struct is
 *  returned, where 'category' is a NULL pointer.
 *  WARNING: The parameter 'uc' has to be in the range of 0x0000 to
 *           0x10FFFF, otherwise the program might crash!
 */

ssize_t utf8proc_decompose_char(
  int32_t uc, int32_t *dst, ssize_t bufsize,
  int options, int *last_boundclass
);
/*
 *  Writes a decomposition of the unicode char 'uc' into the array being
 *  pointed to by 'dst'.
 *  Following flags in the 'options' field are regarded:
 *  REJECTNA:  an unassigned unicode code point leads to an error
 *  IGNORE:    "default ignorable" chars are stripped
 *  CASEFOLD:  unicode casefolding is applied
 *  COMPAT:    replace certain characters with their
 *             compatibility decomposition
 *  CHARBOUND: Inserts 0xFF bytes before each grapheme cluster
 *  LUMP:      lumps certain different characters together
 *  STRIPMARK: removes all character marks
 *  The pointer 'last_boundclass' has to point to an integer variable which
 *  is storing the last character boundary class, if the CHARBOUND option
 *  is used.
 *  In case of success the number of chars written is returned,
 *  in case of an error, a negative error code is returned.
 *  If the number of written chars would be bigger than 'bufsize',
 *  the buffer (up to 'bufsize') has inpredictable data, and the needed
 *  buffer size is returned.
 *  WARNING: The parameter 'uc' has to be in the range of 0x0000 to
 *           0x10FFFF, otherwise the program might crash!
 */

ssize_t utf8proc_decompose(
  const uint8_t *str, ssize_t strlen,
  int32_t *buffer, ssize_t bufsize, int options
);
/*
 *  Does the same as 'utf8proc_decompose_char', but acts on a whole UTF-8
 *  string, and orders the decomposed sequences correctly.
 *  If the NULLTERM flag in 'options' is set, processing will be stopped,
 *  when a NULL byte is encounted, otherwise 'strlen' bytes are processed.
 *  The result in form of unicode code points is written into the buffer
 *  being pointed to by 'buffer', having the length of 'bufsize' entries.
 *  In case of success the number of chars written is returned,
 *  in case of an error, a negative error code is returned.
 *  If the number of written chars would be bigger than 'bufsize',
 *  the buffer (up to 'bufsize') has inpredictable data, and the needed
 *  buffer size is returned.
 */

ssize_t utf8proc_reencode(int32_t *buffer, ssize_t length, int options);
/*
 *  Reencodes the sequence of unicode characters given by the pointer
 *  'buffer' and 'length' as UTF-8.
 *  The result is stored in the same memory area where the data is read.
 *  Following flags in the 'options' field are regarded:
 *  NLF2LS:  converts LF, CRLF, CR and NEL into LS
 *  NLF2PS:  converts LF, CRLF, CR and NEL into PS
 *  NLF2LF:  converts LF, CRLF, CR and NEL into LF
 *  STRIPCC: strips or converts all non-affected control characters
 *  COMPOSE: tries to combine decomposed characters into composite
 *           characters
 *  STABLE:  prohibits combining characters which would violate
 *           the unicode versioning stability
 *  In case of success the length of the resulting UTF-8 string is
 *  returned, otherwise a negative error code is returned.
 *  WARNING: The amount of free space being pointed to by 'buffer', has to
 *           exceed the amount of the input data by one byte, and the
 *           entries of the array pointed to by 'str' have to be in the
 *           range of 0x0000 to 0x10FFFF, otherwise the program might
 *           crash!
 */

ssize_t utf8proc_map(
  const uint8_t *str, ssize_t strlen, uint8_t **dstptr, int options
);
/*
 *  Maps the given UTF-8 string being pointed to by 'str' to a new UTF-8
 *  string, which is allocated dynamically, and afterwards pointed to by
 *  the pointer being pointed to by 'dstptr'.
 *  If the NULLTERM flag in the 'options' field is set, the length is
 *  determined by a NULL terminator, otherwise the parameter 'strlen' is
 *  evaluated to determine the string length, but in any case the result
 *  will be NULL terminated (though it might contain NULL characters
 *  before). Other flags in the 'options' field are passed to the functions
 *  defined above, and regarded as described.
 *  In case of success the length of the new string is returned,
 *  otherwise a negative error code is returned.
 *  NOTICE: The memory of the new UTF-8 string will have been allocated with
 *          'malloc', and has theirfore to be freed with 'free'.
 */

uint8_t *utf8proc_NFD(const uint8_t *str);
uint8_t *utf8proc_NFC(const uint8_t *str);
uint8_t *utf8proc_NFKD(const uint8_t *str);
uint8_t *utf8proc_NFKC(const uint8_t *str);
/*
 *  Returns a pointer to newly allocated memory of a NFD, NFC, NFKD or NFKC
 *  normalized version of the null-terminated string 'str'.
 */

#ifdef __cplusplus
}
#endif

#endif

