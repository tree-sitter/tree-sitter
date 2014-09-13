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
 *  This library contains derived data from a modified version of the
 *  Unicode data files.
 *
 *  The original data files are available at
 *  http://www.unicode.org/Public/UNIDATA/
 *
 *  Please notice the copyright statement in the file "utf8proc_data.c".
 */


/*
 *  File name:    utf8proc.c
 *
 *  Description:
 *  Implementation of libutf8proc.
 */


#include "utf8proc.h"
#include "utf8proc_data.c"


const int8_t utf8proc_utf8class[256] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0 };

#define UTF8PROC_HANGUL_SBASE 0xAC00
#define UTF8PROC_HANGUL_LBASE 0x1100
#define UTF8PROC_HANGUL_VBASE 0x1161
#define UTF8PROC_HANGUL_TBASE 0x11A7
#define UTF8PROC_HANGUL_LCOUNT 19
#define UTF8PROC_HANGUL_VCOUNT 21
#define UTF8PROC_HANGUL_TCOUNT 28
#define UTF8PROC_HANGUL_NCOUNT 588
#define UTF8PROC_HANGUL_SCOUNT 11172
/* END is exclusive */
#define UTF8PROC_HANGUL_L_START  0x1100
#define UTF8PROC_HANGUL_L_END    0x115A
#define UTF8PROC_HANGUL_L_FILLER 0x115F
#define UTF8PROC_HANGUL_V_START  0x1160
#define UTF8PROC_HANGUL_V_END    0x11A3
#define UTF8PROC_HANGUL_T_START  0x11A8
#define UTF8PROC_HANGUL_T_END    0x11FA
#define UTF8PROC_HANGUL_S_START  0xAC00
#define UTF8PROC_HANGUL_S_END    0xD7A4


#define UTF8PROC_BOUNDCLASS_START    0
#define UTF8PROC_BOUNDCLASS_OTHER    1
#define UTF8PROC_BOUNDCLASS_CR       2
#define UTF8PROC_BOUNDCLASS_LF       3
#define UTF8PROC_BOUNDCLASS_CONTROL  4
#define UTF8PROC_BOUNDCLASS_EXTEND   5
#define UTF8PROC_BOUNDCLASS_L        6
#define UTF8PROC_BOUNDCLASS_V        7
#define UTF8PROC_BOUNDCLASS_T        8
#define UTF8PROC_BOUNDCLASS_LV       9
#define UTF8PROC_BOUNDCLASS_LVT     10


const char *utf8proc_version(void) {
  return "1.1.6";
}

const char *utf8proc_errmsg(ssize_t errcode) {
  switch (errcode) {
    case UTF8PROC_ERROR_NOMEM:
    return "Memory for processing UTF-8 data could not be allocated.";
    case UTF8PROC_ERROR_OVERFLOW:
    return "UTF-8 string is too long to be processed.";
    case UTF8PROC_ERROR_INVALIDUTF8:
    return "Invalid UTF-8 string";
    case UTF8PROC_ERROR_NOTASSIGNED:
    return "Unassigned Unicode code point found in UTF-8 string.";
    case UTF8PROC_ERROR_INVALIDOPTS:
    return "Invalid options for UTF-8 processing chosen.";
    default:
    return "An unknown error occured while processing UTF-8 data.";
  }
}

ssize_t utf8proc_iterate(
  const uint8_t *str, ssize_t strlen, int32_t *dst
) {
  int length;
  int i;
  int32_t uc = -1;
  *dst = -1;
  if (!strlen) return 0;
  length = utf8proc_utf8class[str[0]];
  if (!length) return UTF8PROC_ERROR_INVALIDUTF8;
  if (strlen >= 0 && length > strlen) return UTF8PROC_ERROR_INVALIDUTF8;
  for (i=1; i<length; i++) {
    if ((str[i] & 0xC0) != 0x80) return UTF8PROC_ERROR_INVALIDUTF8;
  }
  switch (length) {
    case 1:
    uc = str[0];
    break;
    case 2:
    uc = ((str[0] & 0x1F) <<  6) + (str[1] & 0x3F);
    if (uc < 0x80) uc = -1;
    break;
    case 3:
    uc = ((str[0] & 0x0F) << 12) + ((str[1] & 0x3F) <<  6)
      + (str[2] & 0x3F);
    if (uc < 0x800 || (uc >= 0xD800 && uc < 0xE000) ||
      (uc >= 0xFDD0 && uc < 0xFDF0)) uc = -1;
    break;
    case 4:
    uc = ((str[0] & 0x07) << 18) + ((str[1] & 0x3F) << 12)
      + ((str[2] & 0x3F) <<  6) + (str[3] & 0x3F);
    if (uc < 0x10000 || uc >= 0x110000) uc = -1;
    break;
  }
  if (uc < 0 || ((uc & 0xFFFF) >= 0xFFFE))
    return UTF8PROC_ERROR_INVALIDUTF8;
  *dst = uc;
  return length;
}

