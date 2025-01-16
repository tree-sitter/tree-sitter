import { INTERNAL, Internal, assertInternal, Point, SIZE_OF_NODE, SIZE_OF_CURSOR, C } from './constants';
import { marshalNode, marshalPoint, marshalTreeCursor, unmarshalNode, unmarshalPoint, unmarshalTreeCursor } from './marshal';
import { Node } from './node';
import { TRANSFER_BUFFER } from './parser';
import { getText, Tree } from './tree';

export class TreeCursor {
  // @ts-expect-error Internal handle for WASM
  private [0]: number;
  // @ts-expect-error Internal handle for WASM
  private [1]: number;
  // @ts-expect-error Internal handle for WASM
  private [2]: number;
  // @ts-expect-error Internal handle for WASM
  private [3]: number;

  private tree: Tree;

  constructor(internal: Internal, tree: Tree) {
    assertInternal(internal);
    this.tree = tree;
    unmarshalTreeCursor(this);
  }

  copy(): TreeCursor {
    const copy = new TreeCursor(INTERNAL, this.tree);
    C._ts_tree_cursor_copy_wasm(this.tree[0]);
    unmarshalTreeCursor(copy);
    return copy;
  }

  delete(): void {
    marshalTreeCursor(this);
    C._ts_tree_cursor_delete_wasm(this.tree[0]);
    this[0] = this[1] = this[2] = 0;
  }

  reset(node: Node): void {
    marshalNode(node);
    marshalTreeCursor(this, TRANSFER_BUFFER + SIZE_OF_NODE);
    C._ts_tree_cursor_reset_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
  }

  resetTo(cursor: TreeCursor): void {
    marshalTreeCursor(this, TRANSFER_BUFFER);
    marshalTreeCursor(cursor, TRANSFER_BUFFER + SIZE_OF_CURSOR);
    C._ts_tree_cursor_reset_to_wasm(this.tree[0], cursor.tree[0]);
    unmarshalTreeCursor(this);
  }

  get nodeType(): string {
    return this.tree.language.types[this.nodeTypeId] || 'ERROR';
  }

  get nodeTypeId(): number {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_type_id_wasm(this.tree[0]);
  }

  get nodeStateId(): number {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_state_id_wasm(this.tree[0]);
  }

  get nodeId(): number {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_id_wasm(this.tree[0]);
  }

  get nodeIsNamed(): boolean {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_is_named_wasm(this.tree[0]) === 1;
  }

  get nodeIsMissing(): boolean {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_node_is_missing_wasm(this.tree[0]) === 1;
  }

  get nodeText(): string {
    marshalTreeCursor(this);
    const startIndex = C._ts_tree_cursor_start_index_wasm(this.tree[0]);
    const endIndex = C._ts_tree_cursor_end_index_wasm(this.tree[0]);
    C._ts_tree_cursor_start_position_wasm(this.tree[0]);
    const startPosition = unmarshalPoint(TRANSFER_BUFFER);
    return getText(this.tree, startIndex, endIndex, startPosition);
  }

  get startPosition(): Point {
    marshalTreeCursor(this);
    C._ts_tree_cursor_start_position_wasm(this.tree[0]);
    return unmarshalPoint(TRANSFER_BUFFER);
  }

  get endPosition(): Point {
    marshalTreeCursor(this);
    C._ts_tree_cursor_end_position_wasm(this.tree[0]);
    return unmarshalPoint(TRANSFER_BUFFER);
  }

  get startIndex(): number {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_start_index_wasm(this.tree[0]);
  }

  get endIndex(): number {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_end_index_wasm(this.tree[0]);
  }

  get currentNode(): Node | null {
    marshalTreeCursor(this);
    C._ts_tree_cursor_current_node_wasm(this.tree[0]);
    return unmarshalNode(this.tree);
  }

  get currentFieldId(): number {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_field_id_wasm(this.tree[0]);
  }

  get currentFieldName(): string | null {
    return this.tree.language.fields[this.currentFieldId];
  }

  get currentDepth(): number {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_depth_wasm(this.tree[0]);
  }

  get currentDescendantIndex(): number {
    marshalTreeCursor(this);
    return C._ts_tree_cursor_current_descendant_index_wasm(this.tree[0]);
  }

  gotoFirstChild(): boolean {
    marshalTreeCursor(this);
    const result = C._ts_tree_cursor_goto_first_child_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }

  gotoLastChild(): boolean {
    marshalTreeCursor(this);
    const result = C._ts_tree_cursor_goto_last_child_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }

  gotoFirstChildForIndex(goalIndex: number): boolean {
    marshalTreeCursor(this);
    setValue(TRANSFER_BUFFER + SIZE_OF_CURSOR, goalIndex, 'i32');
    const result = C._ts_tree_cursor_goto_first_child_for_index_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }

  gotoFirstChildForPosition(goalPosition: Point): boolean {
    marshalTreeCursor(this);
    marshalPoint(TRANSFER_BUFFER + SIZE_OF_CURSOR, goalPosition);
    const result = C._ts_tree_cursor_goto_first_child_for_position_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }

  gotoNextSibling(): boolean {
    marshalTreeCursor(this);
    const result = C._ts_tree_cursor_goto_next_sibling_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }

  gotoPreviousSibling(): boolean {
    marshalTreeCursor(this);
    const result = C._ts_tree_cursor_goto_previous_sibling_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }

  gotoDescendant(goalDescendantIndex: number): void {
    marshalTreeCursor(this);
    C._ts_tree_cursor_goto_descendant_wasm(this.tree[0], goalDescendantIndex);
    unmarshalTreeCursor(this);
  }

  gotoParent(): boolean {
    marshalTreeCursor(this);
    const result = C._ts_tree_cursor_goto_parent_wasm(this.tree[0]);
    unmarshalTreeCursor(this);
    return result === 1;
  }
}
