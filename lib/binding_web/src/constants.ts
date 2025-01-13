import { CaptureQuantifier } from "./query";

export interface Point {
  row: number;
  column: number;
}

export interface Range {
  startPosition: Point;
  endPosition: Point;
  startIndex: number;
  endIndex: number;
}

export interface Edit {
  startPosition: Point;
  oldEndPosition: Point;
  newEndPosition: Point;
  startIndex: number;
  oldEndIndex: number;
  newEndIndex: number;
}

export interface ParserOptions {
  includedRanges?: Range[];
  progressCallback?: (progress: { currentOffset: number }) => boolean;
}

export const SIZE_OF_SHORT = 2;
export const SIZE_OF_INT = 4;
export const SIZE_OF_CURSOR = 4 * SIZE_OF_INT;
export const SIZE_OF_NODE = 5 * SIZE_OF_INT;
export const SIZE_OF_POINT = 2 * SIZE_OF_INT;
export const SIZE_OF_RANGE = 2 * SIZE_OF_INT + 2 * SIZE_OF_POINT;
export const ZERO_POINT: Point = { row: 0, column: 0 };

// Types for callbacks
export type ParseCallback = (index: number, position: Point) => string | null;
export type ProgressCallback = (progress: { currentOffset: number }) => boolean;
export type LogCallback = (message: string, isLex: boolean) => void;

// Helper type for internal use
export const INTERNAL = Symbol('INTERNAL');
export type Internal = typeof INTERNAL;

// Helper functions for type checking
export function assertInternal(x: unknown): asserts x is Internal {
  if (x !== INTERNAL) throw new Error('Illegal constructor');
}

export function isPoint(point: Point): point is Point {
  return (
    !!point &&
    typeof (point as Point).row === 'number' &&
    typeof (point as Point).column === 'number'
  );
}

