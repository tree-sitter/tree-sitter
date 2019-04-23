const C = Module;
const INTERNAL = {};
const SIZE_OF_INT = 4;
const SIZE_OF_NODE = 5 * SIZE_OF_INT;
const SIZE_OF_POINT = 2 * SIZE_OF_INT;
const SIZE_OF_RANGE = 2 * SIZE_OF_INT + 2 * SIZE_OF_POINT;

var TRANSFER_BUFFER;
var currentParseCallback;
var currentLogCallback;

class Parser {
  static init() {
    return new Promise(resolve => {
      Module.onRuntimeInitialized = resolve
    }).then(() => {
      TRANSFER_BUFFER = C._ts_init();
    });
  }

  constructor() {
    C._ts_parser_new_wasm();
    this[0] = getValue(TRANSFER_BUFFER, 'i32');
    this[1] = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
  }

  delete() {
    C._ts_parser_delete(this[0]);
    C._free(this[1]);
  }

  setLanguage(language) {
    this.language = language;
    if (language.constructor !== Language) {
      throw new Error('Argument must be a Language');
    }
    C._ts_parser_set_language(this[0], language[0]);
    if (C._ts_parser_language(this[0]) !== language[0]) {
      throw new Error('Incompatible language');
    }
  }

  getLanguage() {
    return this.language
  }

  setIncludedRanges(ranges) {
    const buffer = C._calloc(ranges.length, SIZE_OF_RANGE);
    let address = buffer;
    for (let i = 0, n = ranges.length; i < n; i++) {
      marshalRange(address, ranges[i]);
      address += SIZE_OF_RANGE;
    }
    C._ts_parser_set_included_ranges(self[0], buffer, ranges.length);
    C._free(buffer);
  }

  getIncludedRanges() {
    const buffer = C._ts_parser_included_ranges(self[0], TRANSFER_BUFFER);
    const length = getValue(TRANSFER_BUFFER, 'i32');
    const result = new Array(length);
    let address = buffer;
    for (let i = 0; i < length; i++) {
      result[i] = unmarshalRange(address);
      address += SIZE_OF_RANGE;
    }
    return result;
  }

  parse(oldTree, callback) {
    if (typeof callback === 'string') {
      return this.parse(oldTree, index => callback.slice(index))
    }

    if (this.logCallback) {
      currentLogCallback = this.logCallback;
      C._ts_parser_enable_logger_wasm(this[0], 1);
    } else {
      C._ts_parser_enable_logger_wasm(this[0], 0);
    }

    currentParseCallback = callback;
    const treeAddress = C._ts_parser_parse_wasm(
      this[0],
      this[1],
      oldTree ? oldTree[0] : 0
    );

    currentParseCallback = null;
    currentLogCallback = null;

    if (!treeAddress) {
      throw new Error('Parsing failed');
    }

    return new Tree(INTERNAL, treeAddress, this.language, callback);
  }

  reset() {
    C._ts_parser_parse_wasm(this[0]);
  }

  setTimeoutMicros(timeout) {
    C._ts_parser_set_timeout_micros(this[0], timeout);
  }

  getTimeoutMicros(timeout) {
    C._ts_parser_timeout_micros(this[0]);
  }

  setLogger(callback) {
    this.logCallback = callback;
  }

  getLogger() {
    return this.logCallback;
  }
}

class Tree {
  constructor(internal, address, language, textCallback) {
    if (internal !== INTERNAL) {
      throw new Error('Illegal constructor')
    }
    this[0] = address;
    this.language = language;
    this.textCallback = textCallback;
  }

  copy() {
    const address = C._ts_tree_copy(this[0]);
    return new Tree(INTERNAL, address, this.language, this.textCallback);
  }

  delete() {
    C._ts_tree_delete(this[0]);
  }

  edit(edit) {
    marshalEdit(edit);
    C._ts_tree_edit_wasm(this[0]);
  }

  get rootNode() {
    C._ts_tree_root_node_wasm(this[0]);
    return unmarshalNode(this);
  }

  getLanguage() {
    return this.language;
  }
}

class Node {
  constructor(internal, tree) {
    if (internal !== INTERNAL) {
      throw new Error('Illegal constructor')
    }
    this.tree = tree;
  }

  get typeId() {
    marshalNode(this);
    return C._ts_node_symbol_wasm(this.tree);
  }

  get type() {
    return this.tree.language.types[this.typeId] || 'ERROR';
  }

  get startPosition() {
    marshalNode(this);
    C._ts_node_start_point_wasm(this.tree[0]);
    return unmarshalPoint(TRANSFER_BUFFER);
  }

  get endPosition() {
    marshalNode(this);
    C._ts_node_end_point_wasm(this.tree[0]);
    return unmarshalPoint(TRANSFER_BUFFER);
  }

  get startIndex() {
    marshalNode(this);
    return C._ts_node_start_index_wasm(this.tree[0]);
  }

  get endIndex() {
    marshalNode(this);
    return C._ts_node_end_index_wasm(this.tree[0]);
  }

  get text() {
    const startIndex = this.startIndex;
    const length = this.endIndex - startIndex;
    let result = this.tree.textCallback(startIndex);
    while (result.length < length) {
      result += this.tree.textCallback(startIndex + result.length);
    }
    return result.slice(0, length);
  }

