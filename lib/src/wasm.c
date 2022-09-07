#include <wasmtime.h>
#include <wasm.h>
#include "tree_sitter/api.h"
#include "./alloc.h"
#include "./language.h"
#include "./array.h"
#include "./atomic.h"
#include "./lexer.h"
#include "./wasm.h"
#include "./lexer.h"

typedef struct {
  wasmtime_module_t *module;
  uint32_t language_id;
  const char *name;
  char *symbol_name_buffer;
  char *field_name_buffer;
} LanguageWasmModule;

typedef struct {
  uint32_t language_id;
  wasmtime_instance_t instance;
  uint32_t main_lex_fn_index;
  uint32_t keyword_lex_fn_index;
  uint32_t external_scan_index;
} LanguageWasmInstance;

struct TSWasmStore {
  wasm_engine_t *engine;
  wasmtime_store_t *store;
  wasmtime_table_t function_table;
  wasmtime_memory_t memory;
  TSLexer *current_lexer;
  LanguageWasmInstance *current_instance;
  Array(LanguageWasmInstance) language_instances;
  uint32_t current_memory_offset;
  uint32_t current_function_table_offset;
};

typedef Array(char) StringData;

typedef struct {
  uint32_t version;
  uint32_t symbol_count;
  uint32_t alias_count;
  uint32_t token_count;
  uint32_t external_token_count;
  uint32_t state_count;
  uint32_t large_state_count;
  uint32_t production_id_count;
  uint32_t field_count;
  uint16_t max_alias_sequence_length;
  int32_t parse_table;
  int32_t small_parse_table;
  int32_t small_parse_table_map;
  int32_t parse_actions;
  int32_t symbol_names;
  int32_t field_names;
  int32_t field_map_slices;
  int32_t field_map_entries;
  int32_t symbol_metadata;
  int32_t public_symbol_map;
  int32_t alias_map;
  int32_t alias_sequences;
  int32_t lex_modes;
  int32_t lex_fn;
  int32_t keyword_lex_fn;
  TSSymbol keyword_capture_token;
  struct {
    int32_t states;
    int32_t symbol_map;
    int32_t create;
    int32_t destroy;
    int32_t scan;
    int32_t serialize;
    int32_t deserialize;
  } external_scanner;
  int32_t primary_state_ids;
} LanguageInWasmMemory;

typedef struct {
  int32_t lookahead;
  TSSymbol result_symbol;
  int32_t advance;
  int32_t mark_end;
  int32_t get_column;
  int32_t is_at_included_range_start;
  int32_t eof;
} LexerInWasmMemory;

static volatile uint32_t NEXT_LANGUAGE_ID;
static const uint32_t LEXER_ADDRESS = 32;
static const uint32_t LEXER_END_ADDRESS = LEXER_ADDRESS + sizeof(LexerInWasmMemory);

static wasm_trap_t *advance_callback(
  void *env,
  wasmtime_caller_t *caller,
  const wasmtime_val_t *args,
  size_t arg_count,
  wasmtime_val_t *results,
  size_t result_count
) {
  wasmtime_context_t *context = wasmtime_caller_context(caller);
  assert(arg_count == 2);
  assert(args[0].kind == WASMTIME_I32);
  assert(args[1].kind == WASMTIME_I32);
  int32_t lexer_address = args[0].of.i32;

  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  bool skip = args[1].of.i32;
  lexer->advance(lexer, skip);

  uint8_t *memory = wasmtime_memory_data(context, &store->memory);
  memcpy(&memory[lexer_address], &lexer->lookahead, sizeof(lexer->lookahead));
  return NULL;
}

static wasm_trap_t *mark_end_callback(
  void *env,
  wasmtime_caller_t *caller,
  const wasmtime_val_t *args,
  size_t arg_count,
  wasmtime_val_t *results,
  size_t result_count
) {
  assert(arg_count == 1);
  assert(args[0].kind == WASM_I32);
  int32_t lexer_address = args[0].of.i32;

  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  lexer->mark_end(lexer);
  return NULL;
}

static wasm_trap_t *get_column_callback(
  void *env,
  wasmtime_caller_t *caller,
  const wasmtime_val_t *args,
  size_t arg_count,
  wasmtime_val_t *results,
  size_t result_count
) {
  assert(arg_count == 1);
  assert(args[0].kind == WASM_I32);
  int32_t lexer_address = args[0].of.i32;

  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  uint32_t result = lexer->get_column(lexer);
  results[0] = (wasmtime_val_t) {
    .kind = WASMTIME_I32,
    .of.i32 = result
  };
  return NULL;
}

