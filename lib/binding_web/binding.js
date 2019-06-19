const C = Module;
const INTERNAL = {};
const SIZE_OF_INT = 4;
const SIZE_OF_NODE = 5 * SIZE_OF_INT;
const SIZE_OF_POINT = 2 * SIZE_OF_INT;
const SIZE_OF_RANGE = 2 * SIZE_OF_INT + 2 * SIZE_OF_POINT;
const ZERO_POINT = {row: 0, column: 0};

var VERSION;
var MIN_COMPATIBLE_VERSION;
var TRANSFER_BUFFER;
var currentParseCallback;
var currentLogCallback;
var initPromise = new Promise(resolve => {
  Module.onRuntimeInitialized = resolve
}).then(() => {
  TRANSFER_BUFFER = C._ts_init();
  VERSION = getValue(TRANSFER_BUFFER, 'i32');
  MIN_COMPATIBLE_VERSION = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
});

class Parser {
  static init() {
    return initPromise;
  }

  constructor() {
    if (TRANSFER_BUFFER == null) {
      throw new Error('You must first call Parser.init() and wait for it to resolve.');
    }

    C._ts_parser_new_wasm();
    this[0] = getValue(TRANSFER_BUFFER, 'i32');
    this[1] = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
  }

  delete() {
    C._ts_parser_delete(this[0]);
    C._free(this[1]);
  }

  setLanguage(language) {
    let address;
    if (!language) {
      address = 0;
      language = null;
    } else if (language.constructor === Language) {
      address = language[0];
      const version = C._ts_language_version(address);
      if (version < MIN_COMPATIBLE_VERSION || VERSION < version) {
        throw new Error(
          `Incompatible language version ${version}. ` +
          `Compatibility range ${MIN_COMPATIBLE_VERSION} through ${VERSION}.`
        );
      }
    } else {
      throw new Error('Argument must be a Language');
    }
    this.language = language;
    C._ts_parser_set_language(this[0], address);
    return this;
  }

  getLanguage() {
    return this.language
  }

  parse(callback, oldTree, options) {
    if (typeof callback === 'string') {
      currentParseCallback = (index, _, endIndex) => callback.slice(index, endIndex);
    } else if (typeof callback === 'function') {
      currentParseCallback = callback;
    } else {
      throw new Error("Argument must be a string or a function");
    }

    if (this.logCallback) {
      currentLogCallback = this.logCallback;
      C._ts_parser_enable_logger_wasm(this[0], 1);
    } else {
      currentLogCallback = null;
      C._ts_parser_enable_logger_wasm(this[0], 0);
    }

    let rangeCount = 0;
    let rangeAddress = 0;
    if (options && options.includedRanges) {
      rangeCount = options.includedRanges.length;
      rangeAddress = C._calloc(rangeCount, SIZE_OF_RANGE);
      let address = rangeAddress;
      for (let i = 0; i < rangeCount; i++) {
        marshalRange(address, options.includedRanges[i]);
        address += SIZE_OF_RANGE;
      }
    }

    const treeAddress = C._ts_parser_parse_wasm(
      this[0],
      this[1],
      oldTree ? oldTree[0] : 0,
      rangeAddress,
      rangeCount
    );

    if (!treeAddress) {
      currentParseCallback = null;
      currentLogCallback = null;
      throw new Error('Parsing failed');
    }

    const result = new Tree(INTERNAL, treeAddress, this.language, currentParseCallback);
    currentParseCallback = null;
    currentLogCallback = null;
    return result;
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
    if (!callback) {
      callback = null;
    } else if (typeof callback !== "function") {
      throw new Error("Logger callback must be a function");
    }
    this.logCallback = callback;
    return this;
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

  walk() {
    return this.rootNode.walk();
  }

  getChangedRanges(other) {
    if (other.constructor !== Tree) {
      throw new TypeError('Argument must be a Tree');
    }

    C._ts_tree_get_changed_ranges_wasm(this[0], other[0]);
    const count = getValue(TRANSFER_BUFFER, 'i32');
    const buffer = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array(count);
    if (count > 0) {
      let address = buffer;
      for (let i = 0; i < count; i++) {
        result[i] = unmarshalRange(address);
        address += SIZE_OF_RANGE;
      }
      C._free(buffer);
    }
    return result;
  }
}

class Node {
  constructor(internal, tree) {
    if (internal !== INTERNAL) {
      throw new Error('Illegal constructor')
    }
    this.tree = tree;
  }

