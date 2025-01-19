import { Edit, INTERNAL, Point, Range, SIZE_OF_INT, SIZE_OF_NODE, SIZE_OF_POINT, C } from "./constants";
import { Node } from "./node";
import { Tree } from "./tree";
import { Query } from "./query";
import { TreeCursor } from "./tree_cursor";
import { TRANSFER_BUFFER } from "./parser";

export function unmarshalCaptures(query: Query, tree: Tree, address: number, result: {name: string, node: Node}[]) {
  for (let i = 0, n = result.length; i < n; i++) {
    const captureIndex = C.getValue(address, 'i32');
    address += SIZE_OF_INT;
    const node = unmarshalNode(tree, address)!;
    address += SIZE_OF_NODE;
    result[i] = {name: query.captureNames[captureIndex], node};
  }
  return address;
}

export function marshalNode(node: Node) {
  let address = TRANSFER_BUFFER;
  C.setValue(address, node.id, 'i32');
  address += SIZE_OF_INT;
  C.setValue(address, node.startIndex, 'i32');
  address += SIZE_OF_INT;
  C.setValue(address, node.startPosition.row, 'i32');
  address += SIZE_OF_INT;
  C.setValue(address, node.startPosition.column, 'i32');
  address += SIZE_OF_INT;
  C.setValue(address, node[0], 'i32');
}

export function unmarshalNode(tree: Tree, address = TRANSFER_BUFFER): Node | null {
  const id = C.getValue(address, 'i32');
  address += SIZE_OF_INT;
  if (id === 0) return null;

  const index = C.getValue(address, 'i32');
  address += SIZE_OF_INT;
  const row = C.getValue(address, 'i32');
  address += SIZE_OF_INT;
  const column = C.getValue(address, 'i32');
  address += SIZE_OF_INT;
  const other = C.getValue(address, 'i32');

  const result = new Node(INTERNAL, {
    id,
    tree,
    startIndex: index,
    startPosition: {row, column},
    other,
  });

  return result;
}

export function marshalTreeCursor(cursor: TreeCursor, address = TRANSFER_BUFFER) {
  C.setValue(address + 0 * SIZE_OF_INT, cursor[0], 'i32');
  C.setValue(address + 1 * SIZE_OF_INT, cursor[1], 'i32');
  C.setValue(address + 2 * SIZE_OF_INT, cursor[2], 'i32');
  C.setValue(address + 3 * SIZE_OF_INT, cursor[3], 'i32');
}

export function unmarshalTreeCursor(cursor: TreeCursor) {
  cursor[0] = C.getValue(TRANSFER_BUFFER + 0 * SIZE_OF_INT, 'i32');
  cursor[1] = C.getValue(TRANSFER_BUFFER + 1 * SIZE_OF_INT, 'i32');
  cursor[2] = C.getValue(TRANSFER_BUFFER + 2 * SIZE_OF_INT, 'i32');
  cursor[3] = C.getValue(TRANSFER_BUFFER + 3 * SIZE_OF_INT, 'i32');
}

export function marshalPoint(address: number, point: Point): void {
  C.setValue(address, point.row, 'i32');
  C.setValue(address + SIZE_OF_INT, point.column, 'i32');
}

export function unmarshalPoint(address: number): Point {
  const result = {
    row: C.getValue(address, 'i32') >>> 0,
    column: C.getValue(address + SIZE_OF_INT, 'i32') >>> 0,
  };
  return result;
}

export function marshalRange(address: number, range: Range): void {
  marshalPoint(address, range.startPosition); address += SIZE_OF_POINT;
  marshalPoint(address, range.endPosition); address += SIZE_OF_POINT;
  C.setValue(address, range.startIndex, 'i32'); address += SIZE_OF_INT;
  C.setValue(address, range.endIndex, 'i32'); address += SIZE_OF_INT;
}

export function unmarshalRange(address: number): Range {
  const result = {} as Range;
  result.startPosition = unmarshalPoint(address); address += SIZE_OF_POINT;
  result.endPosition = unmarshalPoint(address); address += SIZE_OF_POINT;
  result.startIndex = C.getValue(address, 'i32') >>> 0; address += SIZE_OF_INT;
  result.endIndex = C.getValue(address, 'i32') >>> 0;
  return result;
}

export function marshalEdit(edit: Edit, address = TRANSFER_BUFFER) {
  marshalPoint(address, edit.startPosition); address += SIZE_OF_POINT;
  marshalPoint(address, edit.oldEndPosition); address += SIZE_OF_POINT;
  marshalPoint(address, edit.newEndPosition); address += SIZE_OF_POINT;
  C.setValue(address, edit.startIndex, 'i32'); address += SIZE_OF_INT;
  C.setValue(address, edit.oldEndIndex, 'i32'); address += SIZE_OF_INT;
  C.setValue(address, edit.newEndIndex, 'i32'); address += SIZE_OF_INT;
}