bool utf8proc_codepoint_valid(int32_t uc) {
  if (uc < 0 || uc >= 0x110000 ||
    ((uc & 0xFFFF) >= 0xFFFE) || (uc >= 0xD800 && uc < 0xE000) ||
    (uc >= 0xFDD0 && uc < 0xFDF0)) return false;
  else return true;
}

ssize_t utf8proc_encode_char(int32_t uc, uint8_t *dst) {
  if (uc < 0x00) {
    return 0;
  } else if (uc < 0x80) {
    dst[0] = uc;
    return 1;
  } else if (uc < 0x800) {
    dst[0] = 0xC0 + (uc >> 6);
    dst[1] = 0x80 + (uc & 0x3F);
    return 2;
  } else if (uc == 0xFFFF) {
    dst[0] = 0xFF;
    return 1;
  } else if (uc == 0xFFFE) {
    dst[0] = 0xFE;
    return 1;
  } else if (uc < 0x10000) {
    dst[0] = 0xE0 + (uc >> 12);
    dst[1] = 0x80 + ((uc >> 6) & 0x3F);
    dst[2] = 0x80 + (uc & 0x3F);
    return 3;
  } else if (uc < 0x110000) {
    dst[0] = 0xF0 + (uc >> 18);
    dst[1] = 0x80 + ((uc >> 12) & 0x3F);
    dst[2] = 0x80 + ((uc >> 6) & 0x3F);
    dst[3] = 0x80 + (uc & 0x3F);
    return 4;
  } else return 0;
}

const utf8proc_property_t *utf8proc_get_property(int32_t uc) {
  /* ASSERT: uc >= 0 && uc < 0x110000 */
  return utf8proc_properties + (
    utf8proc_stage2table[
      utf8proc_stage1table[uc >> 8] + (uc & 0xFF)
    ]
  );
}

#define utf8proc_decompose_lump(replacement_uc) \
  return utf8proc_decompose_char((replacement_uc), dst, bufsize, \
  options & ~UTF8PROC_LUMP, last_boundclass)