static wasm_trap_t *is_at_included_range_start_callback(
  void *env,
  wasmtime_caller_t *caller,
  const wasmtime_val_t *args,
  size_t arg_count,
  wasmtime_val_t *results,
  size_t result_count
) {
  assert(arg_count == 1);
  assert(args[0].kind == WASM_I32);
  int32_t lexer_address = args[0].of.i32;

  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  bool result = lexer->is_at_included_range_start(lexer);
  results[0] = (wasmtime_val_t) {
    .kind = WASMTIME_I32,
    .of.i32 = result
  };
  return NULL;
}

static wasm_trap_t *eof_callback(
  void *env,
  wasmtime_caller_t *caller,
  const wasmtime_val_t *args,
  size_t arg_count,
  wasmtime_val_t *results,
  size_t result_count
) {
  assert(arg_count == 1);
  assert(args[0].kind == WASM_I32);
  int32_t lexer_address = args[0].of.i32;

  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  bool result = lexer->eof(lexer);

  results[0] = (wasmtime_val_t) {
    .kind = WASMTIME_I32,
    .of.i32 = result
  };
  return NULL;
}

typedef struct {
  wasmtime_func_callback_t callback;
  wasm_functype_t *type;
} FunctionDefinition;

#define array_len(a) (sizeof(a) / sizeof(a[0]))

static void *copy(const void *data, size_t size) {
  void *result = ts_malloc(size);
  memcpy(result, data, size);
  return result;
}

static void *copy_strings(
  const uint8_t *data,
  int32_t array_address,
  size_t count,
  StringData *string_data
) {
  const char **result = ts_malloc(count * sizeof(char *));
  for (unsigned i = 0; i < count; i++) {
    int32_t address;
    memcpy(&address, &data[array_address + i * sizeof(address)], sizeof(address));
    if (address == 0) {
      result[i] = (const char *)-1;
    } else {
      const uint8_t *string = &data[address];
      uint32_t len = strlen((const char *)string);
      result[i] = (const char *)(uintptr_t)string_data->size;
      array_extend(string_data, len + 1, string);
    }
  }
  for (unsigned i = 0; i < count; i++) {
    if (result[i] == (const char *)-1) {
      result[i] = NULL;
    } else {
      result[i] = string_data->contents + (uintptr_t)result[i];
    }
    printf("  string %u: %s\n", i, result[i]);
  }
  return result;
}

static bool name_eq(const wasm_name_t *name, const char *string) {
  return strncmp(string, name->data, name->size) == 0;
}

