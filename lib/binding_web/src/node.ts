import { INTERNAL, Internal, assertInternal, Point, Edit, SIZE_OF_INT, SIZE_OF_NODE, SIZE_OF_POINT, ZERO_POINT, isPoint, C } from './constants';
import { getText, Tree } from './tree';
import { TreeCursor } from './tree_cursor';
import { marshalNode, marshalPoint, unmarshalNode, unmarshalPoint } from './marshal';
import { TRANSFER_BUFFER } from './parser';

export class Node {
  /** @internal */
  private [0] = 0; // Internal handle for WASM

  /** @internal */
  private _children?: (Node | null)[];

  /** @internal */
  private _namedChildren?: (Node | null)[];

  id!: number;
  startIndex!: number;
  startPosition!: Point;
  tree: Tree;

  constructor(
    internal: Internal,
    {
      id,
      tree,
      startIndex,
      startPosition,
      other,
    }: {
      id: number;
      tree: Tree;
      startIndex: number;
      startPosition: Point;
      other: number;
    }
  ) {
    assertInternal(internal);
    this[0] = other;
    this.id = id;
    this.tree = tree;
    this.startIndex = startIndex;
    this.startPosition = startPosition;
  }

  get typeId(): number {
    marshalNode(this);
    return C._ts_node_symbol_wasm(this.tree[0]);
  }

  get grammarId(): number {
    marshalNode(this);
    return C._ts_node_grammar_symbol_wasm(this.tree[0]);
  }

  get type(): string {
    return this.tree.language.types[this.typeId] || 'ERROR';
  }

  get grammarType(): string {
    return this.tree.language.types[this.grammarId] || 'ERROR';
  }

  get endPosition(): Point {
    marshalNode(this);
    C._ts_node_end_point_wasm(this.tree[0]);
    return unmarshalPoint(TRANSFER_BUFFER);
  }

  get endIndex(): number {
    marshalNode(this);
    return C._ts_node_end_index_wasm(this.tree[0]);
  }

  get text(): string {
    return getText(this.tree, this.startIndex, this.endIndex, this.startPosition);
  }

  get parseState(): number {
    marshalNode(this);
    return C._ts_node_parse_state_wasm(this.tree[0]);
  }

  get nextParseState(): number {
    marshalNode(this);
    return C._ts_node_next_parse_state_wasm(this.tree[0]);
  }

  get isNamed(): boolean {
    marshalNode(this);
    return C._ts_node_is_named_wasm(this.tree[0]) === 1;
  }

  get hasError(): boolean {
    marshalNode(this);
    return C._ts_node_has_error_wasm(this.tree[0]) === 1;
  }

  get hasChanges(): boolean {
    marshalNode(this);
    return C._ts_node_has_changes_wasm(this.tree[0]) === 1;
  }

  get isError(): boolean {
    marshalNode(this);
    return C._ts_node_is_error_wasm(this.tree[0]) === 1;
  }

  get isMissing(): boolean {
    marshalNode(this);
    return C._ts_node_is_missing_wasm(this.tree[0]) === 1;
  }

  get isExtra(): boolean {
    marshalNode(this);
    return C._ts_node_is_extra_wasm(this.tree[0]) === 1;
  }

  equals(other: Node): boolean {
    return this.tree === other.tree && this.id === other.id;
  }

  child(index: number): Node | null {
    marshalNode(this);
    C._ts_node_child_wasm(this.tree[0], index);
    return unmarshalNode(this.tree);
  }

  namedChild(index: number): Node | null {
    marshalNode(this);
    C._ts_node_named_child_wasm(this.tree[0], index);
    return unmarshalNode(this.tree);
  }

  childForFieldId(fieldId: number): Node | null {
    marshalNode(this);
    C._ts_node_child_by_field_id_wasm(this.tree[0], fieldId);
    return unmarshalNode(this.tree);
  }

  childForFieldName(fieldName: string): Node | null {
    const fieldId = this.tree.language.fields.indexOf(fieldName);
    if (fieldId !== -1) return this.childForFieldId(fieldId);
    return null;
  }

  fieldNameForChild(index: number): string | null {
    marshalNode(this);
    const address = C._ts_node_field_name_for_child_wasm(this.tree[0], index);
    if (!address) return null;
    return C.AsciiToString(address);
  }

  fieldNameForNamedChild(index: number): string | null {
    marshalNode(this);
    const address = C._ts_node_field_name_for_named_child_wasm(this.tree[0], index);
    if (!address) return null;
    return C.AsciiToString(address);
  }

  childrenForFieldName(fieldName: string): (Node | null)[] {
    const fieldId = this.tree.language.fields.indexOf(fieldName);
    if (fieldId !== -1 && fieldId !== 0) return this.childrenForFieldId(fieldId);
    return [];
  }

  childrenForFieldId(fieldId: number): (Node | null)[] {
    marshalNode(this);
    C._ts_node_children_by_field_id_wasm(this.tree[0], fieldId);
    const count = C.getValue(TRANSFER_BUFFER, 'i32');
    const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array<Node | null>(count);

    if (count > 0) {
      let address = buffer;
      for (let i = 0; i < count; i++) {
        result[i] = unmarshalNode(this.tree, address);
        address += SIZE_OF_NODE;
      }
      C._free(buffer);
    }
    return result;
  }

