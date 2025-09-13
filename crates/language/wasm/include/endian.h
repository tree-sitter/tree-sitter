#ifndef TREE_SITTER_WASM_ENDIAN_H_
#define TREE_SITTER_WASM_ENDIAN_H_

#define be16toh(x) __builtin_bswap16(x)
#define be32toh(x) __builtin_bswap32(x)
#define be64toh(x) __builtin_bswap64(x)
#define le16toh(x) (x)
#define le32toh(x) (x)
#define le64toh(x) (x)


#endif // TREE_SITTER_WASM_ENDIAN_H_