  get id() {
    return this[0];
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
    let {startIndex, endIndex} = this;
    const length = endIndex - startIndex;
    let result = this.tree.textCallback(startIndex, null, endIndex);
    startIndex += result.length;
    while (startIndex < endIndex) {
      const string = this.tree.textCallback(startIndex, null, endIndex);
      if (string && string.length > 0) {
        startIndex += string.length;
        result += string;
      } else {
        break;
      }
    }
    if (startIndex > endIndex) {
      result = result.slice(0, length);
    }
    return result;
  }

  isNamed() {
    marshalNode(this);
    return C._ts_node_is_named_wasm(this.tree[0]) === 1;
  }

  hasError() {
    marshalNode(this);
    return C._ts_node_has_error_wasm(this.tree[0]) === 1;
  }

  hasChanges() {
    marshalNode(this);
    return C._ts_node_has_changes_wasm(this.tree[0]) === 1;
  }

  isMissing() {
    marshalNode(this);
    return C._ts_node_is_missing_wasm(this.tree[0]) === 1;
  }

  equals(other) {
    if (this === other) return true;
    for (let i = 0; i < 5; i++) {
      if (this[i] !== other[i]) return false;
    }
    return true;
  }

  child(index) {
    marshalNode(this);
    C._ts_node_child_wasm(this.tree[0], index);
    return unmarshalNode(this.tree);
  }

  namedChild(index) {
    marshalNode(this);
    C._ts_node_named_child_wasm(this.tree[0], index);
    return unmarshalNode(this.tree);
  }

  childForFieldId(fieldId) {
    marshalNode(this);
    C._ts_node_child_by_field_id_wasm(this.tree[0], fieldId);
    return unmarshalNode(this.tree);
  }

  childForFieldName(fieldName) {
    const fieldId = this.tree.language.fields.indexOf(fieldName);
    if (fieldId !== -1) return this.childForFieldId(fieldId);
  }

  get childCount() {
    marshalNode(this);
    return C._ts_node_child_count_wasm(this.tree[0]);
  }

  get namedChildCount() {
    marshalNode(this);
    return C._ts_node_named_child_count_wasm(this.tree[0]);
  }

  get firstChild() {
    return this.child(0);
  }

  get firstNamedChild() {
    return this.namedChild(0);
  }

  get lastChild() {
    return this.child(this.childCount - 1);
  }

  get lastNamedChild() {
    return this.namedChild(this.namedChildCount - 1);
  }

  get children() {
    if (!this._children) {
      marshalNode(this);
      C._ts_node_children_wasm(this.tree[0]);
      const count = getValue(TRANSFER_BUFFER, 'i32');
      const buffer = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
      this._children = new Array(count);
      if (count > 0) {
        let address = buffer;
        for (let i = 0; i < count; i++) {
          this._children[i] = unmarshalNode(this.tree, address);
          address += SIZE_OF_NODE;
        }
        C._free(buffer);
      }
    }
    return this._children;
  }

  get namedChildren() {
    if (!this._namedChildren) {
      marshalNode(this);
      C._ts_node_named_children_wasm(this.tree[0]);
      const count = getValue(TRANSFER_BUFFER, 'i32');
      const buffer = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
      this._namedChildren = new Array(count);
      if (count > 0) {
        let address = buffer;
        for (let i = 0; i < count; i++) {
          this._namedChildren[i] = unmarshalNode(this.tree, address);
          address += SIZE_OF_NODE;
        }
        C._free(buffer);
      }
    }
    return this._namedChildren;
  }

  descendantsOfType(types, startPosition, endPosition) {
    if (!Array.isArray(types)) types = [types];
    if (!startPosition) startPosition = ZERO_POINT;
    if (!endPosition) endPosition = ZERO_POINT;

    // Convert the type strings to numeric type symbols.
    const symbols = [];
    const typesBySymbol = this.tree.language.types;
    for (let i = 0, n = typesBySymbol.length; i < n; i++) {
      if (types.includes(typesBySymbol[i])) {
        symbols.push(i);
      }
    }

    // Copy the array of symbols to the WASM heap.
    const symbolsAddress = C._malloc(SIZE_OF_INT * symbols.count);
    for (let i = 0, n = symbols.length; i < n; i++) {
      setValue(symbolsAddress + i * SIZE_OF_INT, symbols[i], 'i32');
    }

    // Call the C API to compute the descendants.
    marshalNode(this);
    C._ts_node_descendants_of_type_wasm(
      this.tree[0],
      symbolsAddress,
      symbols.length,
      startPosition.row,
      startPosition.column,
      endPosition.row,
      endPosition.column
    );

    // Instantiate the nodes based on the data returned.
    const descendantCount = getValue(TRANSFER_BUFFER, 'i32');
    const descendantAddress = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array(descendantCount);
    if (descendantCount > 0) {
      let address = descendantAddress;
      for (let i = 0; i < descendantCount; i++) {
        result[i] = unmarshalNode(this.tree, address);
        address += SIZE_OF_NODE;
      }
    }

    // Free the intermediate buffers
    C._free(descendantAddress);
    C._free(symbolsAddress);
    return result;
  }

