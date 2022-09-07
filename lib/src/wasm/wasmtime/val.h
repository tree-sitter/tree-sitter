/**
 * \file wasmtime/val.h
 *
 * APIs for interacting with WebAssembly values in Wasmtime.
 */

#ifndef WASMTIME_VAL_H
#define WASMTIME_VAL_H

#include <wasm.h>
#include <wasmtime/extern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \typedef wasmtime_externref_t
 * \brief Convenience alias for #wasmtime_externref
 *
 * \struct wasmtime_externref
 * \brief A host-defined un-forgeable reference to pass into WebAssembly.
 *
 * This structure represents an `externref` that can be passed to WebAssembly.
 * It cannot be forged by WebAssembly itself and is guaranteed to have been
 * created by the host.
 */
typedef struct wasmtime_externref wasmtime_externref_t;

/**
 * \brief Create a new `externref` value.
 *
 * Creates a new `externref` value wrapping the provided data, returning the
 * pointer to the externref.
 *
 * \param data the host-specific data to wrap
 * \param finalizer an optional finalizer for `data`
 *
 * When the reference is reclaimed, the wrapped data is cleaned up with the
 * provided `finalizer`.
 *
 * The returned value must be deleted with #wasmtime_externref_delete
 */
WASM_API_EXTERN wasmtime_externref_t *wasmtime_externref_new(void *data, void (*finalizer)(void*));

/**
 * \brief Get an `externref`'s wrapped data
 *
 * Returns the original `data` passed to #wasmtime_externref_new. It is required
 * that `data` is not `NULL`.
 */
WASM_API_EXTERN void *wasmtime_externref_data(wasmtime_externref_t *data);

/**
 * \brief Creates a shallow copy of the `externref` argument, returning a
 * separately owned pointer (increases the reference count).
 */
WASM_API_EXTERN wasmtime_externref_t *wasmtime_externref_clone(wasmtime_externref_t *ref);

/**
 * \brief Decrements the reference count of the `ref`, deleting it if it's the
 * last reference.
 */
WASM_API_EXTERN void wasmtime_externref_delete(wasmtime_externref_t *ref);

/**
 * \brief Converts a raw `externref` value coming from #wasmtime_val_raw_t into
 * a #wasmtime_externref_t.
 *
 * Note that the returned #wasmtime_externref_t is an owned value that must be
 * deleted via #wasmtime_externref_delete by the caller if it is non-null.
 */
WASM_API_EXTERN wasmtime_externref_t *wasmtime_externref_from_raw(wasmtime_context_t *context, size_t raw);

/**
 * \brief Converts a #wasmtime_externref_t to a raw value suitable for storing
 * into a #wasmtime_val_raw_t.
 *
 * Note that the returned underlying value is not tracked by Wasmtime's garbage
 * collector until it enters WebAssembly. This means that a GC may release the
 * context's reference to the raw value, making the raw value invalid within the
 * context of the store. Do not perform a GC between calling this function and
 * passing it to WebAssembly.
 */
WASM_API_EXTERN size_t wasmtime_externref_to_raw(
    wasmtime_context_t *context,
    const wasmtime_externref_t *ref);

/// \brief Discriminant stored in #wasmtime_val::kind
typedef uint8_t wasmtime_valkind_t;
/// \brief Value of #wasmtime_valkind_t meaning that #wasmtime_val_t is an i32
#define WASMTIME_I32 0
/// \brief Value of #wasmtime_valkind_t meaning that #wasmtime_val_t is an i64
#define WASMTIME_I64 1
/// \brief Value of #wasmtime_valkind_t meaning that #wasmtime_val_t is a f32
#define WASMTIME_F32 2
/// \brief Value of #wasmtime_valkind_t meaning that #wasmtime_val_t is a f64
#define WASMTIME_F64 3
/// \brief Value of #wasmtime_valkind_t meaning that #wasmtime_val_t is a v128
#define WASMTIME_V128 4
/// \brief Value of #wasmtime_valkind_t meaning that #wasmtime_val_t is a funcref
#define WASMTIME_FUNCREF 5
/// \brief Value of #wasmtime_valkind_t meaning that #wasmtime_val_t is an externref
#define WASMTIME_EXTERNREF 6

/// \brief A 128-bit value representing the WebAssembly `v128` type. Bytes are
/// stored in little-endian order.
typedef uint8_t wasmtime_v128[16];

