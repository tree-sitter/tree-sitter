/* eslint-disable @typescript-eslint/no-use-before-define */
import Module from '../../build-wasm/tree-sitter-c';
import * as _fs from 'fs'; // Only used for types

interface TreeSitterModule extends EmscriptenModule {
  /* eslint-disable @typescript-eslint/camelcase */
  // Emscripten exports
  _ts_init(): number;

  _ts_tree_root_node_wasm(tree: number): void;
  _ts_tree_copy(tree: number): number;
  _ts_tree_delete(tree: number): void;
  _ts_tree_edit_wasm(tree: number): void;
  _ts_tree_get_changed_ranges_wasm(tree: number, other: number): void;

  _ts_tree_cursor_new_wasm(tree: number): void;
  _ts_tree_cursor_delete_wasm(tree: number): void;
  _ts_tree_cursor_reset_wasm(tree: number): void;
  _ts_tree_cursor_current_node_type_id_wasm(tree: number): number;
  _ts_tree_cursor_current_node_id_wasm(tree: number): number;
  _ts_tree_cursor_current_node_is_named_wasm(tree: number): number;
  _ts_tree_cursor_current_node_is_missing_wasm(tree: number): number;
  _ts_tree_cursor_start_index_wasm(tree: number): number;
  _ts_tree_cursor_end_index_wasm(tree: number): number;
  _ts_tree_cursor_start_position_wasm(tree: number): void;
  _ts_tree_cursor_end_position_wasm(tree: number): void;
  _ts_tree_cursor_current_node_wasm(tree: number): void;
  _ts_tree_cursor_current_field_id_wasm(tree: number): number;
  _ts_tree_cursor_goto_first_child_wasm(tree: number): number;
  _ts_tree_cursor_goto_next_sibling_wasm(tree: number): number;
  _ts_tree_cursor_goto_parent_wasm(tree: number): number;

  _ts_node_end_point_wasm(tree: number): void;
  _ts_node_end_index_wasm(tree: number): number;
  _ts_node_is_named_wasm(tree: number): number;
  _ts_node_symbol_wasm(tree: number): number;
  _ts_node_has_error_wasm(tree: number): number;
  _ts_node_has_changes_wasm(tree: number): number;
  _ts_node_is_missing_wasm(tree: number): number;
  _ts_node_child_wasm(tree: number, index: number): void;
  _ts_node_named_child_wasm(tree: number, index: number): void;
  _ts_node_child_by_field_id_wasm(tree: number, fieldId: number): void;
  _ts_node_child_count_wasm(tree: number): number;
  _ts_node_named_child_count_wasm(tree: number): number;
  _ts_node_children_wasm(tree: number): void;
  _ts_node_named_children_wasm(tree: number): void;
  _ts_node_descendants_of_type_wasm(
    tree: number,
    symbols: number,
    symbol_count: number,
    start_row: number,
    start_column: number,
    end_row: number,
    end_column: number
  ): void;
  _ts_node_next_sibling_wasm(tree: number): void;
  _ts_node_prev_sibling_wasm(tree: number): void;
  _ts_node_next_named_sibling_wasm(tree: number): void;
  _ts_node_prev_named_sibling_wasm(tree: number): void;
  _ts_node_parent_wasm(tree: number): void;
  _ts_node_descendant_for_index_wasm(tree: number): void;
  _ts_node_named_descendant_for_index_wasm(tree: number): void;
  _ts_node_descendant_for_position_wasm(tree: number): void;
  _ts_node_named_descendant_for_position_wasm(tree: number): void;
  _ts_node_to_string_wasm(tree: number): number;

  _ts_parser_new_wasm(): void;
  _ts_parser_delete(parser: number): void;
  _ts_parser_set_language(parser: number, language: number): boolean;
  _ts_parser_enable_logger_wasm(parser: number, shouldLog: number): void;
  _ts_parser_parse_wasm(
    parser: number,
    inputBuffer?: number,
    oldTree?: number,
    ranges?: number,
    rangeCount?: number
  ): number;
  _ts_parser_set_timeout_micros(parser: number, timeout: number): void;
  _ts_parser_timeout_micros(parser: number): number;

  _ts_language_version(language: number): number;
  _ts_language_symbol_count(language: number): number;
  _ts_language_symbol_type(language: number, symbol: number): number; // symbol and the return value are Enums of type TSSymbolType
  _ts_language_symbol_name(language: number, symbol: number): number;
  _ts_language_field_count(language: number): number;
  _ts_language_field_name_for_id(language: number, fieldId: number): number;

  _ts_query_new(language: number, source: number, sourceLen: number, error_offset: number, error_type: number): number;
  _ts_query_delete(query: number): void;
  _ts_query_captures_wasm(
    query: number,
    tree: number,
    start_row: number,
    start_column: number,
    end_row: number,
    end_column: number
  ): void;
  _ts_query_matches_wasm(
    query: number,
    tree: number,
    start_row: number,
    start_column: number,
    end_row: number,
    end_column: number
  ): void;
  _ts_query_pattern_count(query: number): number;
  _ts_query_capture_count(query: number): number;
  _ts_query_string_count(query: number): number;
  _ts_query_capture_name_for_id(query: number, id: number, length: number): number;
  _ts_query_string_value_for_id(query: number, id: number, length: number): number;
  _ts_query_predicates_for_pattern(query: number, pattern_index: number, length: number): number;