  get nextSibling() {
    marshalNode(this);
    C._ts_node_next_sibling_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get previousSibling() {
    marshalNode(this);
    C._ts_node_prev_sibling_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get nextNamedSibling() {
    marshalNode(this);
    C._ts_node_next_named_sibling_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get previousNamedSibling() {
    marshalNode(this);
    C._ts_node_prev_named_sibling_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get parent() {
    marshalNode(this);
    C._ts_node_parent_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  descendantForIndex(start, end = start) {
    if (typeof start !== 'number' || typeof end !== 'number') {
      throw new Error('Arguments must be numbers');
    }

    marshalNode(this);
    let address = TRANSFER_BUFFER + SIZE_OF_NODE;
    setValue(address, start, 'i32');
    setValue(address + SIZE_OF_INT, end, 'i32');
    C._ts_node_descendant_for_index_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  namedDescendantForIndex(start, end = start) {
    if (typeof start !== 'number' || typeof end !== 'number') {
      throw new Error('Arguments must be numbers');
    }

    marshalNode(this);
    let address = TRANSFER_BUFFER + SIZE_OF_NODE;
    setValue(address, start, 'i32');
    setValue(address + SIZE_OF_INT, end, 'i32');
    C._ts_node_named_descendant_for_index_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  descendantForPosition(start, end = start) {
    if (!isPoint(start) || !isPoint(end)) {
      throw new Error('Arguments must be {row, column} objects');
    }

    marshalNode(this);
    let address = TRANSFER_BUFFER + SIZE_OF_NODE;
    marshalPoint(address, start);
    marshalPoint(address + SIZE_OF_POINT, end);
    C._ts_node_descendant_for_position_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  namedDescendantForPosition(start, end = start) {
    if (!isPoint(start) || !isPoint(end)) {
      throw new Error('Arguments must be {row, column} objects');
    }

    marshalNode(this);
    let address = TRANSFER_BUFFER + SIZE_OF_NODE;
    marshalPoint(address, start);
    marshalPoint(address + SIZE_OF_POINT, end);
    C._ts_node_named_descendant_for_position_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  walk() {
    marshalNode(this);
    C._ts_tree_cursor_new_wasm(this.tree[0]);
    return new TreeCursor(INTERNAL, this.tree);
  }

  toString() {
    marshalNode(this);
    const address = C._ts_node_to_string_wasm(this.tree[0]);
    const result = AsciiToString(address);
    C._free(address);
    return result;
  }
}

class TreeCursor {
  constructor(internal, tree) {
    if (internal !== INTERNAL) {
      throw new Error('Illegal constructor')
    }
    this.tree = tree;
    unmarshalTreeCursor(this);
  }

  delete() {
    marshalTreeCursor(this);
    C._ts_tree_cursor_delete_wasm(this.tree[0]);
  }

  reset(node) {
    marshalNode(node);
    marshalTreeCursor(this, TRANSFER_BUFFER + SIZE_OF_NODE);
    C._ts_tree_cursor_reset_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
  }

  get nodeType() {
    return this.tree.language.types[this.nodeTypeId] || 'ERROR';
  }

  get nodeTypeId() {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_type_id_wasm(this.tree[0]);
  }

  get nodeId() {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_id_wasm(this.tree[0]);
  }

  get nodeIsNamed() {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_is_named_wasm(this.tree[0]) === 1;
  }

  get nodeIsMissing() {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_is_missing_wasm(this.tree[0]) === 1;
  }

  get startPosition() {
    marshalTreeCursor(this);
    C._ts_tree_cursor_start_position_wasm(this.tree[0]);
    return unmarshalPoint(TRANSFER_BUFFER);
  }

  get endPosition() {
    marshalTreeCursor(this);
    C._ts_tree_cursor_end_position_wasm(this.tree[0]);
    return unmarshalPoint(TRANSFER_BUFFER);
  }

  get startIndex() {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_start_index_wasm(this.tree[0]);
  }

  get endIndex() {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_end_index_wasm(this.tree[0]);
  }

  currentNode() {
    marshalTreeCursor(this);
    C._ts_tree_cursor_current_node_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  currentFieldId() {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_field_id_wasm(this.tree[0]);
  }

  currentFieldName() {
    return this.tree.language.fields[this.currentFieldId()];
  }

  gotoFirstChild() {
    marshalTreeCursor(this);
    const result = C._ts_tree_cursor_goto_first_child_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }

  gotoNextSibling() {
    marshalTreeCursor(this);
    const result = C._ts_tree_cursor_goto_next_sibling_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }

  gotoParent() {
    marshalTreeCursor(this);
    const result = C._ts_tree_cursor_goto_parent_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
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
    this.fields = new Array(C._ts_language_field_count(this[0]) + 1);
    for (let i = 0, n = this.fields.length; i < n; i++) {
      const fieldName = C._ts_language_field_name_for_id(this[0], i);
      if (fieldName !== 0) {
        this.fields[i] = UTF8ToString(fieldName);
      } else {
        this.fields[i] = null;
      }
    }
  }

  get version() {
    return C._ts_language_version(this[0]);
  }

  get fieldCount() {
    return this.fields.length - 1;
  }

  fieldIdForName(fieldName) {
    const result = this.fields.indexOf(fieldName);
    if (result !== -1) {
      return result;
    } else {
      return null;
    }
  }

  fieldNameForId(fieldId) {
    return this.fields[fieldName] || null;
  }

  static load(url) {
    let bytes;
    if (
      typeof process !== 'undefined' &&
      process.versions &&
      process.versions.node
    ) {
      const fs = require('fs');
      bytes = Promise.resolve(fs.readFileSync(url));
    } else {
      bytes = fetch(url)
        .then(response => response.arrayBuffer()
          .then(buffer => {
            if (response.ok) {
              return new Uint8Array(buffer);
            } else {
              const body = new TextDecoder('utf-8').decode(buffer);
              throw new Error(`Language.load failed with status ${response.status}.\n\n${body}`)
            }
          }));
    }

    return bytes
      .then(bytes => loadWebAssemblyModule(bytes, {loadAsync: true}))
      .then(mod => {
        const functionName = Object.keys(mod).find(key => key.includes("tree_sitter_"));
        const languageAddress = mod[functionName]();
        return new Language(INTERNAL, languageAddress);
      });
  }
}

function isPoint(point) {
  return (
    point &&
    typeof point.row === 'number' &&
    typeof point.column === 'number'
  );
}

function marshalNode(node) {
  let address = TRANSFER_BUFFER;
  for (let i = 0; i < 5; i++) {
    setValue(address, node[i], 'i32');
    address += SIZE_OF_INT;
  }
}

function unmarshalNode(tree, address = TRANSFER_BUFFER) {
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

function marshalTreeCursor(cursor, address = TRANSFER_BUFFER) {
  setValue(address + 0 * SIZE_OF_INT, cursor[0], 'i32'),
  setValue(address + 1 * SIZE_OF_INT, cursor[1], 'i32'),
  setValue(address + 2 * SIZE_OF_INT, cursor[2], 'i32')
}

function unmarshalTreeCursor(cursor) {
  cursor[0] = getValue(TRANSFER_BUFFER + 0 * SIZE_OF_INT, 'i32'),
  cursor[1] = getValue(TRANSFER_BUFFER + 1 * SIZE_OF_INT, 'i32'),
  cursor[2] = getValue(TRANSFER_BUFFER + 2 * SIZE_OF_INT, 'i32')
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
  marshalPoint(address, range.startPosition); address += SIZE_OF_POINT;
  marshalPoint(address, range.endPosition); address += SIZE_OF_POINT;
  setValue(address, range.startIndex, 'i32'); address += SIZE_OF_INT;
  setValue(address, range.endIndex, 'i32'); address += SIZE_OF_INT;
}

function unmarshalRange(address) {
  const result = {};
  result.startPosition = unmarshalPoint(address); address += SIZE_OF_POINT;
  result.endPosition = unmarshalPoint(address); address += SIZE_OF_POINT;
  result.startIndex = getValue(address, 'i32'); address += SIZE_OF_INT;
  result.endIndex = getValue(address, 'i32');
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