TSWasmStore *ts_wasm_store_new(TSWasmEngine *engine) {
  TSWasmStore *self = ts_malloc(sizeof(TSWasmStore));
  wasmtime_store_t *store = wasmtime_store_new(engine, self, NULL);
  wasmtime_context_t *context = wasmtime_store_context(store);
  wasmtime_error_t *error = NULL;

  // Initialize store's memory
  wasm_limits_t memory_limits = {.min = LEXER_END_ADDRESS, .max = wasm_limits_max_default};
  wasm_memorytype_t *memory_type = wasm_memorytype_new(&memory_limits);
  wasmtime_memory_t memory;
  error = wasmtime_memory_new(context, memory_type, &memory);
  assert(!error);
  wasm_memorytype_delete(memory_type);

  // Initialize lexer struct with function pointers in wasm memory.
  uint8_t *memory_data = wasmtime_memory_data(context, &memory);
  LexerInWasmMemory lexer = {
    .lookahead = 0,
    .result_symbol = 0,
    .advance = 0,
    .mark_end = 1,
    .get_column = 2,
    .is_at_included_range_start = 3,
    .eof = 4,
  };
  memcpy(&memory_data[LEXER_ADDRESS], &lexer, sizeof(lexer));

  // Define lexer functions.
  FunctionDefinition definitions[] = {
    {advance_callback, wasm_functype_new_2_0(wasm_valtype_new_i32(), wasm_valtype_new_i32())},
    {mark_end_callback, wasm_functype_new_1_0(wasm_valtype_new_i32())},
    {get_column_callback, wasm_functype_new_1_1(wasm_valtype_new_i32(), wasm_valtype_new_i32())},
    {is_at_included_range_start_callback, wasm_functype_new_1_1(wasm_valtype_new_i32(), wasm_valtype_new_i32())},
    {eof_callback, wasm_functype_new_1_1(wasm_valtype_new_i32(), wasm_valtype_new_i32())},
  };
  unsigned definitions_len = array_len(definitions);

  // Add lexer functions to the store's function table.
  wasmtime_table_t function_table;
  wasm_limits_t table_limits = {.min = definitions_len, .max = wasm_limits_max_default};
  wasm_tabletype_t *table_type = wasm_tabletype_new(wasm_valtype_new(WASM_FUNCREF), &table_limits);
  wasmtime_val_t initializer = {.kind = WASMTIME_FUNCREF};
  error = wasmtime_table_new(context, table_type, &initializer, &function_table);
  assert(!error);
  wasm_tabletype_delete(table_type);

  uint32_t prev_size;
  error = wasmtime_table_grow(context, &function_table, definitions_len, &initializer, &prev_size);
  assert(!error);
  for (unsigned i = 0; i < definitions_len; i++) {
    FunctionDefinition *definition = &definitions[i];
    wasmtime_func_t func;
    wasmtime_func_new(context, definition->type, definition->callback, self, NULL, &func);
    wasmtime_val_t func_val = {.kind = WASMTIME_FUNCREF, .of.funcref = func};
    error = wasmtime_table_set(context, &function_table, i, &func_val);
    assert(!error);
    wasm_functype_delete(definition->type);
  }

  *self = (TSWasmStore) {
    .store = store,
    .engine = engine,
    .memory = memory,
    .language_instances = array_new(),
    .function_table = function_table,
    .current_memory_offset = LEXER_END_ADDRESS,
    .current_function_table_offset = definitions_len,
  };
  return self;
}

void ts_wasm_store_delete(TSWasmStore *self) {
  wasmtime_store_delete(self->store);
  wasm_engine_delete(self->engine);
  array_delete(&self->language_instances);
  ts_free(self);
}