ssize_t utf8proc_decompose_char(int32_t uc, int32_t *dst, ssize_t bufsize,
    int options, int *last_boundclass) {
  /* ASSERT: uc >= 0 && uc < 0x110000 */
  const utf8proc_property_t *property;
  utf8proc_propval_t category;
  int32_t hangul_sindex;
  property = utf8proc_get_property(uc);
  category = property->category;
  hangul_sindex = uc - UTF8PROC_HANGUL_SBASE;
  if (options & (UTF8PROC_COMPOSE|UTF8PROC_DECOMPOSE)) {
    if (hangul_sindex >= 0 && hangul_sindex < UTF8PROC_HANGUL_SCOUNT) {
      int32_t hangul_tindex;
      if (bufsize >= 1) {
        dst[0] = UTF8PROC_HANGUL_LBASE +
          hangul_sindex / UTF8PROC_HANGUL_NCOUNT;
        if (bufsize >= 2) dst[1] = UTF8PROC_HANGUL_VBASE +
          (hangul_sindex % UTF8PROC_HANGUL_NCOUNT) / UTF8PROC_HANGUL_TCOUNT;
      }
      hangul_tindex = hangul_sindex % UTF8PROC_HANGUL_TCOUNT;
      if (!hangul_tindex) return 2;
      if (bufsize >= 3) dst[2] = UTF8PROC_HANGUL_TBASE + hangul_tindex;
      return 3;
    }
  }
  if (options & UTF8PROC_REJECTNA) {
    if (!category) return UTF8PROC_ERROR_NOTASSIGNED;
  }
  if (options & UTF8PROC_IGNORE) {
    if (property->ignorable) return 0;
  }
  if (options & UTF8PROC_LUMP) {
    if (category == UTF8PROC_CATEGORY_ZS) utf8proc_decompose_lump(0x0020);
    if (uc == 0x2018 || uc == 0x2019 || uc == 0x02BC || uc == 0x02C8)
      utf8proc_decompose_lump(0x0027);
    if (category == UTF8PROC_CATEGORY_PD || uc == 0x2212)
      utf8proc_decompose_lump(0x002D);
    if (uc == 0x2044 || uc == 0x2215) utf8proc_decompose_lump(0x002F);
    if (uc == 0x2236) utf8proc_decompose_lump(0x003A);
    if (uc == 0x2039 || uc == 0x2329 || uc == 0x3008)
      utf8proc_decompose_lump(0x003C);
    if (uc == 0x203A || uc == 0x232A || uc == 0x3009)
      utf8proc_decompose_lump(0x003E);
    if (uc == 0x2216) utf8proc_decompose_lump(0x005C);
    if (uc == 0x02C4 || uc == 0x02C6 || uc == 0x2038 || uc == 0x2303)
      utf8proc_decompose_lump(0x005E);
    if (category == UTF8PROC_CATEGORY_PC || uc == 0x02CD)
      utf8proc_decompose_lump(0x005F);
    if (uc == 0x02CB) utf8proc_decompose_lump(0x0060);
    if (uc == 0x2223) utf8proc_decompose_lump(0x007C);
    if (uc == 0x223C) utf8proc_decompose_lump(0x007E);
    if ((options & UTF8PROC_NLF2LS) && (options & UTF8PROC_NLF2PS)) {
      if (category == UTF8PROC_CATEGORY_ZL ||
          category == UTF8PROC_CATEGORY_ZP)
        utf8proc_decompose_lump(0x000A);
    }
  }
  if (options & UTF8PROC_STRIPMARK) {
    if (category == UTF8PROC_CATEGORY_MN ||
      category == UTF8PROC_CATEGORY_MC ||
      category == UTF8PROC_CATEGORY_ME) return 0;
  }
  if (options & UTF8PROC_CASEFOLD) {
    if (property->casefold_mapping) {
      const int32_t *casefold_entry;
      ssize_t written = 0;
      for (casefold_entry = property->casefold_mapping;
          *casefold_entry >= 0; casefold_entry++) {
        written += utf8proc_decompose_char(*casefold_entry, dst+written,
          (bufsize > written) ? (bufsize - written) : 0, options,
          last_boundclass);
        if (written < 0) return UTF8PROC_ERROR_OVERFLOW;
      }
      return written;
    }
  }
  if (options & (UTF8PROC_COMPOSE|UTF8PROC_DECOMPOSE)) {
    if (property->decomp_mapping &&
        (!property->decomp_type || (options & UTF8PROC_COMPAT))) {
      const int32_t *decomp_entry;
      ssize_t written = 0;
      for (decomp_entry = property->decomp_mapping;
          *decomp_entry >= 0; decomp_entry++) {
        written += utf8proc_decompose_char(*decomp_entry, dst+written,
          (bufsize > written) ? (bufsize - written) : 0, options,
        last_boundclass);
        if (written < 0) return UTF8PROC_ERROR_OVERFLOW;
      }
      return written;
    }
  }
  if (options & UTF8PROC_CHARBOUND) {
    bool boundary;
    int tbc, lbc;
    tbc =
      (uc == 0x000D) ? UTF8PROC_BOUNDCLASS_CR :
      (uc == 0x000A) ? UTF8PROC_BOUNDCLASS_LF :
      ((category == UTF8PROC_CATEGORY_ZL ||
        category == UTF8PROC_CATEGORY_ZP ||
        category == UTF8PROC_CATEGORY_CC ||
        category == UTF8PROC_CATEGORY_CF) &&
        !(uc == 0x200C || uc == 0x200D)) ? UTF8PROC_BOUNDCLASS_CONTROL :
      property->extend ? UTF8PROC_BOUNDCLASS_EXTEND :
      ((uc >= UTF8PROC_HANGUL_L_START && uc < UTF8PROC_HANGUL_L_END) ||
        uc == UTF8PROC_HANGUL_L_FILLER) ? UTF8PROC_BOUNDCLASS_L :
      (uc >= UTF8PROC_HANGUL_V_START && uc < UTF8PROC_HANGUL_V_END) ?
        UTF8PROC_BOUNDCLASS_V :
      (uc >= UTF8PROC_HANGUL_T_START && uc < UTF8PROC_HANGUL_T_END) ?
        UTF8PROC_BOUNDCLASS_T :
      (uc >= UTF8PROC_HANGUL_S_START && uc < UTF8PROC_HANGUL_S_END) ? (
        ((uc-UTF8PROC_HANGUL_SBASE) % UTF8PROC_HANGUL_TCOUNT == 0) ?
          UTF8PROC_BOUNDCLASS_LV : UTF8PROC_BOUNDCLASS_LVT
      ) :
      UTF8PROC_BOUNDCLASS_OTHER;
    lbc = *last_boundclass;
    boundary =
      (tbc == UTF8PROC_BOUNDCLASS_EXTEND) ? false :
      (lbc == UTF8PROC_BOUNDCLASS_START) ? true :
      (lbc == UTF8PROC_BOUNDCLASS_CR &&
       tbc == UTF8PROC_BOUNDCLASS_LF) ? false :
      (lbc == UTF8PROC_BOUNDCLASS_CONTROL) ? true :
      (tbc == UTF8PROC_BOUNDCLASS_CONTROL) ? true :
      (lbc == UTF8PROC_BOUNDCLASS_L &&
       (tbc == UTF8PROC_BOUNDCLASS_L ||
        tbc == UTF8PROC_BOUNDCLASS_V ||
        tbc == UTF8PROC_BOUNDCLASS_LV ||
        tbc == UTF8PROC_BOUNDCLASS_LVT)) ? false :
      ((lbc == UTF8PROC_BOUNDCLASS_LV ||
        lbc == UTF8PROC_BOUNDCLASS_V) &&
       (tbc == UTF8PROC_BOUNDCLASS_V ||
        tbc == UTF8PROC_BOUNDCLASS_T)) ? false :
      ((lbc == UTF8PROC_BOUNDCLASS_LVT ||
        lbc == UTF8PROC_BOUNDCLASS_T) &&
       tbc == UTF8PROC_BOUNDCLASS_T) ? false :
       true;
    *last_boundclass = tbc;
    if (boundary) {
      if (bufsize >= 1) dst[0] = 0xFFFF;
      if (bufsize >= 2) dst[1] = uc;
      return 2;
    }
  }
  if (bufsize >= 1) *dst = uc;
  return 1;
}

