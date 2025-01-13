import { Edit, INTERNAL, Point, Range, SIZE_OF_INT, SIZE_OF_NODE, SIZE_OF_POINT } from "./constants";
import { Node } from "./node";
import { Tree } from "./tree";
import { Query } from "./query";
import { TreeCursor } from "./tree_cursor";
import { TRANSFER_BUFFER } from "./parser";

export function unmarshalCaptures(query: Query, tree: Tree, address: number, result: Array<{name: string, node: Node}>) {
  for (let i = 0, n = result.length; i < n; i++) {
    const captureIndex = getValue(address, 'i32');
    address += SIZE_OF_INT;
    const node = unmarshalNode(tree, address)!;
    address += SIZE_OF_NODE;
    result[i] = {name: query.captureNames[captureIndex], node};
  }
  return address;
}

export function marshalNode(node: Node) {
  let address = TRANSFER_BUFFER;
  setValue(address, node.id, 'i32');
  address += SIZE_OF_INT;
  setValue(address, node.startIndex, 'i32');
  address += SIZE_OF_INT;
  setValue(address, node.startPosition.row, 'i32');
  address += SIZE_OF_INT;
  setValue(address, node.startPosition.column, 'i32');
  address += SIZE_OF_INT;
  setValue(address, node[0], 'i32');
}

export function unmarshalNode(tree: Tree, address = TRANSFER_BUFFER): Node | null {
  const id = getValue(address, 'i32');
  address += SIZE_OF_INT;
  if (id === 0) return null;

  const index = getValue(address, 'i32');
  address += SIZE_OF_INT;
  const row = getValue(address, 'i32');
  address += SIZE_OF_INT;
  const column = getValue(address, 'i32');
  address += SIZE_OF_INT;
  const other = getValue(address, 'i32');

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
  setValue(address + 0 * SIZE_OF_INT, cursor[0], 'i32');
  setValue(address + 1 * SIZE_OF_INT, cursor[1], 'i32');
  setValue(address + 2 * SIZE_OF_INT, cursor[2], 'i32');
  setValue(address + 3 * SIZE_OF_INT, cursor[3], 'i32');
}

export function unmarshalTreeCursor(cursor: TreeCursor) {
  cursor[0] = getValue(TRANSFER_BUFFER + 0 * SIZE_OF_INT, 'i32');
  cursor[1] = getValue(TRANSFER_BUFFER + 1 * SIZE_OF_INT, 'i32');
  cursor[2] = getValue(TRANSFER_BUFFER + 2 * SIZE_OF_INT, 'i32');
  cursor[3] = getValue(TRANSFER_BUFFER + 3 * SIZE_OF_INT, 'i32');
}

export function marshalPoint(address: number, point: Point): void {
  setValue(address, point.row, 'i32');
  setValue(address + SIZE_OF_INT, point.column, 'i32');
}

export function unmarshalPoint(address: number): Point {
  const result = {
    row: getValue(address, 'i32') >>> 0,
    column: getValue(address + SIZE_OF_INT, 'i32') >>> 0,
  };
  return result;
}

export function marshalRange(address: number, range: Range): void {
  marshalPoint(address, range.startPosition); address += SIZE_OF_POINT;
  marshalPoint(address, range.endPosition); address += SIZE_OF_POINT;
  setValue(address, range.startIndex, 'i32'); address += SIZE_OF_INT;
  setValue(address, range.endIndex, 'i32'); address += SIZE_OF_INT;
}

export function unmarshalRange(address: number): Range {
  const result = {} as Range;
  result.startPosition = unmarshalPoint(address); address += SIZE_OF_POINT;
  result.endPosition = unmarshalPoint(address); address += SIZE_OF_POINT;
  result.startIndex = getValue(address, 'i32') >>> 0; address += SIZE_OF_INT;
  result.endIndex = getValue(address, 'i32') >>> 0;
  return result;
}

export function marshalEdit(edit: Edit, address = TRANSFER_BUFFER) {
  marshalPoint(address, edit.startPosition); address += SIZE_OF_POINT;
  marshalPoint(address, edit.oldEndPosition); address += SIZE_OF_POINT;
  marshalPoint(address, edit.newEndPosition); address += SIZE_OF_POINT;
  setValue(address, edit.startIndex, 'i32'); address += SIZE_OF_INT;
  setValue(address, edit.oldEndIndex, 'i32'); address += SIZE_OF_INT;
  setValue(address, edit.newEndIndex, 'i32'); address += SIZE_OF_INT;
}