  equals(other) {
    if (this === other) return true;
    for (let i = 0; i < 5; i++) {
      if (this[i] !== other[i]) return false;
    }
    return true;
  }

  get childCount() {
    marshalNode(this);
    return C._ts_node_child_count_wasm(this.tree[0]);
  }

  child(index) {
    marshalNode(this);
    C._ts_node_child_wasm(this.tree[0], index);
    return unmarshalNode(this.tree);
  }

  get namedChildCount() {
    marshalNode(this);
    return C._ts_node_named_child_count_wasm(this.tree[0]);
  }

  namedChild(index) {
    marshalNode(this);
    C._ts_node_named_child_wasm(this.tree[0], index);
    return unmarshalNode(this.tree);
  }

  get parent() {
    marshalNode(this);
    C._ts_node_parent_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  descendantForPosition(start, end = start) {
    marshalNode(this);
    let address = TRANSFER_BUFFER + SIZE_OF_NODE;
    marshalPoint(address);
    marshalPoint(address + SIZE_OF_POINT);
    C._ts_node_descendant_for_position_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  namedDescendantForPosition(start, end = start) {
    marshalNode(this);
    let address = TRANSFER_BUFFER + SIZE_OF_NODE;
    marshalPoint(address, start);
    marshalPoint(address + SIZE_OF_POINT, end);
    C._ts_node_named_descendant_for_position_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  toString() {
    marshalNode(this);
    const address = C._ts_node_to_string_wasm(this.tree[0]);
    const result = AsciiToString(address);
    C._free(address);
    return result;
  }
}

class Language {
  constructor(internal, address) {
    if (internal !== INTERNAL) {
      throw new Error('Illegal constructor')
    }
    this[0] = address;
    this.types = new Array(C._ts_language_symbol_count(this[0]));
    for (let i = 0, n = this.types.length; i < n; i++) {
      if (C._ts_language_symbol_type(this[0], i) < 2) {
        this.types[i] = UTF8ToString(C._ts_language_symbol_name(this[0], i));
      }
    }
  }

  get version() {
    return C._ts_language_version(this[0]);
  }

  static load(url) {
    return fetch(url)
      .then(response => response.arrayBuffer()
        .then(buffer => {
          if (response.ok) {
            return loadWebAssemblyModule(new Uint8Array(buffer), {loadAsync: true});
          } else {
            const body = new TextDecoder('utf-8').decode(buffer);
            throw new Error(`Language.load failed with status ${response.status}.\n\n${body}`)
          }
        }))
      .then(exports => {
        const functionName = Object.keys(exports).find(key => key.includes("tree_sitter_"));
        const languageAddress = exports[functionName]();
        return new Language(INTERNAL, languageAddress);
      });
  }
}

function marshalNode(node) {
  let address = TRANSFER_BUFFER;
  for (let i = 0; i < 5; i++) {
    setValue(address, node[i], 'i32');
    address += SIZE_OF_INT;
  }
}

function unmarshalNode(tree) {
  let address = TRANSFER_BUFFER;
  const id = getValue(address, 'i32');
  if (id === 0) return null;
  const result = new Node(INTERNAL, tree);
  result[0] = id;
  address += SIZE_OF_INT;
  for (let i = 1; i < 5; i++) {
    result[i] = getValue(address, 'i32');
    address += SIZE_OF_INT;
  }
  return result;
}

function marshalPoint(address, point) {
  setValue(address, point.row, 'i32')
  setValue(address + SIZE_OF_INT, point.column, 'i32')
}

function unmarshalPoint(address) {
  return {
    row: getValue(address, 'i32'),
    column: getValue(address + SIZE_OF_INT, 'i32')
  }
}

function marshalRange(address, range) {
  setValue(address, range.startIndex, 'i32'); address += SIZE_OF_INT;
  setValue(address, range.endIndex, 'i32'); address += SIZE_OF_INT;
  marshalPoint(address, range.startPosition); address += SIZE_OF_POINT;
  marshalPoint(address, range.endPosition); address += SIZE_OF_POINT;
}

function unmarshalRange(address) {
  const result = {};
  result.startIndex = getValue(address, 'i32'); address += SIZE_OF_INT;
  result.endIndex = getValue(address, 'i32'); address += SIZE_OF_INT;
  result.startPosition = unmarshalPoint(address); address += SIZE_OF_POINT;
  result.endPosition = unmarshalPoint(address);
  return result;
}

function marshalEdit(edit) {
  let address = TRANSFER_BUFFER;
  marshalPoint(address, edit.startPosition); address += SIZE_OF_POINT;
  marshalPoint(address, edit.oldEndPosition); address += SIZE_OF_POINT;
  marshalPoint(address, edit.newEndPosition); address += SIZE_OF_POINT;
  setValue(address, edit.startIndex, 'i32'); address += SIZE_OF_INT;
  setValue(address, edit.oldEndIndex, 'i32'); address += SIZE_OF_INT;
  setValue(address, edit.newEndIndex, 'i32'); address += SIZE_OF_INT;
}

Parser.Language = Language;

return Parser;

}));