ssize_t utf8proc_decompose(
  const uint8_t *str, ssize_t strlen,
  int32_t *buffer, ssize_t bufsize, int options
) {
  /* strlen will be ignored, if UTF8PROC_NULLTERM is set in options */
  ssize_t wpos = 0;
  if ((options & UTF8PROC_COMPOSE) && (options & UTF8PROC_DECOMPOSE))
    return UTF8PROC_ERROR_INVALIDOPTS;
  if ((options & UTF8PROC_STRIPMARK) &&
      !(options & UTF8PROC_COMPOSE) && !(options & UTF8PROC_DECOMPOSE))
    return UTF8PROC_ERROR_INVALIDOPTS;
  {
    int32_t uc;
    ssize_t rpos = 0;
    ssize_t decomp_result;
    int boundclass = UTF8PROC_BOUNDCLASS_START;
    while (1) {
      if (options & UTF8PROC_NULLTERM) {
        rpos += utf8proc_iterate(str + rpos, -1, &uc);
        /* checking of return value is not neccessary,
           as 'uc' is < 0 in case of error */
        if (uc < 0) return UTF8PROC_ERROR_INVALIDUTF8;
        if (rpos < 0) return UTF8PROC_ERROR_OVERFLOW;
        if (uc == 0) break;
      } else {
        if (rpos >= strlen) break;
        rpos += utf8proc_iterate(str + rpos, strlen - rpos, &uc);
        if (uc < 0) return UTF8PROC_ERROR_INVALIDUTF8;
      }
      decomp_result = utf8proc_decompose_char(
        uc, buffer + wpos, (bufsize > wpos) ? (bufsize - wpos) : 0, options,
        &boundclass
      );
      if (decomp_result < 0) return decomp_result;
      wpos += decomp_result;
      /* prohibiting integer overflows due to too long strings: */
      if (wpos < 0 || wpos > SSIZE_MAX/sizeof(int32_t)/2)
        return UTF8PROC_ERROR_OVERFLOW;
    }
  }
  if ((options & (UTF8PROC_COMPOSE|UTF8PROC_DECOMPOSE)) && bufsize >= wpos) {
    ssize_t pos = 0;
    while (pos < wpos-1) {
      int32_t uc1, uc2;
      const utf8proc_property_t *property1, *property2;
      uc1 = buffer[pos];
      uc2 = buffer[pos+1];
      property1 = utf8proc_get_property(uc1);
      property2 = utf8proc_get_property(uc2);
      if (property1->combining_class > property2->combining_class &&
          property2->combining_class > 0) {
        buffer[pos] = uc2;
        buffer[pos+1] = uc1;
        if (pos > 0) pos--; else pos++;
      } else {
        pos++;
      }
    }
  }
  return wpos;
}

