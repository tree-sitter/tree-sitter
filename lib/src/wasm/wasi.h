/**
 * \file wasi.h
 *
 * C API for WASI
 */

#ifndef WASI_H
#define WASI_H

#include "wasm.h"

#ifndef WASI_API_EXTERN
#ifdef _WIN32
#define WASI_API_EXTERN __declspec(dllimport)
#else
#define WASI_API_EXTERN
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define own

#define WASI_DECLARE_OWN(name) \
  typedef struct wasi_##name##_t wasi_##name##_t; \
  WASI_API_EXTERN void wasi_##name##_delete(own wasi_##name##_t*);

/**
 * \typedef wasi_config_t
 * \brief Convenience alias for #wasi_config_t
 *
 * \struct wasi_config_t
 * \brief TODO
 *
 * \fn void wasi_config_delete(wasi_config_t *);
 * \brief Deletes a configuration object.
 */
WASI_DECLARE_OWN(config)

/**
 * \brief Creates a new empty configuration object.
 *
 * The caller is expected to deallocate the returned configuration
 */
WASI_API_EXTERN own wasi_config_t* wasi_config_new();

/**
 * \brief Sets the argv list for this configuration object.
 *
 * By default WASI programs have an empty argv list, but this can be used to
 * explicitly specify what the argv list for the program is.
 *
 * The arguments are copied into the `config` object as part of this function
 * call, so the `argv` pointer only needs to stay alive for this function call.
 */
WASI_API_EXTERN void wasi_config_set_argv(wasi_config_t* config, int argc, const char* argv[]);

/**
 * \brief Indicates that the argv list should be inherited from this process's
 * argv list.
 */
WASI_API_EXTERN void wasi_config_inherit_argv(wasi_config_t* config);

/**
 * \brief Sets the list of environment variables available to the WASI instance.
 *
 * By default WASI programs have a blank environment, but this can be used to
 * define some environment variables for them.
 *
 * It is required that the `names` and `values` lists both have `envc` entries.
 *
 * The env vars are copied into the `config` object as part of this function
 * call, so the `names` and `values` pointers only need to stay alive for this
 * function call.
 */
WASI_API_EXTERN void wasi_config_set_env(wasi_config_t* config, int envc, const char* names[], const char* values[]);

/**
 * \brief Indicates that the entire environment of the calling process should be
 * inherited by this WASI configuration.
 */
WASI_API_EXTERN void wasi_config_inherit_env(wasi_config_t* config);

/**
 * \brief Configures standard input to be taken from the specified file.
 *
 * By default WASI programs have no stdin, but this configures the specified
 * file to be used as stdin for this configuration.
 *
 * If the stdin location does not exist or it cannot be opened for reading then
 * `false` is returned. Otherwise `true` is returned.
 */
WASI_API_EXTERN bool wasi_config_set_stdin_file(wasi_config_t* config, const char* path);

/**
 * \brief Configures this process's own stdin stream to be used as stdin for
 * this WASI configuration.
 */
WASI_API_EXTERN void wasi_config_inherit_stdin(wasi_config_t* config);

/**
 * \brief Configures standard output to be written to the specified file.
 *
 * By default WASI programs have no stdout, but this configures the specified
 * file to be used as stdout.
 *
 * If the stdout location could not be opened for writing then `false` is
 * returned. Otherwise `true` is returned.
 */
WASI_API_EXTERN bool wasi_config_set_stdout_file(wasi_config_t* config, const char* path);

/**
 * \brief Configures this process's own stdout stream to be used as stdout for
 * this WASI configuration.
 */
WASI_API_EXTERN void wasi_config_inherit_stdout(wasi_config_t* config);

/**
 * \brief Configures standard output to be written to the specified file.
 *
 * By default WASI programs have no stderr, but this configures the specified
 * file to be used as stderr.
 *
 * If the stderr location could not be opened for writing then `false` is
 * returned. Otherwise `true` is returned.
 */
WASI_API_EXTERN bool wasi_config_set_stderr_file(wasi_config_t* config, const char* path);

/**
 * \brief Configures this process's own stderr stream to be used as stderr for
 * this WASI configuration.
 */
WASI_API_EXTERN void wasi_config_inherit_stderr(wasi_config_t* config);

/**
 * \brief Configures a "preopened directory" to be available to WASI APIs.
 *
 * By default WASI programs do not have access to anything on the filesystem.
 * This API can be used to grant WASI programs access to a directory on the
 * filesystem, but only that directory (its whole contents but nothing above it).
 *
 * The `path` argument here is a path name on the host filesystem, and
 * `guest_path` is the name by which it will be known in wasm.
 */
WASI_API_EXTERN bool wasi_config_preopen_dir(wasi_config_t* config, const char* path, const char* guest_path);

#undef own

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // #ifdef WASI_H