  // Emscripten runtime exports
  _calloc(num: number, size: number): number;
  loadWebAssemblyModule(binary: Uint8Array, flags: Record<string, boolean>): object;
  getValue: typeof getValue;
  setValue: typeof setValue;
  AsciiToString: (ptr: number) => string; // TODO: Make a pr for this, probably with max bytes param
  UTF8ToString: typeof UTF8ToString;
  lengthBytesUTF8: typeof lengthBytesUTF8;
  stringToUTF8: typeof stringToUTF8;
  /* eslint-enable @typescript-eslint/camelcase */

  // JS imports
  currentLogCallback: Parser.Logger | null;
  currentParseCallback: Parser.Input | null;
}

const C = Module as TreeSitterModule;
let TRANSFER_BUFFER: number; // A mutable shared buffer of 12 (void *)s
// Sizes in bytes
const SIZE_OF_INT = 4;
const SIZE_OF_POINT = 2 * SIZE_OF_INT;
const SIZE_OF_RANGE = 2 * SIZE_OF_INT + 2 * SIZE_OF_POINT;
const SIZE_OF_NODE = 5 * SIZE_OF_INT;

// Make sure only we can call constructors
const INTERNAL: {} = {};
function assertInternal(x: {}): void {
  if (x !== INTERNAL) throw new Error('Illegal constructor');
}

let VERSION: number;
let MIN_COMPATIBLE_VERSION: number;
const initPromise = new Promise(resolve => {
  C.onRuntimeInitialized = resolve;
}).then(() => {
  TRANSFER_BUFFER = C._ts_init();
  VERSION = C.getValue(TRANSFER_BUFFER, 'i32');
  MIN_COMPATIBLE_VERSION = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
});

class Parser {
  _addr: number;
  _inBuf: number;
  language: Parser.Language | null = null;
  logCallback: Parser.Logger | null = null;
  static init(): Promise<void> {
    return initPromise;
  }

  constructor() {
    if (TRANSFER_BUFFER == null) {
      throw new Error('You must first call Parser.init() and wait for it to resolve.');
    }

    C._ts_parser_new_wasm();
    this._addr = C.getValue(TRANSFER_BUFFER, 'i32');
    this._inBuf = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
  }

  delete(): void {
    C._ts_parser_delete(this._addr);
    C._free(this._inBuf);
  }

  setLanguage(language: Parser.Language | null): Parser {
    let address: number;
    if (!language) {
      address = 0;
      this.language = null;
    } else if (language instanceof Parser.Language) {
      this.language = language;
      address = language._addr;
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
    C._ts_parser_set_language(this._addr, address);
    return this;
  }

  getLanguage(): Parser.Language | null {
    return this.language;
  }

  parse(callback: string | Parser.Input, oldTree?: Parser.Tree, options?: Parser.Options): Parser.Tree {
    if (typeof callback === 'string') {
      C.currentParseCallback = (index, _, endIndex): string => callback.slice(index, endIndex);
    } else if (typeof callback === 'function') {
      C.currentParseCallback = callback;
    } else {
      throw new Error('Argument must be a string or a function');
    }

    if (this.logCallback) {
      C.currentLogCallback = this.logCallback;
      C._ts_parser_enable_logger_wasm(this._addr, 1);
    } else {
      C.currentLogCallback = null;
      C._ts_parser_enable_logger_wasm(this._addr, 0);
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
      this._addr,
      this._inBuf,
      oldTree ? oldTree._addr : 0,
      rangeAddress,
      rangeCount
    );

    if (!treeAddress) {
      C.currentParseCallback = null;
      C.currentLogCallback = null;
      throw new Error('Parsing failed');
    }
    // C._ts_parser_parse_wasm returns a null if a language is not provided, so there must be one defined if we got here
    const result = new Parser.Tree(INTERNAL, treeAddress, this.language!, C.currentParseCallback);
    C.currentParseCallback = null;
    C.currentLogCallback = null;
    return result;
  }

  reset(): void {
    C._ts_parser_parse_wasm(this._addr);
  }

  setTimeoutMicros(timeout: number): void {
    C._ts_parser_set_timeout_micros(this._addr, timeout);
  }

  getTimeoutMicros(): number {
    return C._ts_parser_timeout_micros(this._addr);
  }

  setLogger(callback: Parser.Logger): Parser {
    if (!callback) {
      this.logCallback = null;
    } else if (typeof callback !== 'function') {
      throw new Error('Logger callback must be a function');
    } else {
      this.logCallback = callback;
    }
    return this;
  }

  getLogger(): Parser.Logger | null {
    return this.logCallback;
  }
}

/* eslint-disable @typescript-eslint/no-namespace */
namespace Parser {
  const ZERO_POINT: Point = { row: 0, column: 0 };

  export type Point = {
    row: number;
    column: number;
  };

  export type Logger = (message: string, params: { [param: string]: string }, type: 'parse' | 'lex') => void;

  export type Input = (startIndex: number, startPoint?: Point | null, endIndex?: number) => string | null;

  export type Options = {
    includedRanges?: Range[];
  };

  export type Edit = {
    startIndex: number;
    oldEndIndex: number;
    newEndIndex: number;
    startPosition: Point;
    oldEndPosition: Point;
    newEndPosition: Point;
  };

  export type Range = {
    startPosition: Point;
    endPosition: Point;
    startIndex: number;
    endIndex: number;
  };

  export class Tree {
    _addr: number;
    language: Language;
    textCallback: Parser.Input;

    constructor(internal: {}, address: number, language: Language, textCallback: Parser.Input) {
      assertInternal(internal);
      this._addr = address;
      this.language = language;
      this.textCallback = textCallback;
    }

