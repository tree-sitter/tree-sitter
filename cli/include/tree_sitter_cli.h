#ifndef TREE_SITTER_CLI_H_
#define TREE_SITTER_CLI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


/// Generate the Swift source which defines the TSLanguage structure for for the given
/// json grammar text and ABI version (with 0 indicating the most recent). If successful, 
/// invoke completion with status 0 along with the bytes and length of the source/ text; 
/// otherwise invoke completion with non-zero status and the bytes and length of the error 
/// description. In either case, return the result of completion.
///
/// Note that the bytes given to completion are owned and managed by this method.

const void *swiftgen(
    const uint8_t *json_bytes, 
    uint32_t json_len,
    uint32_t abi_version,
    const void *(*completion)(uint32_t success, const uint8_t *bytes, uint32_t bytes_len)
);

uint32_t swiftgen_max_abi_version();

enum {
    SWIFTGEN_ERROR_INVALID_VERSION = 1,
    SWIFTGEN_ERROR_INVALID_INPUT = 2,
    SWIFTGEN_ERROR_OUTPUT_TOO_LONG = 3,
    SWIFTGEN_ERROR_OTHER = 4,
};


#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_PARSER_H_