static bool ts_wasm_store__instantiate(
  TSWasmStore *self,
  wasmtime_module_t *module,
  const char *language_name,
  wasmtime_instance_t *result,
  int32_t *language_address
) {
  wasmtime_context_t *context = wasmtime_store_context(self->store);
  wasmtime_error_t *error = NULL;
  wasm_trap_t *trap = NULL;

  // Construct the language function name as string.
  unsigned prefix_len = strlen("tree_sitter_");
  unsigned name_len = strlen(language_name);
  char language_function_name[prefix_len + name_len + 1];
  memcpy(&language_function_name[0], "tree_sitter_", prefix_len);
  memcpy(&language_function_name[prefix_len], language_name, name_len);
  language_function_name[prefix_len + name_len] = '\0';

  // Construct globals representing the offset in memory and in the function
  // table where the module should be added.
  wasmtime_val_t table_base_val = WASM_I32_VAL(self->current_function_table_offset);
  wasmtime_val_t memory_base_val = WASM_I32_VAL(self->current_memory_offset);
  wasmtime_global_t memory_base_global;
  wasmtime_global_t table_base_global;
  wasm_globaltype_t *const_i32_type = wasm_globaltype_new(wasm_valtype_new_i32(), WASM_CONST);
  error = wasmtime_global_new(context, const_i32_type, &memory_base_val, &memory_base_global);
  assert(!error);
  error = wasmtime_global_new(context, const_i32_type, &table_base_val, &table_base_global);
  assert(!error);
  wasm_globaltype_delete(const_i32_type);

  // Build the imports list for the module.
  wasm_importtype_vec_t import_types = WASM_EMPTY_VEC;
  wasmtime_module_imports(module, &import_types);
  wasmtime_extern_t imports[import_types.size];
  for (unsigned i = 0; i < import_types.size; i++) {
    const wasm_importtype_t *import_type = import_types.data[i];
    const wasm_name_t *import_name = wasm_importtype_name(import_type);

    if (name_eq(import_name, "__memory_base")) {
      imports[i] = (wasmtime_extern_t) {.kind = WASMTIME_EXTERN_GLOBAL, .of.global = memory_base_global};
    } else if (name_eq(import_name, "__table_base")) {
      imports[i] = (wasmtime_extern_t) {.kind = WASMTIME_EXTERN_GLOBAL, .of.global = table_base_global};
    } else if (name_eq(import_name, "memory")) {
      imports[i] = (wasmtime_extern_t) {.kind = WASMTIME_EXTERN_MEMORY, .of.memory = self->memory};
    } else if (name_eq(import_name, "__indirect_function_table")) {
      imports[i] = (wasmtime_extern_t) {.kind = WASMTIME_EXTERN_TABLE, .of.table = self->function_table};
    } else {
      printf("unexpected import '%.*s'\n", (int)import_name->size, import_name->data);
      return false;
    }
  }
  wasm_importtype_vec_delete(&import_types);

  wasmtime_instance_t instance;
  error = wasmtime_instance_new(context, module, imports, 4, &instance, &trap);
  assert(!error);
  if (trap) {
    wasm_message_t message;
    wasm_trap_message(trap, &message);
    printf("error instantiating wasm module: %s\n", message.data);
    return false;
  }

  // Process the module's exports.
  wasmtime_extern_t language_extern;
  wasm_exporttype_vec_t export_types = WASM_EMPTY_VEC;
  wasmtime_module_exports(module, &export_types);
  for (unsigned i = 0; i < export_types.size; i++) {
    wasm_exporttype_t *export_type = export_types.data[i];
    const wasm_name_t *name = wasm_exporttype_name(export_type);

    char *export_name;
    size_t name_len;
    wasmtime_extern_t export = {.kind = WASM_EXTERN_GLOBAL};
    bool exists = wasmtime_instance_export_nth(context, &instance, i, &export_name, &name_len, &export);
    assert(exists);

    // Update pointers to reflect memory and function table offsets.
    if (name_eq(name, "__wasm_apply_data_relocs")) {
      wasmtime_func_t apply_relocation_func = export.of.func;
      error = wasmtime_func_call(context, &apply_relocation_func, NULL, 0, NULL, 0, &trap);
      assert(!error);
      if (trap) {
        wasm_message_t message;
        wasm_trap_message(trap, &message);
        printf("error calling relocation function: %s\n", message.data);
        abort();
      }
    }

    // Find the main language function for the module.
    else if (name_eq(name, language_function_name)) {
      language_extern = export;
    }
  }
  wasm_exporttype_vec_delete(&export_types);

  if (language_extern.kind != WASMTIME_EXTERN_FUNC) {
    printf("failed to find function %s\n", language_function_name);
    return false;
  }

  // Invoke the language function to get the static address of the language object.
  wasmtime_func_t language_func = language_extern.of.func;
  wasmtime_val_t language_address_val;
  error = wasmtime_func_call(context, &language_func, NULL, 0, &language_address_val, 1, &trap);
  assert(!error);
  if (trap) {
    wasm_message_t message;
    wasm_trap_message(trap, &message);
    printf("error calling language function: %s\n", message.data);
    return false;
  }

  assert(language_address_val.kind == WASMTIME_I32);
  *result = instance;
  *language_address = language_address_val.of.i32;
  return true;
}

static bool ts_wasm_store__sentinel_lex_fn(TSLexer *_lexer, TSStateId state) {
  return false;
}