ssize_t utf8proc_reencode(int32_t *buffer, ssize_t length, int options) {
  /* UTF8PROC_NULLTERM option will be ignored, 'length' is never ignored
     ASSERT: 'buffer' has one spare byte of free space at the end! */
  if (options & (UTF8PROC_NLF2LS | UTF8PROC_NLF2PS | UTF8PROC_STRIPCC)) {
    ssize_t rpos;
    ssize_t wpos = 0;
    int32_t uc;
    for (rpos = 0; rpos < length; rpos++) {
      uc = buffer[rpos];
      if (uc == 0x000D && rpos < length-1 && buffer[rpos+1] == 0x000A) rpos++;
      if (uc == 0x000A || uc == 0x000D || uc == 0x0085 ||
          ((options & UTF8PROC_STRIPCC) && (uc == 0x000B || uc == 0x000C))) {
        if (options & UTF8PROC_NLF2LS) {
          if (options & UTF8PROC_NLF2PS) {
            buffer[wpos++] = 0x000A;
          } else {
            buffer[wpos++] = 0x2028;
          }
        } else {
          if (options & UTF8PROC_NLF2PS) {
            buffer[wpos++] = 0x2029;
          } else {
            buffer[wpos++] = 0x0020;
          }
        }
      } else if ((options & UTF8PROC_STRIPCC) &&
          (uc < 0x0020 || (uc >= 0x007F && uc < 0x00A0))) {
        if (uc == 0x0009) buffer[wpos++] = 0x0020;
      } else {
        buffer[wpos++] = uc;
      }
    }
    length = wpos;
  }
  if (options & UTF8PROC_COMPOSE) {
    int32_t *starter = NULL;
    int32_t current_char;
    const utf8proc_property_t *starter_property = NULL, *current_property;
    utf8proc_propval_t max_combining_class = -1;
    ssize_t rpos;
    ssize_t wpos = 0;
    int32_t composition;
    for (rpos = 0; rpos < length; rpos++) {
      current_char = buffer[rpos];
      current_property = utf8proc_get_property(current_char);
      if (starter && current_property->combining_class > max_combining_class) {
        /* combination perhaps possible */
        int32_t hangul_lindex;
        int32_t hangul_sindex;
        hangul_lindex = *starter - UTF8PROC_HANGUL_LBASE;
        if (hangul_lindex >= 0 && hangul_lindex < UTF8PROC_HANGUL_LCOUNT) {
          int32_t hangul_vindex;
          hangul_vindex = current_char - UTF8PROC_HANGUL_VBASE;
          if (hangul_vindex >= 0 && hangul_vindex < UTF8PROC_HANGUL_VCOUNT) {
            *starter = UTF8PROC_HANGUL_SBASE +
              (hangul_lindex * UTF8PROC_HANGUL_VCOUNT + hangul_vindex) *
              UTF8PROC_HANGUL_TCOUNT;
            starter_property = NULL;
            continue;
          }
        }
        hangul_sindex = *starter - UTF8PROC_HANGUL_SBASE;
        if (hangul_sindex >= 0 && hangul_sindex < UTF8PROC_HANGUL_SCOUNT &&
            (hangul_sindex % UTF8PROC_HANGUL_TCOUNT) == 0) {
          int32_t hangul_tindex;
          hangul_tindex = current_char - UTF8PROC_HANGUL_TBASE;
          if (hangul_tindex >= 0 && hangul_tindex < UTF8PROC_HANGUL_TCOUNT) {
            *starter += hangul_tindex;
            starter_property = NULL;
            continue;
          }
        }
        if (!starter_property) {
          starter_property = utf8proc_get_property(*starter);
        }
        if (starter_property->comb1st_index >= 0 &&
            current_property->comb2nd_index >= 0) {
          composition = utf8proc_combinations[
            starter_property->comb1st_index +
            current_property->comb2nd_index
          ];
          if (composition >= 0 && (!(options & UTF8PROC_STABLE) ||
              !(utf8proc_get_property(composition)->comp_exclusion))) {
            *starter = composition;
            starter_property = NULL;
            continue;
          }
        }
      }
      buffer[wpos] = current_char;
      if (current_property->combining_class) {
        if (current_property->combining_class > max_combining_class) {
          max_combining_class = current_property->combining_class;
        }
      } else {
        starter = buffer + wpos;
        starter_property = NULL;
        max_combining_class = -1;
      }
      wpos++;
    }
    length = wpos;
  }
  {
    ssize_t rpos, wpos = 0;
    int32_t uc;
    for (rpos = 0; rpos < length; rpos++) {
      uc = buffer[rpos];
      wpos += utf8proc_encode_char(uc, ((uint8_t *)buffer) + wpos);
    }
    ((uint8_t *)buffer)[wpos] = 0;
    return wpos;
  }
}

