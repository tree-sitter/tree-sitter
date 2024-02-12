/**
 * \file wasmtime/engine.h
 *
 * Wasmtime-specific extensions to #wasm_engine_t.
 */

#ifndef WASMTIME_ENGINE_H
#define WASMTIME_ENGINE_H

#include <wasm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Increments the engine-local epoch variable.
 *
 * This function will increment the engine's current epoch which can be used to
 * force WebAssembly code to trap if the current epoch goes beyond the
 * #wasmtime_store_t configured epoch deadline.
 *
 * This function is safe to call from any thread, and it is also
 * async-signal-safe.
 *
 * See also #wasmtime_config_epoch_interruption_set.
 */
WASM_API_EXTERN void wasmtime_engine_increment_epoch(wasm_engine_t *engine);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif // WASMTIME_ENGINE_H