export const C: EmscriptenModule & {
  // Global
  _ts_init(): number;

  // Libc
  _malloc(size: number): number;
  _calloc(count: number, size: number): number;
  _free(ptr: number): void;

  // Parser
  _ts_parser_new_wasm(): void;
  _ts_parser_delete(address: number): void;
  _ts_parser_set_language(parserAddress: number, languageAddress: number): void;
  _ts_language_version(address: number): number;
  _ts_parser_enable_logger_wasm(address: number, enabled: number): void;
  _ts_parser_parse_wasm(
    address: number,
    payload: number,
    oldTreeAddress: number,
    rangeAddress: number,
    rangeCount: number
  ): number;
  _ts_parser_reset(address: number): void;
  _ts_parser_timeout_micros(address: number): number;
  _ts_parser_set_timeout_micros(address: number, timeout: number): void;
  _ts_parser_included_ranges_wasm(address: number): void;

  // Language
  _ts_language_symbol_count(address: number): number;
  _ts_language_symbol_name(address: number, index: number): number;
  _ts_language_symbol_type(address: number, index: number): number;
  _ts_language_field_count(address: number): number;
  _ts_language_field_name_for_id(address: number, id: number): number;
  _ts_language_name(address: number): number;
  _ts_language_version(address: number): number;
  _ts_language_state_count(address: number): number;
  _ts_language_symbol_for_name(address: number, typeAddress: number, typeLength: number, named: boolean): number;
  _ts_language_type_is_named_wasm(address: number, typeId: number): number;
  _ts_language_type_is_visible_wasm(address: number, typeId: number): number;
  _ts_language_next_state(address: number, stateId: number, typeId: number): number;
  _ts_language_supertypes_wasm(address: number): void;
  _ts_language_subtypes_wasm(address: number, supertype: number): void;

  // Tree
  _ts_tree_copy(tree: number): number;
  _ts_tree_delete(tree: number): void;
  _ts_tree_edit_wasm(tree: number): void;
  _ts_tree_root_node_wasm(tree: number): void;
  _ts_tree_root_node_with_offset_wasm(tree: number): void;
  _ts_tree_get_changed_ranges_wasm(self: number, other: number): void;
  _ts_tree_included_ranges_wasm(self: number): void;

  // Node
  _ts_node_symbol_wasm(tree: number): number;
  _ts_node_grammar_symbol_wasm(tree: number): number;
  _ts_node_end_point_wasm(tree: number): void;
  _ts_node_end_index_wasm(tree: number): number;
  _ts_node_parse_state_wasm(tree: number): number;
  _ts_node_next_parse_state_wasm(tree: number): number;
  _ts_node_is_named_wasm(tree: number): number;
  _ts_node_has_error_wasm(tree: number): number;
  _ts_node_has_changes_wasm(tree: number): number;
  _ts_node_is_error_wasm(tree: number): number;
  _ts_node_is_missing_wasm(tree: number): number;
  _ts_node_is_extra_wasm(tree: number): number;
  _ts_node_child_wasm(tree: number, index: number): void;
  _ts_node_named_child_wasm(tree: number, index: number): void;
  _ts_node_child_by_field_id_wasm(tree: number, fieldId: number): void;
  _ts_node_field_name_for_child_wasm(tree: number, index: number): number;
  _ts_node_field_name_for_named_child_wasm(tree: number, index: number): number;
  _ts_node_children_by_field_id_wasm(tree: number, fieldId: number): void;
  _ts_node_first_child_for_byte_wasm(tree: number): void;
  _ts_node_first_named_child_for_byte_wasm(tree: number): void;
  _ts_node_child_count_wasm(tree: number): number;
  _ts_node_named_child_count_wasm(tree: number): number;
  _ts_node_children_wasm(tree: number): void;
  _ts_node_named_children_wasm(tree: number): void;
  _ts_node_descendants_of_type_wasm(
    tree: number,
    symbolsAddress: number,
    symbolCount: number,
    startRow: number,
    startColumn: number,
    endRow: number,
    endColumn: number
  ): void;
  _ts_node_next_sibling_wasm(tree: number): void;
  _ts_node_prev_sibling_wasm(tree: number): void;
  _ts_node_next_named_sibling_wasm(tree: number): void;
  _ts_node_prev_named_sibling_wasm(tree: number): void;
  _ts_node_descendant_count_wasm(tree: number): number;
  _ts_node_parent_wasm(tree: number): void;
  _ts_node_descendant_for_index_wasm(tree: number): void;
  _ts_node_named_descendant_for_index_wasm(tree: number): void;
  _ts_node_descendant_for_position_wasm(tree: number): void;
  _ts_node_named_descendant_for_position_wasm(tree: number): void;
  _ts_tree_cursor_new_wasm(tree: number): void;
  _ts_node_to_string_wasm(tree: number): number;

  // TreeCursor
  _ts_tree_cursor_copy_wasm(cursor: number): void;
  _ts_tree_cursor_delete_wasm(cursor: number): void;
  _ts_tree_cursor_reset_wasm(cursor: number): void;
  _ts_tree_cursor_reset_to_wasm(cursor: number, other: number): void;
  _ts_tree_cursor_current_node_type_id_wasm(cursor: number): number;
  _ts_tree_cursor_current_node_state_id_wasm(cursor: number): number;
  _ts_tree_cursor_current_node_id_wasm(cursor: number): number;
  _ts_tree_cursor_current_node_is_named_wasm(cursor: number): number;
  _ts_tree_cursor_current_node_is_missing_wasm(cursor: number): number;
  _ts_tree_cursor_start_index_wasm(cursor: number): number;
  _ts_tree_cursor_end_index_wasm(cursor: number): number;
  _ts_tree_cursor_start_position_wasm(cursor: number): void;
  _ts_tree_cursor_end_position_wasm(cursor: number): void;
  _ts_tree_cursor_current_node_wasm(cursor: number): void;
  _ts_tree_cursor_current_field_id_wasm(cursor: number): number;
  _ts_tree_cursor_current_depth_wasm(cursor: number): number;
  _ts_tree_cursor_current_descendant_index_wasm(cursor: number): number;
  _ts_tree_cursor_goto_first_child_wasm(cursor: number): number;
  _ts_tree_cursor_goto_last_child_wasm(cursor: number): number;
  _ts_tree_cursor_goto_first_child_for_index_wasm(cursor: number): number;
  _ts_tree_cursor_goto_first_child_for_position_wasm(cursor: number): number;
  _ts_tree_cursor_goto_next_sibling_wasm(cursor: number): number;
  _ts_tree_cursor_goto_previous_sibling_wasm(cursor: number): number;
  _ts_tree_cursor_goto_descendant_wasm(cursor: number, index: number): void;
  _ts_tree_cursor_goto_parent_wasm(cursor: number): number;

  // Query
  _ts_query_new(languageAddress: number, sourceAddress: number, sourceLength: number, errorOffset: number, errorType: number): number;
  _ts_query_string_count(address: number): number;
  _ts_query_capture_count(address: number): number;
  _ts_query_pattern_count(address: number): number;
  _ts_query_capture_name_for_id(address: number, id: number, buffer: number): number;
  _ts_query_capture_quantifier_for_id(address: number, patternId: number, captureId: number): CaptureQuantifier;
  _ts_query_string_value_for_id(address: number, id: number, buffer: number): number;
  _ts_query_predicates_for_pattern(address: number, patternId: number, buffer: number): number;
  _ts_query_delete(address: number): void;
  _ts_query_matches_wasm(
    address: number,
    treeAddress: number,
    startRow: number,
    startColumn: number,
    endRow: number,
    endColumn: number,
    startIndex: number,
    endIndex: number,
    matchLimit: number,
    maxStartDepth: number,
    timeoutMicros: number
  ): void;
  _ts_query_captures_wasm(
    address: number,
    treeAddress: number,
    startRow: number,
    startColumn: number,
    endRow: number,
    endColumn: number,
    startIndex: number,
    endIndex: number,
    matchLimit: number,
    maxStartDepth: number,
    timeoutMicros: number
  ): void;
  _ts_query_disable_capture(address: number, nameAddress: number, nameLength: number): void;
  _ts_query_disable_pattern(address: number, patternIndex: number): void;
  _ts_query_start_byte_for_pattern(address: number, patternIndex: number): number;
  _ts_query_end_byte_for_pattern(address: number, patternIndex: number): number;
  _ts_query_is_pattern_non_local(address: number, patternIndex: number): number;
  _ts_query_is_pattern_rooted(address: number, patternIndex: number): number;
  _ts_query_is_pattern_guaranteed_at_step(address: number, patternIndex: number, stepIndex: number): number;

  // LookaheadIterator
  _ts_lookahead_iterator_new(address: number, stateId: number): number;
  _ts_lookahead_iterator_current_symbol(address: number): number;
  _ts_lookahead_iterator_delete(address: number): void;
  _ts_lookahead_iterator_reset_state(address: number, stateId: number): boolean;
  _ts_lookahead_iterator_reset(address: number, languageAddress: number, stateId: number): boolean;
  _ts_lookahead_iterator_next(address: number): boolean;

  // @ts-ignore
} = Module;