/**
 * \typedef wasmtime_valunion_t
 * \brief Convenience alias for #wasmtime_valunion
 *
 * \union wasmtime_valunion
 * \brief Container for different kinds of wasm values.
 *
 * This type is contained in #wasmtime_val_t and contains the payload for the
 * various kinds of items a value can be.
 */
typedef union wasmtime_valunion {
  /// Field used if #wasmtime_val_t::kind is #WASMTIME_I32
  ///
  /// Note that this field is always stored in a little-endian format.
  int32_t i32;
  /// Field used if #wasmtime_val_t::kind is #WASMTIME_I64
  ///
  /// Note that this field is always stored in a little-endian format.
  int64_t i64;
  /// Field used if #wasmtime_val_t::kind is #WASMTIME_F32
  ///
  /// Note that this field is always stored in a little-endian format.
  float32_t f32;
  /// Field used if #wasmtime_val_t::kind is #WASMTIME_F64
  ///
  /// Note that this field is always stored in a little-endian format.
  float64_t f64;
  /// Field used if #wasmtime_val_t::kind is #WASMTIME_FUNCREF
  ///
  /// If this value represents a `ref.null func` value then the `store_id` field
  /// is set to zero.
  ///
  /// Note that this field is always stored in a little-endian format.
  wasmtime_func_t funcref;
  /// Field used if #wasmtime_val_t::kind is #WASMTIME_EXTERNREF
  ///
  /// If this value represents a `ref.null extern` value then this pointer will
  /// be `NULL`.
  ///
  /// Note that this field is always stored in a little-endian format.
  wasmtime_externref_t *externref;
  /// Field used if #wasmtime_val_t::kind is #WASMTIME_V128
  ///
  /// Note that this field is always stored in a little-endian format.
  wasmtime_v128 v128;
} wasmtime_valunion_t;

/**
 * \typedef wasmtime_val_raw_t
 * \brief Convenience alias for #wasmtime_val_raw
 *
 * \union wasmtime_val_raw
 * \brief Container for possible wasm values.
 *
 * This type is used on conjunction with #wasmtime_func_new_unchecked as well
 * as #wasmtime_func_call_unchecked. Instances of this type do not have type
 * information associated with them, it's up to the embedder to figure out
 * how to interpret the bits contained within, often using some other channel
 * to determine the type.
 */
typedef union wasmtime_val_raw {
  /// Field for when this val is a WebAssembly `i32` value.
  int32_t i32;
  /// Field for when this val is a WebAssembly `i64` value.
  int64_t i64;
  /// Field for when this val is a WebAssembly `f32` value.
  float32_t f32;
  /// Field for when this val is a WebAssembly `f64` value.
  float64_t f64;
  /// Field for when this val is a WebAssembly `v128` value.
  wasmtime_v128 v128;
  /// Field for when this val is a WebAssembly `funcref` value.
  ///
  /// If this is set to 0 then it's a null funcref, otherwise this must be
  /// passed to `wasmtime_func_from_raw` to determine the `wasmtime_func_t`.
  size_t funcref;
  /// Field for when this val is a WebAssembly `externref` value.
  ///
  /// If this is set to 0 then it's a null externref, otherwise this must be
  /// passed to `wasmtime_externref_from_raw` to determine the
  /// `wasmtime_externref_t`.
  size_t externref;
} wasmtime_val_raw_t;

/**
 * \typedef wasmtime_val_t
 * \brief Convenience alias for #wasmtime_val_t
 *
 * \union wasmtime_val
 * \brief Container for different kinds of wasm values.
 *
 * Note that this structure may contain an owned value, namely
 * #wasmtime_externref_t, depending on the context in which this is used. APIs
 * which consume a #wasmtime_val_t do not take ownership, but APIs that return
 * #wasmtime_val_t require that #wasmtime_val_delete is called to deallocate
 * the value.
 */
typedef struct wasmtime_val {
  /// Discriminant of which field of #of is valid.
  wasmtime_valkind_t kind;
  /// Container for the extern item's value.
  wasmtime_valunion_t of;
} wasmtime_val_t;

/**
 * \brief Delets an owned #wasmtime_val_t.
 *
 * Note that this only deletes the contents, not the memory that `val` points to
 * itself (which is owned by the caller).
 */
WASM_API_EXTERN void wasmtime_val_delete(wasmtime_val_t *val);

/**
 * \brief Copies `src` into `dst`.
 */
WASM_API_EXTERN void wasmtime_val_copy(wasmtime_val_t *dst, const wasmtime_val_t *src);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif // WASMTIME_VAL_H

