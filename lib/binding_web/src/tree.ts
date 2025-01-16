import { INTERNAL, Internal, assertInternal, ParseCallback, Point, Range, Edit, SIZE_OF_NODE, SIZE_OF_INT, SIZE_OF_RANGE, C } from './constants';
import { Language } from './language';
import { Node } from './node';
import { TreeCursor } from './tree_cursor';
import { marshalEdit, marshalPoint, unmarshalNode, unmarshalRange } from './marshal';
import { TRANSFER_BUFFER } from './parser';

export function getText(tree: Tree, startIndex: number, endIndex: number, startPosition: Point): string {
  const length = endIndex - startIndex;
  let result = tree.textCallback(startIndex, startPosition);
  if (result) {
    startIndex += result.length;
    while (startIndex < endIndex) {
      const string = tree.textCallback(startIndex, startPosition);
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
  }
  return result ?? '';
}

export class Tree {
  private [0]: number; // Internal handle for WASM

  textCallback: ParseCallback;
  language: Language;

  constructor(internal: Internal, address: number, language: Language, textCallback: ParseCallback) {
    assertInternal(internal);
    this[0] = address;
    this.language = language;
    this.textCallback = textCallback;
  }

  copy(): Tree {
    const address = C._ts_tree_copy(this[0]);
    return new Tree(INTERNAL, address, this.language, this.textCallback);
  }

  delete(): void {
    C._ts_tree_delete(this[0]);
    this[0] = 0;
  }

  edit(edit: Edit): void {
    marshalEdit(edit);
    C._ts_tree_edit_wasm(this[0]);
  }

  get rootNode(): Node {
    C._ts_tree_root_node_wasm(this[0]);
    return unmarshalNode(this)!;
  }

  rootNodeWithOffset(offsetBytes: number, offsetExtent: Point): Node {
    const address = TRANSFER_BUFFER + SIZE_OF_NODE;
    setValue(address, offsetBytes, 'i32');
    marshalPoint(address + SIZE_OF_INT, offsetExtent);
    C._ts_tree_root_node_with_offset_wasm(this[0]);
    return unmarshalNode(this)!;
  }

  getLanguage(): Language {
    return this.language;
  }

  walk(): TreeCursor {
    return this.rootNode.walk();
  }

  getChangedRanges(other: Tree): Range[] {
    if (!(other instanceof Tree)) {
      throw new TypeError('Argument must be a Tree');
    }

    C._ts_tree_get_changed_ranges_wasm(this[0], other[0]);
    const count = getValue(TRANSFER_BUFFER, 'i32');
    const buffer = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array<Range>(count);

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

  getIncludedRanges(): Range[] {
    C._ts_tree_included_ranges_wasm(this[0]);
    const count = getValue(TRANSFER_BUFFER, 'i32');
    const buffer = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array<Range>(count);

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
