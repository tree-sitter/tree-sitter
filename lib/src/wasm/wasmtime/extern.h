/**
 * \file wasmtime/extern.h
 *
 * \brief Definition of #wasmtime_extern_t and external items.
 */

#ifndef WASMTIME_EXTERN_H
#define WASMTIME_EXTERN_H

#include <wasmtime/module.h>
#include <wasmtime/store.h>

#ifdef __cplusplus
extern "C" {
#endif

/// \brief Representation of a function in Wasmtime.
///
/// Functions are represented with a 64-bit identifying integer in Wasmtime.
/// They do not have any destructor associated with them. Functions cannot
/// interoperate between #wasmtime_store_t instances and if the wrong function
/// is passed to the wrong store then it may trigger an assertion to abort the
/// process.
typedef struct wasmtime_func {
  /// Internal identifier of what store this belongs to, never zero.
  uint64_t store_id;
  /// Internal index within the store.
  size_t index;
} wasmtime_func_t;

/// \brief Representation of a table in Wasmtime.
///
/// Tables are represented with a 64-bit identifying integer in Wasmtime.
/// They do not have any destructor associated with them. Tables cannot
/// interoperate between #wasmtime_store_t instances and if the wrong table
/// is passed to the wrong store then it may trigger an assertion to abort the
/// process.
typedef struct wasmtime_table {
  /// Internal identifier of what store this belongs to, never zero.
  uint64_t store_id;
  /// Internal index within the store.
  size_t index;
} wasmtime_table_t;

/// \brief Representation of a memory in Wasmtime.
///
/// Memories are represented with a 64-bit identifying integer in Wasmtime.
/// They do not have any destructor associated with them. Memories cannot
/// interoperate between #wasmtime_store_t instances and if the wrong memory
/// is passed to the wrong store then it may trigger an assertion to abort the
/// process.
typedef struct wasmtime_memory {
  /// Internal identifier of what store this belongs to, never zero.
  uint64_t store_id;
  /// Internal index within the store.
  size_t index;
} wasmtime_memory_t;

/// \brief Representation of a global in Wasmtime.
///
/// Globals are represented with a 64-bit identifying integer in Wasmtime.
/// They do not have any destructor associated with them. Globals cannot
/// interoperate between #wasmtime_store_t instances and if the wrong global
/// is passed to the wrong store then it may trigger an assertion to abort the
/// process.
typedef struct wasmtime_global {
  /// Internal identifier of what store this belongs to, never zero.
  uint64_t store_id;
  /// Internal index within the store.
  size_t index;
} wasmtime_global_t;

/// \brief Discriminant of #wasmtime_extern_t
typedef uint8_t wasmtime_extern_kind_t;

/// \brief Value of #wasmtime_extern_kind_t meaning that #wasmtime_extern_t is a
/// function
#define WASMTIME_EXTERN_FUNC 0
/// \brief Value of #wasmtime_extern_kind_t meaning that #wasmtime_extern_t is a
/// global
#define WASMTIME_EXTERN_GLOBAL 1
/// \brief Value of #wasmtime_extern_kind_t meaning that #wasmtime_extern_t is a
/// table
#define WASMTIME_EXTERN_TABLE 2
/// \brief Value of #wasmtime_extern_kind_t meaning that #wasmtime_extern_t is a
/// memory
#define WASMTIME_EXTERN_MEMORY 3

/**
 * \typedef wasmtime_extern_union_t
 * \brief Convenience alias for #wasmtime_extern_union
 *
 * \union wasmtime_extern_union
 * \brief Container for different kinds of extern items.
 *
 * This type is contained in #wasmtime_extern_t and contains the payload for the
 * various kinds of items an extern wasm item can be.
 */
typedef union wasmtime_extern_union {
    /// Field used if #wasmtime_extern_t::kind is #WASMTIME_EXTERN_FUNC
    wasmtime_func_t func;
    /// Field used if #wasmtime_extern_t::kind is #WASMTIME_EXTERN_GLOBAL
    wasmtime_global_t global;
    /// Field used if #wasmtime_extern_t::kind is #WASMTIME_EXTERN_TABLE
    wasmtime_table_t table;
    /// Field used if #wasmtime_extern_t::kind is #WASMTIME_EXTERN_MEMORY
    wasmtime_memory_t memory;
} wasmtime_extern_union_t;

/**
 * \typedef wasmtime_extern_t
 * \brief Convenience alias for #wasmtime_extern_t
 *
 * \union wasmtime_extern
 * \brief Container for different kinds of extern items.
 *
 * Note that this structure may contain an owned value, namely
 * #wasmtime_module_t, depending on the context in which this is used. APIs
 * which consume a #wasmtime_extern_t do not take ownership, but APIs that
 * return #wasmtime_extern_t require that #wasmtime_extern_delete is called to
 * deallocate the value.
 */
typedef struct wasmtime_extern {
    /// Discriminant of which field of #of is valid.
    wasmtime_extern_kind_t kind;
    /// Container for the extern item's value.
    wasmtime_extern_union_t of;
} wasmtime_extern_t;

/// \brief Deletes a #wasmtime_extern_t.
void wasmtime_extern_delete(wasmtime_extern_t *val);

/// \brief Returns the type of the #wasmtime_extern_t defined within the given
/// store.
///
/// Does not take ownership of `context` or `val`, but the returned
/// #wasm_externtype_t is an owned value that needs to be deleted.
wasm_externtype_t *wasmtime_extern_type(wasmtime_context_t *context, wasmtime_extern_t *val);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif // WASMTIME_EXTERN_H