ssize_t utf8proc_map(
  const uint8_t *str, ssize_t strlen, uint8_t **dstptr, int options
) {
  int32_t *buffer;
  ssize_t result;
  *dstptr = NULL;
  result = utf8proc_decompose(str, strlen, NULL, 0, options);
  if (result < 0) return result;
  buffer = malloc(result * sizeof(int32_t) + 1);
  if (!buffer) return UTF8PROC_ERROR_NOMEM;
  result = utf8proc_decompose(str, strlen, buffer, result, options);
  if (result < 0) {
    free(buffer);
    return result;
  }
  result = utf8proc_reencode(buffer, result, options);
  if (result < 0) {
    free(buffer);
    return result;
  }
  {
    int32_t *newptr;
    newptr = realloc(buffer, (size_t)result+1);
    if (newptr) buffer = newptr;
  }
  *dstptr = (uint8_t *)buffer;
  return result;
}

uint8_t *utf8proc_NFD(const uint8_t *str) {
  uint8_t *retval;
  utf8proc_map(str, 0, &retval, UTF8PROC_NULLTERM | UTF8PROC_STABLE |
    UTF8PROC_DECOMPOSE);
  return retval;
}

uint8_t *utf8proc_NFC(const uint8_t *str) {
  uint8_t *retval;
  utf8proc_map(str, 0, &retval, UTF8PROC_NULLTERM | UTF8PROC_STABLE |
    UTF8PROC_COMPOSE);
  return retval;
}

uint8_t *utf8proc_NFKD(const uint8_t *str) {
  uint8_t *retval;
  utf8proc_map(str, 0, &retval, UTF8PROC_NULLTERM | UTF8PROC_STABLE |
    UTF8PROC_DECOMPOSE | UTF8PROC_COMPAT);
  return retval;
}

uint8_t *utf8proc_NFKC(const uint8_t *str) {
  uint8_t *retval;
  utf8proc_map(str, 0, &retval, UTF8PROC_NULLTERM | UTF8PROC_STABLE |
    UTF8PROC_COMPOSE | UTF8PROC_COMPAT);
  return retval;
}