const TSLanguage *ts_wasm_store_load_language(
  TSWasmStore *self,
  const char *language_name,
  const char *wasm,
  uint32_t wasm_len
) {
  // Compile the wasm code.
  wasmtime_module_t *module;
  wasmtime_error_t *error = wasmtime_module_new(self->engine, (const uint8_t *)wasm, wasm_len, &module);
  if (error) {
    wasm_message_t message;
    wasmtime_error_message(error, &message);
    printf("failed to load wasm language: %s", message.data);
    return NULL;
  }

  // Instantiate the module in this store.
  wasmtime_instance_t instance;
  int32_t language_address;
  if (!ts_wasm_store__instantiate(
    self,
    module,
    language_name,
    &instance,
    &language_address
  )) return NULL;

  // Copy all of the static data out of the language object in wasm memory,
  // constructing a native language object.
  LanguageInWasmMemory wasm_language;
  wasmtime_context_t *context = wasmtime_store_context(self->store);
  const uint8_t *memory = wasmtime_memory_data(context, &self->memory);
  memcpy(&wasm_language, &memory[language_address], sizeof(LanguageInWasmMemory));

  TSLanguage *language = ts_malloc(sizeof(TSLanguage));
  StringData symbol_name_buffer = array_new();
  StringData field_name_buffer = array_new();

  *language = (TSLanguage) {
    .version = wasm_language.version,
    .symbol_count = wasm_language.symbol_count,
    .alias_count = wasm_language.alias_count,
    .token_count = wasm_language.token_count,
    .external_token_count = wasm_language.external_token_count,
    .state_count = wasm_language.state_count,
    .large_state_count = wasm_language.large_state_count,
    .production_id_count = wasm_language.production_id_count,
    .field_count = wasm_language.field_count,
    .max_alias_sequence_length = wasm_language.max_alias_sequence_length,
    .keyword_capture_token = wasm_language.keyword_capture_token,
    .parse_table = copy(
      &memory[wasm_language.parse_table],
      wasm_language.large_state_count * wasm_language.symbol_count * sizeof(uint16_t)
    ),
    .parse_actions = copy(
      &memory[wasm_language.parse_actions],
      2800 * sizeof(TSParseActionEntry) // TODO - determine number of parse actions
    ),
    .symbol_names = copy_strings(
      memory,
      wasm_language.symbol_names,
      wasm_language.symbol_count + wasm_language.alias_count,
      &symbol_name_buffer
    ),
    .symbol_metadata = copy(
      &memory[wasm_language.symbol_metadata],
      wasm_language.symbol_count * sizeof(TSSymbolMetadata)
    ),
    .public_symbol_map = copy(
      &memory[wasm_language.public_symbol_map],
      wasm_language.symbol_count * sizeof(TSSymbol)
    ),
    .lex_modes = copy(
      &memory[wasm_language.lex_modes],
      wasm_language.state_count * sizeof(TSLexMode)
    ),
  };

  if (language->field_count > 0 && language->production_id_count > 0) {
    language->field_map_slices = copy(
      &memory[wasm_language.field_map_slices],
      wasm_language.production_id_count * sizeof(TSFieldMapSlice)
    );
    const TSFieldMapSlice last_field_map_slice = language->field_map_slices[language->production_id_count - 1];
    language->field_map_entries = copy(
      &memory[wasm_language.field_map_entries],
      (last_field_map_slice.index + last_field_map_slice.length) * sizeof(TSFieldMapEntry)
    );
    language->field_names = copy_strings(
      memory,
      wasm_language.field_names,
      wasm_language.field_count + 1,
      &field_name_buffer
    );
  }

  if (language->alias_count > 0 && language->production_id_count > 0) {
    // The alias map contains symbols, alias counts, and aliases, terminated by a null symbol.
    int32_t alias_map_size = 0;
    for (;;) {
      TSSymbol symbol;
      memcpy(&symbol, &memory[wasm_language.alias_map + alias_map_size], sizeof(symbol));
      alias_map_size += sizeof(TSSymbol);
      if (symbol == 0) break;
      uint16_t value_count;
      memcpy(&value_count, &memory[wasm_language.alias_map + alias_map_size], sizeof(value_count));
      alias_map_size += value_count * sizeof(TSSymbol);
    }
    language->alias_map = copy(
      &memory[wasm_language.alias_map],
      alias_map_size * sizeof(TSSymbol)
    );
    language->alias_sequences = copy(
      &memory[wasm_language.alias_sequences],
      wasm_language.production_id_count * wasm_language.max_alias_sequence_length * sizeof(TSSymbol)
    );
  }

  if (language->state_count > language->large_state_count) {
    uint32_t small_state_count = wasm_language.state_count - wasm_language.large_state_count;
    language->small_parse_table_map = copy(
      &memory[wasm_language.small_parse_table_map],
      small_state_count * sizeof(uint32_t)
    );
    uint32_t index = language->small_parse_table_map[small_state_count - 1];
    language->small_parse_table = copy(
      &memory[wasm_language.small_parse_table],
      (index + 64) * sizeof(uint16_t) // TODO - determine actual size
    );
  }

  unsigned name_len = strlen(language_name);
  char *name = ts_malloc(name_len + 1);
  memcpy(name, language_name, name_len);
  name[name_len] = '\0';

  LanguageWasmModule *language_module = ts_malloc(sizeof(LanguageWasmModule));
  *language_module = (LanguageWasmModule) {
    .language_id = atomic_inc(&NEXT_LANGUAGE_ID),
    .module = module,
    .name = name,
    .symbol_name_buffer = symbol_name_buffer.contents,
    .field_name_buffer = field_name_buffer.contents,
  };

  // The lex functions are not used for wasm languages. Use those two fields
  // to mark this language as WASM-based and to store the language's
  // WASM-specific data.
  language->lex_fn = ts_wasm_store__sentinel_lex_fn;
  language->keyword_lex_fn = (void *)language_module;

  // Store some information about this store's specific instance of this
  // language module, keyed by the language's id.
  array_push(&self->language_instances, ((LanguageWasmInstance) {
    .language_id = language_module->language_id,
    .instance = instance,
    .main_lex_fn_index = wasm_language.lex_fn,
    .keyword_lex_fn_index = wasm_language.keyword_lex_fn,
  }));

  return language;
}

