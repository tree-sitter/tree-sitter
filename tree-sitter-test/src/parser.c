#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 32
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 25
#define ALIAS_COUNT 3
#define TOKEN_COUNT 15
#define EXTERNAL_TOKEN_COUNT 3
#define FIELD_COUNT 2
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 8

enum ts_symbol_identifiers {
  sym__line = 1,
  anon_sym_COLONskip = 2,
  anon_sym_COLONerror = 3,
  anon_sym_COLONfail_DASHfast = 4,
  anon_sym_COLONlanguage = 5,
  anon_sym_LPAREN = 6,
  anon_sym_RPAREN = 7,
  anon_sym_COLONplatform = 8,
  sym__lang = 9,
  sym__os = 10,
  sym__eol = 11,
  sym__equals_begin = 12,
  sym__equals_end = 13,
  sym__dashes = 14,
  sym_file = 15,
  sym_test = 16,
  aux_sym__body = 17,
  sym_header = 18,
  sym_attributes = 19,
  sym_attribute = 20,
  sym__language = 21,
  sym__platform = 22,
  aux_sym_file_repeat1 = 23,
  aux_sym_attributes_repeat1 = 24,
  alias_sym_input = 25,
  alias_sym_name = 26,
  alias_sym_output = 27,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym__line] = "_line",
  [anon_sym_COLONskip] = ":skip",
  [anon_sym_COLONerror] = ":error",
  [anon_sym_COLONfail_DASHfast] = ":fail-fast",
  [anon_sym_COLONlanguage] = ":language",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_COLONplatform] = ":platform",
  [sym__lang] = "parameter",
  [sym__os] = "parameter",
  [sym__eol] = "_eol",
  [sym__equals_begin] = "separator",
  [sym__equals_end] = "separator",
  [sym__dashes] = "separator",
  [sym_file] = "file",
  [sym_test] = "test",
  [aux_sym__body] = "_body",
  [sym_header] = "header",
  [sym_attributes] = "attributes",
  [sym_attribute] = "attribute",
  [sym__language] = "_language",
  [sym__platform] = "_platform",
  [aux_sym_file_repeat1] = "file_repeat1",
  [aux_sym_attributes_repeat1] = "attributes_repeat1",
  [alias_sym_input] = "input",
  [alias_sym_name] = "name",
  [alias_sym_output] = "output",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym__line] = sym__line,
  [anon_sym_COLONskip] = anon_sym_COLONskip,
  [anon_sym_COLONerror] = anon_sym_COLONerror,
  [anon_sym_COLONfail_DASHfast] = anon_sym_COLONfail_DASHfast,
  [anon_sym_COLONlanguage] = anon_sym_COLONlanguage,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_COLONplatform] = anon_sym_COLONplatform,
  [sym__lang] = sym__lang,
  [sym__os] = sym__lang,
  [sym__eol] = sym__eol,
  [sym__equals_begin] = sym__equals_begin,
  [sym__equals_end] = sym__equals_begin,
  [sym__dashes] = sym__equals_begin,
  [sym_file] = sym_file,
  [sym_test] = sym_test,
  [aux_sym__body] = aux_sym__body,
  [sym_header] = sym_header,
  [sym_attributes] = sym_attributes,
  [sym_attribute] = sym_attribute,
  [sym__language] = sym__language,
  [sym__platform] = sym__platform,
  [aux_sym_file_repeat1] = aux_sym_file_repeat1,
  [aux_sym_attributes_repeat1] = aux_sym_attributes_repeat1,
  [alias_sym_input] = alias_sym_input,
  [alias_sym_name] = alias_sym_name,
  [alias_sym_output] = alias_sym_output,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym__line] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_COLONskip] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLONerror] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLONfail_DASHfast] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLONlanguage] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLONplatform] = {
    .visible = true,
    .named = false,
  },
  [sym__lang] = {
    .visible = true,
    .named = true,
  },
  [sym__os] = {
    .visible = true,
    .named = true,
  },
  [sym__eol] = {
    .visible = false,
    .named = true,
  },
  [sym__equals_begin] = {
    .visible = true,
    .named = true,
  },
  [sym__equals_end] = {
    .visible = true,
    .named = true,
  },
  [sym__dashes] = {
    .visible = true,
    .named = true,
  },
  [sym_file] = {
    .visible = true,
    .named = true,
  },
  [sym_test] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__body] = {
    .visible = false,
    .named = false,
  },
  [sym_header] = {
    .visible = true,
    .named = true,
  },
  [sym_attributes] = {
    .visible = true,
    .named = true,
  },
  [sym_attribute] = {
    .visible = true,
    .named = true,
  },
  [sym__language] = {
    .visible = false,
    .named = true,
  },
  [sym__platform] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_attributes_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_input] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_name] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_output] = {
    .visible = true,
    .named = true,
  },
};