    copy(): Tree {
      const address = C._ts_tree_copy(this._addr);
      return new Tree(INTERNAL, address, this.language, this.textCallback);
    }

    delete(): void {
      C._ts_tree_delete(this._addr);
    }

    edit(delta: Edit): void {
      marshalEdit(delta);
      C._ts_tree_edit_wasm(this._addr);
    }

    get rootNode(): Node {
      C._ts_tree_root_node_wasm(this._addr);
      return unmarshalNode(this)!; // There is always a root node
    }

    getLanguage(): Language {
      return this.language;
    }

    walk(): TreeCursor {
      return this.rootNode.walk();
    }

    getChangedRanges(other: Tree): Range[] {
      if (other.constructor !== Tree) {
        throw new TypeError('Argument must be a Tree');
      }
      C._ts_tree_get_changed_ranges_wasm(this._addr, other._addr);
      const count = C.getValue(TRANSFER_BUFFER, 'i32');
      const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
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

  export class Node {
    _addr: number;
    private _children: Array<Node> | undefined;
    private _namedChildren: Array<Node> | undefined;

    id: number;
    startPosition: Point;
    startIndex: number;
    tree: Tree;

    constructor(internal: {}, tree: Tree, id: number, startPosition: Point, startIndex: number, address: number) {
      assertInternal(internal);
      this.tree = tree;
      this.id = id;
      this.startPosition = startPosition;
      this.startIndex = startIndex;
      this._addr = address;
    }

    get typeId(): number {
      marshalNode(this);
      return C._ts_node_symbol_wasm(this.tree._addr);
    }

    get type(): string {
      return this.tree.language.types[this.typeId] || 'ERROR';
    }

    get endPosition(): Point {
      marshalNode(this);
      C._ts_node_end_point_wasm(this.tree._addr);
      return unmarshalPoint(TRANSFER_BUFFER);
    }

    get endIndex(): number {
      marshalNode(this);
      return C._ts_node_end_index_wasm(this.tree._addr);
    }

    get text(): string {
      return getText(this.tree, this.startIndex, this.endIndex);
    }

    isNamed(): boolean {
      marshalNode(this);
      return C._ts_node_is_named_wasm(this.tree._addr) === 1;
    }

    hasError(): boolean {
      marshalNode(this);
      return C._ts_node_has_error_wasm(this.tree._addr) === 1;
    }

    hasChanges(): boolean {
      marshalNode(this);
      return C._ts_node_has_changes_wasm(this.tree._addr) === 1;
    }

    isMissing(): boolean {
      marshalNode(this);
      return C._ts_node_is_missing_wasm(this.tree._addr) === 1;
    }

    equals(other: Node): boolean {
      if (this === other) return true;
      if (this._addr !== other._addr) return false;
      return true;
    }

    child(index: number): Node | null {
      marshalNode(this);
      C._ts_node_child_wasm(this.tree._addr, index);
      return unmarshalNode(this.tree);
    }

    namedChild(index: number): Node | null {
      marshalNode(this);
      C._ts_node_named_child_wasm(this.tree._addr, index);
      return unmarshalNode(this.tree);
    }

    childForFieldId(fieldId: number): Node | null {
      marshalNode(this);
      C._ts_node_child_by_field_id_wasm(this.tree._addr, fieldId);
      return unmarshalNode(this.tree);
    }

    childForFieldName(fieldName: string): Node | null {
      const fieldId = this.tree.language.fields.indexOf(fieldName);
      if (fieldId !== -1) return this.childForFieldId(fieldId);
      return null;
    }

    get childCount(): number {
      marshalNode(this);
      return C._ts_node_child_count_wasm(this.tree._addr);
    }

    get namedChildCount(): number {
      marshalNode(this);
      return C._ts_node_named_child_count_wasm(this.tree._addr);
    }

    get firstChild(): Node | null {
      return this.child(0);
    }

    get firstNamedChild(): Node | null {
      return this.namedChild(0);
    }

    get lastChild(): Node | null {
      return this.child(this.childCount - 1);
    }

    get lastNamedChild(): Node | null {
      return this.namedChild(this.namedChildCount - 1);
    }

    get children(): Array<Node> {
      if (!this._children) {
        marshalNode(this);
        C._ts_node_children_wasm(this.tree._addr);
        const count = C.getValue(TRANSFER_BUFFER, 'i32');
        const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
        this._children = new Array(count);
        if (count > 0) {
          let address = buffer;
          for (let i = 0; i < count; i++) {
            this._children[i] = unmarshalNode(this.tree, address)!; // This is okay because we got the list from the C call
            address += SIZE_OF_NODE;
          }
          C._free(buffer);
        }
      }
      return this._children;
    }

    get namedChildren(): Array<Node> {
      if (!this._namedChildren) {
        marshalNode(this);
        C._ts_node_named_children_wasm(this.tree._addr);
        const count = C.getValue(TRANSFER_BUFFER, 'i32');
        const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
        this._namedChildren = new Array(count);
        if (count > 0) {
          let address = buffer;
          for (let i = 0; i < count; i++) {
            this._namedChildren[i] = unmarshalNode(this.tree, address)!; // This is okay because we got the list from the C call
            address += SIZE_OF_NODE;
          }
          C._free(buffer);
        }
      }
      return this._namedChildren;
    }

    descendantsOfType(types: string | Array<string>, startPosition?: Point, endPosition?: Point): Array<Node> {
      if (!Array.isArray(types)) types = [types];
      if (!startPosition) startPosition = ZERO_POINT;
      if (!endPosition) endPosition = ZERO_POINT;

      // Convert the type strings to numeric type symbols.
      const symbols: Array<number> = [];
      const typesBySymbol = this.tree.language.types;
      for (let i = 0, n = typesBySymbol.length; i < n; i++) {
        if (types.includes(typesBySymbol[i])) {
          symbols.push(i);
        }
      }

      // Copy the array of symbols to the WASM heap.
      const symbolsAddress = C._malloc(SIZE_OF_INT * symbols.length);
      for (let i = 0, n = symbols.length; i < n; i++) {
        C.setValue(symbolsAddress + i * SIZE_OF_INT, symbols[i], 'i32');
      }

      // Call the C API to compute the descendants.
      marshalNode(this);
      C._ts_node_descendants_of_type_wasm(
        this.tree._addr,
        symbolsAddress,
        symbols.length,
        startPosition.row,
        startPosition.column,
        endPosition.row,
        endPosition.column
      );

      // Instantiate the nodes based on the data returned.
      const descendantCount = C.getValue(TRANSFER_BUFFER, 'i32');
      const descendantAddress = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
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
    get nextSibling(): Node | null {
      marshalNode(this);
      C._ts_node_next_sibling_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    get previousSibling(): Node | null {
      marshalNode(this);
      C._ts_node_prev_sibling_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    get nextNamedSibling(): Node | null {
      marshalNode(this);
      C._ts_node_next_named_sibling_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    get previousNamedSibling(): Node | null {
      marshalNode(this);
      C._ts_node_prev_named_sibling_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    get parent(): Node | null {
      marshalNode(this);
      C._ts_node_parent_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    descendantForIndex(start: number, end: number = start): Node | null {
      if (typeof start !== 'number' || typeof end !== 'number') {
        throw new Error('Arguments must be numbers');
      }
      marshalNode(this);
      const address = TRANSFER_BUFFER + SIZE_OF_NODE;
      C.setValue(address, start, 'i32');
      C.setValue(address + SIZE_OF_INT, end, 'i32');
      C._ts_node_descendant_for_index_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    namedDescendantForIndex(start: number, end: number = start): Node | null {
      if (typeof start !== 'number' || typeof end !== 'number') {
        throw new Error('Arguments must be numbers');
      }
      marshalNode(this);
      const address = TRANSFER_BUFFER + SIZE_OF_NODE;
      C.setValue(address, start, 'i32');
      C.setValue(address + SIZE_OF_INT, end, 'i32');
      C._ts_node_named_descendant_for_index_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    descendantForPosition(start: Point, end: Point = start): Node | null {
      if (!isPoint(start) || !isPoint(end)) {
        throw new Error('Arguments must be {row, column} objects');
      }
      marshalNode(this);
      const address = TRANSFER_BUFFER + SIZE_OF_NODE;
      marshalPoint(address, start);
      marshalPoint(address + SIZE_OF_POINT, end);
      C._ts_node_descendant_for_position_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    namedDescendantForPosition(start: Point, end: Point = start): Node | null {
      if (!isPoint(start) || !isPoint(end)) {
        throw new Error('Arguments must be {row, column} objects');
      }
      marshalNode(this);
      const address = TRANSFER_BUFFER + SIZE_OF_NODE;
      marshalPoint(address, start);
      marshalPoint(address + SIZE_OF_POINT, end);
      C._ts_node_named_descendant_for_position_wasm(this.tree._addr);
      return unmarshalNode(this.tree);
    }

    walk(): TreeCursor {
      marshalNode(this);
      C._ts_tree_cursor_new_wasm(this.tree._addr);
      return new TreeCursor(INTERNAL, this.tree);
    }

    toString(): string {
      marshalNode(this);
      const address = C._ts_node_to_string_wasm(this.tree._addr);
      const result = C.AsciiToString(address);
      C._free(address);
      return result;
    }
  }

  export class TreeCursor {
    _id!: number; // unmarshalTreeCursor(this) always fills this out
    _ctx: number[];
    tree: Tree;

    constructor(internal: {}, tree: Tree) {
      assertInternal(internal);
      this._ctx = new Array<number>(2);
      this.tree = tree;
      unmarshalTreeCursor(this);
    }

    delete(): void {
      marshalTreeCursor(this);
      C._ts_tree_cursor_delete_wasm(this.tree._addr);
    }

    reset(node: Node): void {
      marshalNode(node);
      marshalTreeCursor(this, TRANSFER_BUFFER + SIZE_OF_NODE);
      C._ts_tree_cursor_reset_wasm(this.tree._addr);
      unmarshalTreeCursor(this);
    }

    get nodeType(): string {
      return this.tree.language.types[this.nodeTypeId] || 'ERROR';
    }

    get nodeTypeId(): number {
      marshalTreeCursor(this);
      return C._ts_tree_cursor_current_node_type_id_wasm(this.tree._addr);
    }

    get nodeId(): number {
      marshalTreeCursor(this);
      return C._ts_tree_cursor_current_node_id_wasm(this.tree._addr);
    }

    get nodeIsNamed(): boolean {
      marshalTreeCursor(this);
      return C._ts_tree_cursor_current_node_is_named_wasm(this.tree._addr) === 1;
    }

    get nodeIsMissing(): boolean {
      marshalTreeCursor(this);
      return C._ts_tree_cursor_current_node_is_missing_wasm(this.tree._addr) === 1;
    }

    get nodeText(): string {
      marshalTreeCursor(this);
      const startIndex = C._ts_tree_cursor_start_index_wasm(this.tree._addr);
      const endIndex = C._ts_tree_cursor_end_index_wasm(this.tree._addr);
      return getText(this.tree, startIndex, endIndex);
    }

    get startPosition(): Point {
      marshalTreeCursor(this);
      C._ts_tree_cursor_start_position_wasm(this.tree._addr);
      return unmarshalPoint(TRANSFER_BUFFER);
    }

    get endPosition(): Point {
      marshalTreeCursor(this);
      C._ts_tree_cursor_end_position_wasm(this.tree._addr);
      return unmarshalPoint(TRANSFER_BUFFER);
    }

    get startIndex(): number {
      marshalTreeCursor(this);
      return C._ts_tree_cursor_start_index_wasm(this.tree._addr);
    }

    get endIndex(): number {
      marshalTreeCursor(this);
      return C._ts_tree_cursor_end_index_wasm(this.tree._addr);
    }

    currentNode(): Node {
      marshalTreeCursor(this);
      C._ts_tree_cursor_current_node_wasm(this.tree._addr);
      return unmarshalNode(this.tree)!;
    }

    currentFieldId(): number {
      marshalTreeCursor(this);
      return C._ts_tree_cursor_current_field_id_wasm(this.tree._addr);
    }

    currentFieldName(): string | null {
      const name = this.tree.language.fields[this.currentFieldId()];
      return name;
    }

    gotoFirstChild(): boolean {
      marshalTreeCursor(this);
      const result = C._ts_tree_cursor_goto_first_child_wasm(this.tree._addr);
      unmarshalTreeCursor(this);
      return result === 1;
    }

    gotoNextSibling(): boolean {
      marshalTreeCursor(this);
      const result = C._ts_tree_cursor_goto_next_sibling_wasm(this.tree._addr);
      unmarshalTreeCursor(this);
      return result === 1;
    }

    gotoParent(): boolean {
      marshalTreeCursor(this);
      const result = C._ts_tree_cursor_goto_parent_wasm(this.tree._addr);
      unmarshalTreeCursor(this);
      return result === 1;
    }
  }

  const enum QueryErrorType {
    Syntax = 1,
    NodeType,
    Field,
    Capture
  }

  // TODO: These types can be cleaned up
  const enum PredicateStepType {
    Done,
    Capture,
    String
  }
  type CapturePredicate = (captures: Capture[]) => boolean;
  type PredicateCaptureStep = {
    type: string;
    name: string;
  };
  type PredicateStringStep = {
    type: string;
    value: string;
  };
  type PredicateStep = PredicateCaptureStep | PredicateStringStep;

  // TODO: Any way to make this not ugly?
  interface QueryError extends Error {
    index?: number;
    length?: number;
  }

  const QUERY_WORD_REGEX = /[\w-.]*/g;

  export type Properties = Record<string, string | null>;

  const LANGUAGE_FUNCTION_REGEX = /^_?tree_sitter_\w+/;

  export class Language {
    _addr: number;
    types: Array<string>;
    fields: Array<string | null>;
    constructor(internal: {}, address: number) {
      assertInternal(internal);
      this._addr = address;
      this.types = new Array(C._ts_language_symbol_count(this._addr));
      for (let i = 0, n = this.types.length; i < n; i++) {
        if (C._ts_language_symbol_type(this._addr, i) < 2) {
          this.types[i] = C.UTF8ToString(C._ts_language_symbol_name(this._addr, i));
        }
      }
      this.fields = new Array(C._ts_language_field_count(this._addr) + 1);
      for (let i = 0, n = this.fields.length; i < n; i++) {
        const fieldName = C._ts_language_field_name_for_id(this._addr, i);
        if (fieldName !== 0) {
          this.fields[i] = C.UTF8ToString(fieldName);
        } else {
          this.fields[i] = null;
        }
      }
    }

    get version(): number {
      return C._ts_language_version(this._addr);
    }

    get fieldCount(): number {
      return this.fields.length - 1;
    }

    fieldIdForName(fieldName: string): number | null {
      const result = this.fields.indexOf(fieldName);
      return result !== -1 ? result : null;
    }

    fieldNameForId(fieldId: number): string | null {
      return this.fields[fieldId] || null;
    }

    query(source: string): Query {
      const sourceLength = C.lengthBytesUTF8(source);
      const sourceAddress = C._malloc(sourceLength + 1);
      C.stringToUTF8(source, sourceAddress, sourceLength + 1);
      const address = C._ts_query_new(
        this._addr,
        sourceAddress,
        sourceLength,
        TRANSFER_BUFFER,
        TRANSFER_BUFFER + SIZE_OF_INT
      );

      if (!address) {
        const errorId = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32') as QueryErrorType;
        const errorByte = C.getValue(TRANSFER_BUFFER, 'i32');
        const errorIndex = C.UTF8ToString(sourceAddress, errorByte).length;
        const suffix = source.substr(errorIndex, 100);
        const word = suffix.match(QUERY_WORD_REGEX)![0];
        let error: QueryError;
        switch (errorId) {
          case QueryErrorType.NodeType:
            error = new RangeError(`Bad node name '${word}'`);
            break;
          case QueryErrorType.Field:
            error = new RangeError(`Bad field name '${word}'`);
            break;
          case QueryErrorType.Capture:
            error = new RangeError(`Bad capture name @${word}`);
            break;
          default:
            // QueryErrorType.Syntax
            error = new SyntaxError(`Bad syntax at offset ${errorIndex}: '${suffix}'...`);
            break;
        }
        error.index = errorIndex;
        error.length = word.length;
        C._free(sourceAddress);
        throw error;
      }

      const stringCount = C._ts_query_string_count(address);
      const captureCount = C._ts_query_capture_count(address);
      const patternCount = C._ts_query_pattern_count(address);
      const captureNames = new Array<string>(captureCount);
      const stringValues = new Array<string>(stringCount);

      for (let i = 0; i < captureCount; i++) {
        const nameAddress = C._ts_query_capture_name_for_id(address, i, TRANSFER_BUFFER);
        const nameLength = C.getValue(TRANSFER_BUFFER, 'i32');
        captureNames[i] = C.UTF8ToString(nameAddress, nameLength);
      }

      for (let i = 0; i < stringCount; i++) {
        const valueAddress = C._ts_query_string_value_for_id(address, i, TRANSFER_BUFFER);
        const nameLength = C.getValue(TRANSFER_BUFFER, 'i32');
        stringValues[i] = C.UTF8ToString(valueAddress, nameLength);
      }

      const setProperties: Properties[] = new Array(patternCount);
      const assertedProperties: Properties[] = new Array(patternCount);
      const refutedProperties: Properties[] = new Array(patternCount);
      const predicates = new Array<CapturePredicate[]>(patternCount);
      for (let i = 0; i < patternCount; i++) {
        const predicatesAddress = C._ts_query_predicates_for_pattern(address, i, TRANSFER_BUFFER);
        const stepCount = C.getValue(TRANSFER_BUFFER, 'i32');

        predicates[i] = [];

        const steps: PredicateStep[] = [];
        let stepAddress = predicatesAddress;
        for (let j = 0; j < stepCount; j++) {
          const stepType = C.getValue(stepAddress, 'i32');
          stepAddress += SIZE_OF_INT;
          const stepValueId = C.getValue(stepAddress, 'i32');
          stepAddress += SIZE_OF_INT;
          if (stepType === PredicateStepType.Capture) {
            steps.push({ type: 'capture', name: captureNames[stepValueId] });
          } else if (stepType === PredicateStepType.String) {
            steps.push({ type: 'string', value: stringValues[stepValueId] });
          } else if (steps.length > 0) {
            if (steps[0].type !== 'string') {
              throw new Error('Predicates must begin with a literal value');
            }
            const operator = (steps[0] as PredicateStringStep).value;
            switch (operator) {
              case 'not-eq?':
              case 'eq?': {
                const isPositive = operator !== 'not-eq?';
                if (steps.length !== 3) {
                  throw new Error(
                    `Wrong number of arguments to \`eq?\` predicate. Expected 2, got ${steps.length - 1}`
                  );
                }
                if (steps[1].type !== 'capture') {
                  throw new Error(
                    `First argument of \`eq?\` predicate must be a capture. Got "${
                      (steps[1] as PredicateStringStep).value
                    }"`
                  );
                }
                if (steps[2].type === 'capture') {
                  const captureName1 = (steps[1] as PredicateCaptureStep).name;
                  const captureName2 = (steps[2] as PredicateCaptureStep).name;
                  predicates[i].push(function(captures) {
                    let node1: Node | null = null;
                    let node2: Node | null = null;
                    for (const c of captures) {
                      if (c.name === captureName1) node1 = c.node;
                      if (c.name === captureName2) node2 = c.node;
                    }
                    return (node1!.text === node2!.text) === isPositive;
                  });
                } else {
                  const captureName = (steps[1] as PredicateCaptureStep).name;
                  const stringValue = (steps[2] as PredicateStringStep).value;
                  predicates[i].push(function(captures) {
                    for (const c of captures) {
                      if (c.name === captureName) {
                        return (c.node.text === stringValue) === isPositive;
                      }
                    }
                    return false;
                  });
                }
                break;
              }
              case 'match?': {
                if (steps.length !== 3) {
                  throw new Error(
                    `Wrong number of arguments to \`match?\` predicate. Expected 2, got ${steps.length - 1}.`
                  );
                }
                if (steps[1].type !== 'capture') {
                  throw new Error(
                    `First argument of \`match?\` predicate must be a capture. Got "${
                      (steps[1] as PredicateStringStep).value
                    }".`
                  );
                }
                if (steps[2].type !== 'string') {
                  throw new Error(
                    `Second argument of \`match?\` predicate must be a string. Got @${
                      (steps[2] as PredicateCaptureStep).name
                    }.`
                  );
                }
                const captureName = (steps[1] as PredicateCaptureStep).name;
                const regex = new RegExp((steps[2] as PredicateStringStep).value);
                predicates[i].push(function(captures) {
                  for (const c of captures) {
                    if (c.name === captureName) return regex.test(c.node.text);
                  }
                  return false;
                });
                break;
              }
              case 'set!':
                if (steps.length < 2 || steps.length > 3) {
                  throw new Error(
                    `Wrong number of arguments to \`set!\` predicate. Expected 1 or 2. Got ${steps.length - 1}.`
                  );
                }
                if (steps.some(s => s.type !== 'string')) {
                  throw new Error('Arguments to `set!` predicate must be a strings.".');
                }
                if (!setProperties[i]) setProperties[i] = {};
                setProperties[i][(steps[1] as PredicateStringStep).value] = steps[2]
                  ? (steps[2] as PredicateStringStep).value
                  : null;
                break;

              case 'is?':
              case 'is-not?': {
                if (steps.length < 2 || steps.length > 3) {
                  throw new Error(
                    `Wrong number of arguments to \`${operator}\` predicate. Expected 1 or 2. Got ${steps.length - 1}.`
                  );
                }
                if (steps.some(s => s.type !== 'string')) {
                  throw new Error(`Arguments to \`${operator}\` predicate must be a strings.".`);
                }
                const properties = operator === 'is?' ? assertedProperties : refutedProperties;
                if (!properties[i]) properties[i] = {};
                properties[i][(steps[1] as PredicateStringStep).value] = steps[2]
                  ? (steps[2] as PredicateStringStep).value
                  : null;
                break;
              }
              default:
                throw new Error(`Unknown query predicate \`${(steps[0] as PredicateStringStep).value}\``);
            }

            steps.length = 0;
          }
        }

        Object.freeze(setProperties[i]);
        Object.freeze(assertedProperties[i]);
        Object.freeze(refutedProperties[i]);
      }

      C._free(sourceAddress);
      return new Query(
        INTERNAL,
        address,
        captureNames,
        predicates,
        Object.freeze(setProperties),
        Object.freeze(assertedProperties),
        Object.freeze(refutedProperties)
      );
    }

    static load(path: string): Promise<Language> {
      let bytes: Promise<Uint8Array>;
      if (typeof process !== 'undefined' && process.versions && process.versions.node) {
        // eslint-disable-next-line @typescript-eslint/no-var-requires
        const fs: typeof _fs = require('fs');
        bytes = Promise.resolve(fs.readFileSync(path));
      } else {
        bytes = fetch(path).then(response =>
          response.arrayBuffer().then(buffer => {
            if (response.ok) {
              return new Uint8Array(buffer);
            } else {
              const body = new TextDecoder('utf-8').decode(buffer);
              throw new Error(`Language.load failed with status ${response.status}.\n\n${body}`);
            }
          })
        );
      }

      return bytes
        .then(bytes => C.loadWebAssemblyModule(bytes, { loadAsync: true }))
        .then(mod => {
          const functionName = Object.keys(mod).find(
            key => LANGUAGE_FUNCTION_REGEX.test(key) && !key.includes('external_scanner_')
          );
          const languageAddress = (mod as Record<string, () => number>)[functionName!](); // TODO: Better error handling for bad wasm?
          return new Language(INTERNAL, languageAddress);
        });
    }
  }

  export type Match = {
    pattern: number;
    captures: Capture[];
    setProperties?: Properties;
    assertedProperties?: Properties;
    refutedProperties?: Properties;
  };
  export type Capture = {
    name: string;
    node: Node;
    setProperties?: Properties;
    assertedProperties?: Properties;
    refutedProperties?: Properties;
  };

  export class Query {
    _addr: number;
    captureNames: string[];
    predicates: CapturePredicate[][];
    setProperties: readonly Properties[];
    assertedProperties: readonly Properties[];
    refutedProperties: readonly Properties[];

    constructor(
      internal: {},
      address: number,
      captureNames: string[],
      predicates: CapturePredicate[][],
      setProperties: readonly Properties[],
      assertedProperties: readonly Properties[],
      refutedProperties: readonly Properties[]
    ) {
      assertInternal(internal);
      this._addr = address;
      this.captureNames = captureNames;
      this.predicates = predicates;
      this.setProperties = setProperties;
      this.assertedProperties = assertedProperties;
      this.refutedProperties = refutedProperties;
    }

    delete(): void {
      C._ts_query_delete(this._addr);
    }

    matches(node: Node, startPosition: Point = ZERO_POINT, endPosition: Point = ZERO_POINT): Match[] {
      marshalNode(node);

      C._ts_query_matches_wasm(
        this._addr,
        node.tree._addr,
        startPosition.row,
        startPosition.column,
        endPosition.row,
        endPosition.column
      );

      const count = C.getValue(TRANSFER_BUFFER, 'i32');
      const startAddress = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
      const result = new Array<Match>(count);

      let address = startAddress;
      for (let i = 0; i < count; i++) {
        const pattern = C.getValue(address, 'i32');
        address += SIZE_OF_INT;
        const captureCount = C.getValue(address, 'i32');
        address += SIZE_OF_INT;

        const captures = new Array<Capture>(captureCount);
        address = unmarshalCaptures(this, node.tree, address, captures);
        if (this.predicates[pattern].every(p => p(captures))) {
          result[i] = { pattern, captures };
          const setProperties = this.setProperties[pattern];
          if (setProperties) result[i].setProperties = setProperties;
          const assertedProperties = this.assertedProperties[pattern];
          if (assertedProperties) result[i].assertedProperties = assertedProperties;
          const refutedProperties = this.refutedProperties[pattern];
          if (refutedProperties) result[i].refutedProperties = refutedProperties;
        }
      }

      C._free(startAddress);
      return result;
    }

    captures(node: Node, startPosition: Point = ZERO_POINT, endPosition: Point = ZERO_POINT): Capture[] {
      marshalNode(node);

      C._ts_query_captures_wasm(
        this._addr,
        node.tree._addr,
        startPosition.row,
        startPosition.column,
        endPosition.row,
        endPosition.column
      );

      const count = C.getValue(TRANSFER_BUFFER, 'i32');
      const startAddress = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
      const result = [];

      const captures: Capture[] = [];
      let address = startAddress;
      for (let i = 0; i < count; i++) {
        const pattern = C.getValue(address, 'i32');
        address += SIZE_OF_INT;
        const captureCount = C.getValue(address, 'i32');
        address += SIZE_OF_INT;
        const captureIndex = C.getValue(address, 'i32');
        address += SIZE_OF_INT;

        captures.length = captureCount;
        address = unmarshalCaptures(this, node.tree, address, captures);

        if (this.predicates[pattern].every(p => p(captures))) {
          const capture = captures[captureIndex];
          const setProperties = this.setProperties[pattern];
          if (setProperties) capture.setProperties = setProperties;
          const assertedProperties = this.assertedProperties[pattern];
          if (assertedProperties) capture.assertedProperties = assertedProperties;
          const refutedProperties = this.refutedProperties[pattern];
          if (refutedProperties) capture.refutedProperties = refutedProperties;
          result.push(capture);
        }
      }

      C._free(startAddress);
      return result;
    }
  }
}

export default Parser;

function marshalNode(node: Parser.Node): void {
  let address = TRANSFER_BUFFER;
  C.setValue(address, node.id, 'i32');
  C.setValue((address += SIZE_OF_INT), node.startIndex, 'i32');
  C.setValue((address += SIZE_OF_INT), node.startPosition.row, 'i32');
  C.setValue((address += SIZE_OF_INT), node.startPosition.column, 'i32');
  C.setValue((address += SIZE_OF_INT), node._addr, 'i32');
}
function unmarshalNode(tree: Parser.Tree, address: number = TRANSFER_BUFFER): Parser.Node | null {
  const id = C.getValue(address, 'i32');
  if (id === 0) return null;

  const index = C.getValue((address += SIZE_OF_INT), 'i32');
  const row = C.getValue((address += SIZE_OF_INT), 'i32');
  const column = C.getValue((address += SIZE_OF_INT), 'i32');
  const other = C.getValue((address += SIZE_OF_INT), 'i32');

  const result = new Parser.Node(INTERNAL, tree, id, { row, column }, index, other);

  return result;
}

function unmarshalCaptures(query: Parser.Query, tree: Parser.Tree, address: number, result: Parser.Capture[]): number {
  for (let i = 0, n = result.length; i < n; i++) {
    const captureIndex = C.getValue(address, 'i32');
    address += SIZE_OF_INT;
    const node = unmarshalNode(tree, address)!; // This should never be null because it came from the capture
    address += SIZE_OF_NODE;
    result[i] = { name: query.captureNames[captureIndex], node };
  }
  return address;
}

function marshalEdit(edit: Parser.Edit): void {
  let address = TRANSFER_BUFFER;
  marshalPoint(address, edit.startPosition);
  marshalPoint((address += SIZE_OF_POINT), edit.oldEndPosition);
  marshalPoint((address += SIZE_OF_POINT), edit.newEndPosition);
  C.setValue((address += SIZE_OF_POINT), edit.startIndex, 'i32');
  C.setValue((address += SIZE_OF_INT), edit.oldEndIndex, 'i32');
  C.setValue((address += SIZE_OF_INT), edit.newEndIndex, 'i32');
}

function marshalPoint(address: number, point: Parser.Point): void {
  C.setValue(address, point.row, 'i32');
  C.setValue(address + SIZE_OF_INT, point.column, 'i32');
}
function unmarshalPoint(address: number): Parser.Point {
  return {
    row: C.getValue(address, 'i32'),
    column: C.getValue(address + SIZE_OF_INT, 'i32')
  };
}

function marshalRange(address: number, range: Parser.Range): void {
  marshalPoint(address, range.startPosition);
  marshalPoint((address += SIZE_OF_POINT), range.endPosition);
  C.setValue((address += SIZE_OF_POINT), range.startIndex, 'i32');
  C.setValue(address + SIZE_OF_INT, range.endIndex, 'i32');
}
function unmarshalRange(address: number): Parser.Range {
  return {
    startPosition: unmarshalPoint(address),
    endPosition: unmarshalPoint((address += SIZE_OF_POINT)),
    startIndex: C.getValue((address += SIZE_OF_POINT), 'i32'),
    endIndex: C.getValue(address + SIZE_OF_INT, 'i32')
  };
}

function unmarshalTreeCursor(cursor: Parser.TreeCursor): void {
  cursor._id = C.getValue(TRANSFER_BUFFER + 0 * SIZE_OF_INT, 'i32');
  cursor._ctx[0] = C.getValue(TRANSFER_BUFFER + 1 * SIZE_OF_INT, 'i32');
  cursor._ctx[1] = C.getValue(TRANSFER_BUFFER + 2 * SIZE_OF_INT, 'i32');
}
function marshalTreeCursor(cursor: Parser.TreeCursor, address: number = TRANSFER_BUFFER): void {
  C.setValue(address + 0 * SIZE_OF_INT, cursor._id, 'i32');
  C.setValue(address + 1 * SIZE_OF_INT, cursor._ctx[0], 'i32');
  C.setValue(address + 2 * SIZE_OF_INT, cursor._ctx[1], 'i32');
}

function isPoint(point: Parser.Point): point is Parser.Point {
  return point && typeof point.row === 'number' && typeof point.column === 'number';
}

function getText(tree: Parser.Tree, startIndex: number, endIndex: number): string {
  const length = endIndex - startIndex;
  let result = tree.textCallback(startIndex, null, endIndex)!;
  // Since this is only called from Node.text() and TreeCursor.nodeText(), result should always be defined
  startIndex += result.length;
  while (startIndex < endIndex) {
    const string = tree.textCallback(startIndex, null, endIndex);
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