bool ts_wasm_store_start(TSWasmStore *self, TSLexer *lexer, const TSLanguage *language) {
  if (!ts_language_is_wasm(language)) return false;
  wasmtime_context_t *context = wasmtime_store_context(self->store);
  const LanguageWasmModule *language_module = (void *)language->keyword_lex_fn;

  // Search for the information about this store's instance of the language module.
  uint32_t instance_index = 0;
  bool exists = false;
  array_search_sorted_by(
    &self->language_instances,
    .language_id,
    language_module->language_id,
    &instance_index,
    &exists
  );

  // If the language module has not been instantiated in this store, then add
  // it to this store.
  if (!exists) {
    wasmtime_instance_t instance;
    int32_t language_address;
    if (!ts_wasm_store__instantiate(
      self,
      language_module->module,
      language_module->name,
      &instance,
      &language_address
    )) {
      return false;
    }

    LanguageInWasmMemory wasm_language;
    const uint8_t *memory = wasmtime_memory_data(context, &self->memory);
    memcpy(&wasm_language, &memory[language_address], sizeof(LanguageInWasmMemory));
    array_insert(&self->language_instances, instance_index, ((LanguageWasmInstance) {
      .language_id = language_module->language_id,
      .instance = instance,
      .main_lex_fn_index = wasm_language.lex_fn,
      .keyword_lex_fn_index = wasm_language.keyword_lex_fn,
    }));
  }

  self->current_lexer = lexer;
  self->current_instance = &self->language_instances.contents[instance_index];
  return true;
}

void ts_wasm_store_stop(TSWasmStore *self) {
  self->current_lexer = NULL;
  self->current_instance = NULL;
}

bool ts_wasm_store_run_lex_function(TSWasmStore *self, TSStateId state, unsigned function_index) {
  wasmtime_context_t *context = wasmtime_store_context(self->store);

  uint8_t *memory_data = wasmtime_memory_data(context, &self->memory);
  memcpy(
    &memory_data[LEXER_ADDRESS],
    &self->current_lexer->lookahead,
    sizeof(self->current_lexer->lookahead)
  );

  wasmtime_val_t lex_val;
  bool succeeded = wasmtime_table_get(context, &self->function_table, function_index, &lex_val);
  assert(succeeded);
  assert(lex_val.kind == WASMTIME_FUNCREF);
  wasmtime_func_t lex_func = lex_val.of.funcref;

  const wasmtime_val_t args[2] = {
    {.kind = WASMTIME_I32, .of.i32 = LEXER_ADDRESS},
    {.kind = WASMTIME_I32, .of.i32 = state},
  };
  wasmtime_val_t results[1] = {
    {.kind = WASMTIME_I32, .of.i32 = 0}
  };

  wasm_trap_t *trap = NULL;
  wasmtime_func_call(context, &lex_func, args, 2, results, 1, &trap);
  if (trap) {
    wasm_message_t message;
    wasm_trap_message(trap, &message);
    printf("error calling lex function index %u: %s\n", function_index, message.data);
    abort();
  }
  assert(results[0].kind == WASM_I32);

  memcpy(
    &self->current_lexer->lookahead,
    &memory_data[LEXER_ADDRESS],
    sizeof(self->current_lexer->lookahead) + sizeof(self->current_lexer->result_symbol)
  );
  return results[0].of.i32;
}

bool ts_wasm_store_run_main_lex_function(TSWasmStore *self, TSStateId state) {
  return ts_wasm_store_run_lex_function(
    self,
    state,
    self->current_instance->main_lex_fn_index
  );
}

bool ts_wasm_store_run_keyword_lex_function(TSWasmStore *self, TSStateId state) {
  return ts_wasm_store_run_lex_function(
    self,
    state,
    self->current_instance->keyword_lex_fn_index
  );
}

bool ts_language_is_wasm(const TSLanguage *self) {
  return self->lex_fn == ts_wasm_store__sentinel_lex_fn;
}