enum ts_field_identifiers {
  field_language = 1,
  field_platform = 2,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_language] = "language",
  [field_platform] = "platform",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [3] = {.index = 0, .length = 1},
  [4] = {.index = 1, .length = 1},
  [6] = {.index = 2, .length = 1},
  [7] = {.index = 3, .length = 1},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_language, 0, .inherited = true},
  [1] =
    {field_platform, 0, .inherited = true},
  [2] =
    {field_language, 2},
  [3] =
    {field_platform, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [1] = {
    [1] = alias_sym_input,
  },
  [2] = {
    [1] = alias_sym_name,
  },
  [5] = {
    [1] = alias_sym_input,
    [3] = alias_sym_output,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  aux_sym__body, 3,
    aux_sym__body,
    alias_sym_input,
    alias_sym_output,
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 13,
  [18] = 18,
  [19] = 15,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(76);
      if (lookahead == '\n') ADVANCE(129);
      if (lookahead == '\r') ADVANCE(130);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(83);
      if (lookahead == ':') ADVANCE(16);
      if (lookahead == 'a') ADVANCE(105);
      if (lookahead == 'd') ADVANCE(116);
      if (lookahead == 'f') ADVANCE(117);
      if (lookahead == 'i') ADVANCE(110);
      if (lookahead == 'l') ADVANCE(100);
      if (lookahead == 'm') ADVANCE(85);
      if (lookahead == 'n') ADVANCE(93);
      if (lookahead == 'o') ADVANCE(115);
      if (lookahead == 's') ADVANCE(111);
      if (lookahead == 'w') ADVANCE(102);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 1:
      if (lookahead == '-') ADVANCE(23);
      END_STATE();
    case 2:
      if (lookahead == 'a') ADVANCE(29);
      END_STATE();
    case 3:
      if (lookahead == 'a') ADVANCE(40);
      END_STATE();
    case 4:
      if (lookahead == 'a') ADVANCE(66);
      END_STATE();
    case 5:
      if (lookahead == 'a') ADVANCE(64);
      END_STATE();
    case 6:
      if (lookahead == 'a') ADVANCE(12);
      END_STATE();
    case 7:
      if (lookahead == 'a') ADVANCE(41);
      if (lookahead == 'd') ADVANCE(62);
      if (lookahead == 'f') ADVANCE(59);
      if (lookahead == 'i') ADVANCE(47);
      if (lookahead == 'l') ADVANCE(31);
      if (lookahead == 'm') ADVANCE(6);
      if (lookahead == 'n') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(54);
      if (lookahead == 's') ADVANCE(52);
      if (lookahead == 'w') ADVANCE(33);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(26);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(27);
      END_STATE();
    case 10:
      if (lookahead == 'a') ADVANCE(61);
      END_STATE();
    case 11:
      if (lookahead == 'b') ADVANCE(65);
      END_STATE();
    case 12:
      if (lookahead == 'c') ADVANCE(47);
      END_STATE();
    case 13:
      if (lookahead == 'd') ADVANCE(128);
      END_STATE();
    case 14:
      if (lookahead == 'd') ADVANCE(46);
      END_STATE();
    case 15:
      if (lookahead == 'd') ADVANCE(60);
      END_STATE();
    case 16:
      if (lookahead == 'e') ADVANCE(58);
      if (lookahead == 'f') ADVANCE(2);
      if (lookahead == 'l') ADVANCE(3);
      if (lookahead == 'p') ADVANCE(37);
      if (lookahead == 's') ADVANCE(34);
      END_STATE();
    case 17:
      if (lookahead == 'e') ADVANCE(81);
      END_STATE();
    case 18:
      if (lookahead == 'e') ADVANCE(11);
      END_STATE();
    case 19:
      if (lookahead == 'e') ADVANCE(68);
      END_STATE();
    case 20:
      if (lookahead == 'e') ADVANCE(42);
      END_STATE();
    case 21:
      if (lookahead == 'e') ADVANCE(18);
      END_STATE();
    case 22:
      if (lookahead == 'f') ADVANCE(36);
      END_STATE();
    case 23:
      if (lookahead == 'f') ADVANCE(5);
      END_STATE();
    case 24:
      if (lookahead == 'f') ADVANCE(49);
      END_STATE();
    case 25:
      if (lookahead == 'g') ADVANCE(70);
      END_STATE();
    case 26:
      if (lookahead == 'g') ADVANCE(17);
      END_STATE();
    case 27:
      if (lookahead == 'g') ADVANCE(51);
      END_STATE();
    case 28:
      if (lookahead == 'i') ADVANCE(53);
      END_STATE();
    case 29:
      if (lookahead == 'i') ADVANCE(35);
      END_STATE();
    case 30:
      if (lookahead == 'i') ADVANCE(63);
      END_STATE();
    case 31:
      if (lookahead == 'i') ADVANCE(43);
      END_STATE();
    case 32:
      if (lookahead == 'i') ADVANCE(13);
      END_STATE();
    case 33:
      if (lookahead == 'i') ADVANCE(44);
      END_STATE();
    case 34:
      if (lookahead == 'k') ADVANCE(28);
      END_STATE();
    case 35:
      if (lookahead == 'l') ADVANCE(1);
      END_STATE();
    case 36:
      if (lookahead == 'l') ADVANCE(73);
      END_STATE();
    case 37:
      if (lookahead == 'l') ADVANCE(4);
      END_STATE();
    case 38:
      if (lookahead == 'l') ADVANCE(10);
      END_STATE();
    case 39:
      if (lookahead == 'm') ADVANCE(84);
      END_STATE();
    case 40:
      if (lookahead == 'n') ADVANCE(25);
      END_STATE();
    case 41:
      if (lookahead == 'n') ADVANCE(15);
      END_STATE();
    case 42:
      if (lookahead == 'n') ADVANCE(11);
      END_STATE();
    case 43:
      if (lookahead == 'n') ADVANCE(69);
      END_STATE();
    case 44:
      if (lookahead == 'n') ADVANCE(14);
      END_STATE();
    case 45:
      if (lookahead == 'n') ADVANCE(22);
      END_STATE();
    case 46:
      if (lookahead == 'o') ADVANCE(71);
      END_STATE();
    case 47:
      if (lookahead == 'o') ADVANCE(63);
      END_STATE();
    case 48:
      if (lookahead == 'o') ADVANCE(56);
      END_STATE();
    case 49:
      if (lookahead == 'o') ADVANCE(57);
      END_STATE();
    case 50:
      if (lookahead == 'o') ADVANCE(32);
      END_STATE();
    case 51:
      if (lookahead == 'o') ADVANCE(45);
      END_STATE();
    case 52:
      if (lookahead == 'o') ADVANCE(38);
      END_STATE();
    case 53:
      if (lookahead == 'p') ADVANCE(78);
      END_STATE();
    case 54:
      if (lookahead == 'p') ADVANCE(20);
      END_STATE();
    case 55:
      if (lookahead == 'r') ADVANCE(48);
      END_STATE();
    case 56:
      if (lookahead == 'r') ADVANCE(79);
      END_STATE();
    case 57:
      if (lookahead == 'r') ADVANCE(39);
      END_STATE();
    case 58:
      if (lookahead == 'r') ADVANCE(55);
      END_STATE();
    case 59:
      if (lookahead == 'r') ADVANCE(21);
      END_STATE();
    case 60:
      if (lookahead == 'r') ADVANCE(50);
      END_STATE();
    case 61:
      if (lookahead == 'r') ADVANCE(30);
      END_STATE();
    case 62:
      if (lookahead == 'r') ADVANCE(9);
      END_STATE();
    case 63:
      if (lookahead == 's') ADVANCE(128);
      END_STATE();
    case 64:
      if (lookahead == 's') ADVANCE(67);
      END_STATE();
    case 65:
      if (lookahead == 's') ADVANCE(13);
      END_STATE();
    case 66:
      if (lookahead == 't') ADVANCE(24);
      END_STATE();
    case 67:
      if (lookahead == 't') ADVANCE(80);
      END_STATE();
    case 68:
      if (lookahead == 't') ADVANCE(11);
      END_STATE();
    case 69:
      if (lookahead == 'u') ADVANCE(72);
      END_STATE();
    case 70:
      if (lookahead == 'u') ADVANCE(8);
      END_STATE();
    case 71:
      if (lookahead == 'w') ADVANCE(63);
      END_STATE();
    case 72:
      if (lookahead == 'x') ADVANCE(128);
      END_STATE();
    case 73:
      if (lookahead == 'y') ADVANCE(128);
      END_STATE();
    case 74:
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 75:
      if (eof) ADVANCE(76);
      if (lookahead == '\n') ADVANCE(129);
      if (lookahead == '\r') ADVANCE(130);
      if (lookahead != 0) ADVANCE(77);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym__line);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(77);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_COLONskip);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_COLONerror);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_COLONfail_DASHfast);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_COLONlanguage);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_COLONplatform);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'a') ADVANCE(89);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'a') ADVANCE(98);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'a') ADVANCE(119);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'b') ADVANCE(121);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'c') ADVANCE(110);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'd') ADVANCE(127);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'd') ADVANCE(118);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'd') ADVANCE(112);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'e') ADVANCE(122);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'e') ADVANCE(88);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'e') ADVANCE(107);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'e') ADVANCE(94);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'f') ADVANCE(103);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'g') ADVANCE(114);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'i') ADVANCE(120);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'i') ADVANCE(106);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'i') ADVANCE(90);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'i') ADVANCE(109);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'l') ADVANCE(126);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'l') ADVANCE(87);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'n') ADVANCE(91);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'n') ADVANCE(123);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'n') ADVANCE(88);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'n') ADVANCE(97);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'n') ADVANCE(92);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'o') ADVANCE(120);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'o') ADVANCE(104);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'o') ADVANCE(124);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'o') ADVANCE(101);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'o') ADVANCE(108);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'p') ADVANCE(95);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'r') ADVANCE(86);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'r') ADVANCE(96);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'r') ADVANCE(113);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'r') ADVANCE(99);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 's') ADVANCE(127);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 's') ADVANCE(90);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 't') ADVANCE(88);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'u') ADVANCE(125);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'w') ADVANCE(120);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'x') ADVANCE(127);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == 'y') ADVANCE(127);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym__lang);
      if (lookahead == '-' ||
          lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(127);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym__os);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym__eol);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym__eol);
      if (lookahead == '\n') ADVANCE(129);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 0, .external_lex_state = 2},
  [2] = {.lex_state = 0, .external_lex_state = 3},
  [3] = {.lex_state = 0, .external_lex_state = 3},
  [4] = {.lex_state = 0, .external_lex_state = 3},
  [5] = {.lex_state = 0, .external_lex_state = 3},
  [6] = {.lex_state = 0, .external_lex_state = 3},
  [7] = {.lex_state = 0, .external_lex_state = 3},
  [8] = {.lex_state = 0, .external_lex_state = 3},
  [9] = {.lex_state = 0, .external_lex_state = 3},
  [10] = {.lex_state = 0, .external_lex_state = 2},
  [11] = {.lex_state = 0, .external_lex_state = 2},
  [12] = {.lex_state = 75, .external_lex_state = 2},
  [13] = {.lex_state = 75, .external_lex_state = 2},
  [14] = {.lex_state = 75, .external_lex_state = 2},
  [15] = {.lex_state = 75, .external_lex_state = 2},
  [16] = {.lex_state = 75, .external_lex_state = 4},
  [17] = {.lex_state = 75, .external_lex_state = 4},
  [18] = {.lex_state = 75},
  [19] = {.lex_state = 75, .external_lex_state = 4},
  [20] = {.lex_state = 75},
  [21] = {.lex_state = 75},
  [22] = {.lex_state = 0, .external_lex_state = 3},
  [23] = {.lex_state = 74},
  [24] = {.lex_state = 7},
  [25] = {.lex_state = 75},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_COLONskip] = ACTIONS(1),
    [anon_sym_COLONerror] = ACTIONS(1),
    [anon_sym_COLONfail_DASHfast] = ACTIONS(1),
    [anon_sym_COLONlanguage] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_COLONplatform] = ACTIONS(1),
    [sym__lang] = ACTIONS(1),
    [sym__os] = ACTIONS(1),
    [sym__eol] = ACTIONS(1),
    [sym__equals_begin] = ACTIONS(1),
    [sym__equals_end] = ACTIONS(1),
    [sym__dashes] = ACTIONS(1),
  },
  [1] = {
    [sym_file] = STATE(31),
    [sym_test] = STATE(10),
    [sym_header] = STATE(18),
    [aux_sym_file_repeat1] = STATE(10),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym__eol] = ACTIONS(5),
    [sym__equals_begin] = ACTIONS(7),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 9,
    ACTIONS(11), 1,
      anon_sym_COLONlanguage,
    ACTIONS(13), 1,
      anon_sym_COLONplatform,
    ACTIONS(15), 1,
      sym__eol,
    ACTIONS(17), 1,
      sym__equals_end,
    STATE(8), 1,
      sym__language,
    STATE(9), 1,
      sym__platform,
    STATE(22), 1,
      sym_attributes,
    STATE(4), 2,
      sym_attribute,
      aux_sym_attributes_repeat1,
    ACTIONS(9), 3,
      anon_sym_COLONskip,
      anon_sym_COLONerror,
      anon_sym_COLONfail_DASHfast,
  [31] = 8,
    ACTIONS(22), 1,
      anon_sym_COLONlanguage,
    ACTIONS(25), 1,
      anon_sym_COLONplatform,
    ACTIONS(28), 1,
      sym__eol,
    ACTIONS(31), 1,
      sym__equals_end,
    STATE(8), 1,
      sym__language,
    STATE(9), 1,
      sym__platform,
    STATE(3), 2,
      sym_attribute,
      aux_sym_attributes_repeat1,
    ACTIONS(19), 3,
      anon_sym_COLONskip,
      anon_sym_COLONerror,
      anon_sym_COLONfail_DASHfast,
  [59] = 8,
    ACTIONS(11), 1,
      anon_sym_COLONlanguage,
    ACTIONS(13), 1,
      anon_sym_COLONplatform,
    ACTIONS(33), 1,
      sym__eol,
    ACTIONS(35), 1,
      sym__equals_end,
    STATE(8), 1,
      sym__language,
    STATE(9), 1,
      sym__platform,
    STATE(3), 2,
      sym_attribute,
      aux_sym_attributes_repeat1,
    ACTIONS(9), 3,
      anon_sym_COLONskip,
      anon_sym_COLONerror,
      anon_sym_COLONfail_DASHfast,
  [87] = 1,
    ACTIONS(37), 7,
      sym__equals_end,
      anon_sym_COLONskip,
      anon_sym_COLONerror,
      anon_sym_COLONfail_DASHfast,
      anon_sym_COLONlanguage,
      anon_sym_COLONplatform,
      sym__eol,
  [97] = 1,
    ACTIONS(39), 7,
      sym__equals_end,
      anon_sym_COLONskip,
      anon_sym_COLONerror,
      anon_sym_COLONfail_DASHfast,
      anon_sym_COLONlanguage,
      anon_sym_COLONplatform,
      sym__eol,
  [107] = 1,
    ACTIONS(41), 7,
      sym__equals_end,
      anon_sym_COLONskip,
      anon_sym_COLONerror,
      anon_sym_COLONfail_DASHfast,
      anon_sym_COLONlanguage,
      anon_sym_COLONplatform,
      sym__eol,
  [117] = 1,
    ACTIONS(43), 7,
      sym__equals_end,
      anon_sym_COLONskip,
      anon_sym_COLONerror,
      anon_sym_COLONfail_DASHfast,
      anon_sym_COLONlanguage,
      anon_sym_COLONplatform,
      sym__eol,
  [127] = 1,
    ACTIONS(45), 7,
      sym__equals_end,
      anon_sym_COLONskip,
      anon_sym_COLONerror,
      anon_sym_COLONfail_DASHfast,
      anon_sym_COLONlanguage,
      anon_sym_COLONplatform,
      sym__eol,
  [137] = 5,
    ACTIONS(7), 1,
      sym__equals_begin,
    ACTIONS(47), 1,
      ts_builtin_sym_end,
    ACTIONS(49), 1,
      sym__eol,
    STATE(18), 1,
      sym_header,
    STATE(11), 2,
      sym_test,
      aux_sym_file_repeat1,
  [154] = 5,
    ACTIONS(51), 1,
      ts_builtin_sym_end,
    ACTIONS(53), 1,
      sym__eol,
    ACTIONS(56), 1,
      sym__equals_begin,
    STATE(18), 1,
      sym_header,
    STATE(11), 2,
      sym_test,
      aux_sym_file_repeat1,
  [171] = 3,
    STATE(13), 1,
      aux_sym__body,
    ACTIONS(59), 2,
      sym__equals_begin,
      ts_builtin_sym_end,
    ACTIONS(61), 2,
      sym__line,
      sym__eol,
  [183] = 3,
    STATE(13), 1,
      aux_sym__body,
    ACTIONS(63), 2,
      sym__equals_begin,
      ts_builtin_sym_end,
    ACTIONS(65), 2,
      sym__line,
      sym__eol,
  [195] = 3,
    STATE(12), 1,
      aux_sym__body,
    ACTIONS(61), 2,
      sym__line,
      sym__eol,
    ACTIONS(68), 2,
      sym__equals_begin,
      ts_builtin_sym_end,
  [207] = 1,
    ACTIONS(70), 4,
      sym__equals_begin,
      ts_builtin_sym_end,
      sym__line,
      sym__eol,
  [214] = 3,
    ACTIONS(74), 1,
      sym__dashes,
    STATE(17), 1,
      aux_sym__body,
    ACTIONS(72), 2,
      sym__line,
      sym__eol,
  [225] = 3,
    ACTIONS(63), 1,
      sym__dashes,
    STATE(17), 1,
      aux_sym__body,
    ACTIONS(76), 2,
      sym__line,
      sym__eol,
  [236] = 2,
    STATE(16), 1,
      aux_sym__body,
    ACTIONS(72), 2,
      sym__line,
      sym__eol,
  [244] = 1,
    ACTIONS(70), 3,
      sym__dashes,
      sym__line,
      sym__eol,
  [250] = 1,
    ACTIONS(79), 2,
      sym__line,
      sym__eol,
  [255] = 1,
    ACTIONS(81), 2,
      sym__line,
      sym__eol,
  [260] = 1,
    ACTIONS(83), 1,
      sym__equals_end,
  [264] = 1,
    ACTIONS(85), 1,
      sym__lang,
  [268] = 1,
    ACTIONS(87), 1,
      sym__os,
  [272] = 1,
    ACTIONS(89), 1,
      sym__line,
  [276] = 1,
    ACTIONS(91), 1,
      anon_sym_LPAREN,
  [280] = 1,
    ACTIONS(93), 1,
      anon_sym_RPAREN,
  [284] = 1,
    ACTIONS(95), 1,
      anon_sym_RPAREN,
  [288] = 1,
    ACTIONS(97), 1,
      anon_sym_LPAREN,
  [292] = 1,
    ACTIONS(99), 1,
      sym__eol,
  [296] = 1,
    ACTIONS(101), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 31,
  [SMALL_STATE(4)] = 59,
  [SMALL_STATE(5)] = 87,
  [SMALL_STATE(6)] = 97,
  [SMALL_STATE(7)] = 107,
  [SMALL_STATE(8)] = 117,
  [SMALL_STATE(9)] = 127,
  [SMALL_STATE(10)] = 137,
  [SMALL_STATE(11)] = 154,
  [SMALL_STATE(12)] = 171,
  [SMALL_STATE(13)] = 183,
  [SMALL_STATE(14)] = 195,
  [SMALL_STATE(15)] = 207,
  [SMALL_STATE(16)] = 214,
  [SMALL_STATE(17)] = 225,
  [SMALL_STATE(18)] = 236,
  [SMALL_STATE(19)] = 244,
  [SMALL_STATE(20)] = 250,
  [SMALL_STATE(21)] = 255,
  [SMALL_STATE(22)] = 260,
  [SMALL_STATE(23)] = 264,
  [SMALL_STATE(24)] = 268,
  [SMALL_STATE(25)] = 272,
  [SMALL_STATE(26)] = 276,
  [SMALL_STATE(27)] = 280,
  [SMALL_STATE(28)] = 284,
  [SMALL_STATE(29)] = 288,
  [SMALL_STATE(30)] = 292,
  [SMALL_STATE(31)] = 296,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [19] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attributes_repeat1, 2), SHIFT_REPEAT(7),
  [22] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attributes_repeat1, 2), SHIFT_REPEAT(29),
  [25] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attributes_repeat1, 2), SHIFT_REPEAT(26),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_attributes_repeat1, 2), SHIFT_REPEAT(3),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_attributes_repeat1, 2),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attributes, 1),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__platform, 4, .production_id = 7),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__language, 4, .production_id = 6),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute, 1),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute, 1, .production_id = 3),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_attribute, 1, .production_id = 4),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file, 1),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [51] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_file_repeat1, 2),
  [53] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_file_repeat1, 2), SHIFT_REPEAT(11),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_file_repeat1, 2), SHIFT_REPEAT(25),
  [59] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_test, 4, .production_id = 5),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__body, 2),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__body, 2), SHIFT_REPEAT(15),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_test, 3, .production_id = 1),
  [70] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__body, 1),
  [72] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [76] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__body, 2), SHIFT_REPEAT(19),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_header, 5, .production_id = 2),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_header, 4, .production_id = 2),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [101] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

enum ts_external_scanner_symbol_identifiers {
  ts_external_token__equals_begin = 0,
  ts_external_token__equals_end = 1,
  ts_external_token__dashes = 2,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token__equals_begin] = sym__equals_begin,
  [ts_external_token__equals_end] = sym__equals_end,
  [ts_external_token__dashes] = sym__dashes,
};

static const bool ts_external_scanner_states[5][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token__equals_begin] = true,
    [ts_external_token__equals_end] = true,
    [ts_external_token__dashes] = true,
  },
  [2] = {
    [ts_external_token__equals_begin] = true,
  },
  [3] = {
    [ts_external_token__equals_end] = true,
  },
  [4] = {
    [ts_external_token__dashes] = true,
  },
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_test_external_scanner_create(void);
void tree_sitter_test_external_scanner_destroy(void *);
bool tree_sitter_test_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_test_external_scanner_serialize(void *, char *);
void tree_sitter_test_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_test() {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_test_external_scanner_create,
      tree_sitter_test_external_scanner_destroy,
      tree_sitter_test_external_scanner_scan,
      tree_sitter_test_external_scanner_serialize,
      tree_sitter_test_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
