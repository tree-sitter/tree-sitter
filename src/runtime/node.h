#ifndef RUNTIME_NODE_H_
#define RUNTIME_NODE_H_

#include "runtime/tree.h"

TSNode ts_node_make(const Tree *, uint32_t character, uint32_t byte, uint32_t row);

#endif