  firstChildForIndex(index: number): Node | null {
    marshalNode(this);
    const address = TRANSFER_BUFFER + SIZE_OF_NODE;
    C.setValue(address, index, 'i32');
    C._ts_node_first_child_for_byte_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  firstNamedChildForIndex(index: number): Node | null {
    marshalNode(this);
    const address = TRANSFER_BUFFER + SIZE_OF_NODE;
    C.setValue(address, index, 'i32');
    C._ts_node_first_named_child_for_byte_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get childCount(): number {
    marshalNode(this);
    return C._ts_node_child_count_wasm(this.tree[0]);
  }

  get namedChildCount(): number {
    marshalNode(this);
    return C._ts_node_named_child_count_wasm(this.tree[0]);
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

  get children(): (Node | null)[] {
    if (!this._children) {
      marshalNode(this);
      C._ts_node_children_wasm(this.tree[0]);
      const count = C.getValue(TRANSFER_BUFFER, 'i32');
      const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
      this._children = new Array<Node>(count);
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

  get namedChildren(): (Node | null)[] {
    if (!this._namedChildren) {
      marshalNode(this);
      C._ts_node_named_children_wasm(this.tree[0]);
      const count = C.getValue(TRANSFER_BUFFER, 'i32');
      const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
      this._namedChildren = new Array<Node>(count);
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

  descendantsOfType(
    types: string | string[],
    startPosition: Point = ZERO_POINT,
    endPosition: Point = ZERO_POINT
  ): (Node | null)[] {
    if (!Array.isArray(types)) types = [types];

    // Convert the type strings to numeric type symbols
    const symbols: number[] = [];
    const typesBySymbol = this.tree.language.types;
    for (let i = 0, n = typesBySymbol.length; i < n; i++) {
      if (types.includes(typesBySymbol[i])) {
        symbols.push(i);
      }
    }

    // Copy the array of symbols to the WASM heap
    const symbolsAddress = C._malloc(SIZE_OF_INT * symbols.length);
    for (let i = 0, n = symbols.length; i < n; i++) {
      C.setValue(symbolsAddress + i * SIZE_OF_INT, symbols[i], 'i32');
    }

    // Call the C API to compute the descendants
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

    // Instantiate the nodes based on the data returned
    const descendantCount = C.getValue(TRANSFER_BUFFER, 'i32');
    const descendantAddress = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array<Node | null>(descendantCount);
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
    C._ts_node_next_sibling_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get previousSibling(): Node | null {
    marshalNode(this);
    C._ts_node_prev_sibling_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get nextNamedSibling(): Node | null {
    marshalNode(this);
    C._ts_node_next_named_sibling_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get previousNamedSibling(): Node | null {
    marshalNode(this);
    C._ts_node_prev_named_sibling_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get descendantCount(): number {
    marshalNode(this);
    return C._ts_node_descendant_count_wasm(this.tree[0]);
  }

  get parent(): Node | null {
    marshalNode(this);
    C._ts_node_parent_wasm(this.tree[0]);
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
    C._ts_node_descendant_for_index_wasm(this.tree[0]);
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
    C._ts_node_named_descendant_for_index_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  descendantForPosition(start: Point, end: Point = start) {
    if (!isPoint(start) || !isPoint(end)) {
      throw new Error('Arguments must be {row, column} objects');
    }

    marshalNode(this);
    const address = TRANSFER_BUFFER + SIZE_OF_NODE;
    marshalPoint(address, start);
    marshalPoint(address + SIZE_OF_POINT, end);
    C._ts_node_descendant_for_position_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  namedDescendantForPosition(start: Point, end: Point = start) {
    if (!isPoint(start) || !isPoint(end)) {
      throw new Error('Arguments must be {row, column} objects');
    }

    marshalNode(this);
    const address = TRANSFER_BUFFER + SIZE_OF_NODE;
    marshalPoint(address, start);
    marshalPoint(address + SIZE_OF_POINT, end);
    C._ts_node_named_descendant_for_position_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  walk(): TreeCursor {
    marshalNode(this);
    C._ts_tree_cursor_new_wasm(this.tree[0]);
    return new TreeCursor(INTERNAL, this.tree);
  }

  edit(edit: Edit) {
    if (this.startIndex >= edit.oldEndIndex) {
      this.startIndex = edit.newEndIndex + (this.startIndex - edit.oldEndIndex);
      let subbedPointRow;
      let subbedPointColumn;
      if (this.startPosition.row > edit.oldEndPosition.row) {
        subbedPointRow = this.startPosition.row - edit.oldEndPosition.row;
        subbedPointColumn = this.startPosition.column;
      } else {
        subbedPointRow = 0;
        subbedPointColumn = this.startPosition.column;
        if (this.startPosition.column >= edit.oldEndPosition.column) {
          subbedPointColumn =
            this.startPosition.column - edit.oldEndPosition.column;
        }
      }

      if (subbedPointRow > 0) {
        this.startPosition.row += subbedPointRow;
        this.startPosition.column = subbedPointColumn;
      } else {
        this.startPosition.column += subbedPointColumn;
      }
    } else if (this.startIndex > edit.startIndex) {
      this.startIndex = edit.newEndIndex;
      this.startPosition.row = edit.newEndPosition.row;
      this.startPosition.column = edit.newEndPosition.column;
    }
  }

  toString() {
    marshalNode(this);
    const address = C._ts_node_to_string_wasm(this.tree[0]);
    const result = C.AsciiToString(address);
    C._free(address);
    return result;
  }
}
