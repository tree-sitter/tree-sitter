#ifndef TREE_SITTER_WASM_ENDIAN_H_
#define TREE_SITTER_WASM_ENDIAN_H_

#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 1234
#endif
#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN 4321
#endif
#ifndef __BYTE_ORDER
#define __BYTE_ORDER __LITTLE_ENDIAN
#endif

#define be16toh(x) __builtin_bswap16(x)
#define be32toh(x) __builtin_bswap32(x)
#define be64toh(x) __builtin_bswap64(x)
#define le16toh(x) (x)
#define le32toh(x) (x)
#define le64toh(x) (x)

#endif // TREE_SITTER_WASM_ENDIAN_H_
