import { Internal, assertInternal, Point, ZERO_POINT, SIZE_OF_INT, C } from './constants';
import { Node } from './node';
import { marshalNode, unmarshalCaptures } from './marshal';
import { TRANSFER_BUFFER } from './parser';

/**
 * Options for query execution
 */
export interface QueryOptions {
  /** The start position of the range to query */
  startPosition?: Point;

  /** The end position of the range to query */
  endPosition?: Point;

  /** The start index of the range to query */
  startIndex?: number;

  /** The end index of the range to query */
  endIndex?: number;

  /**
   * The maximum number of in-progress matches for this query.
   * The limit must be > 0 and <= 65536.
   */
  matchLimit?: number;

  /**
   * The maximum start depth for a query cursor.
   *
   * This prevents cursors from exploring children nodes at a certain depth.
   * Note if a pattern includes many children, then they will still be
   * checked.
   *
   * The zero max start depth value can be used as a special behavior and
   * it helps to destructure a subtree by staying on a node and using
   * captures for interested parts. Note that the zero max start depth
   * only limit a search depth for a pattern's root node but other nodes
   * that are parts of the pattern may be searched at any depth what
   * defined by the pattern structure.
   *
   * Set to `null` to remove the maximum start depth.
   */
  maxStartDepth?: number;

  /**
   * The maximum duration in microseconds that query execution should be allowed to
   * take before halting.
   *
   * If query execution takes longer than this, it will halt early, returning an empty array.
   */
  timeoutMicros?: number;

  /**
   * A function that will be called periodically during the execution of the query to check
   * if query execution should be cancelled. You can also use this to instrument query execution
   * and check where the query is at in the document. The progress callback takes a single argument,
   * which is a {@link QueryState} representing the current state of the query.
   */
  progressCallback?: (state: QueryState) => void;
}

/**
 * A stateful object that is passed into the progress callback {@link QueryOptions#progressCallback}
 * to provide the current state of the query.
 */
export interface QueryState {
  /** The byte offset in the document that the query is at. */
  currentOffset: number;
}

/** A record of key-value pairs associated with a particular pattern in a {@link Query}. */
export type QueryProperties = Record<string, string | null>;

/**
 * A predicate that contains an operator and list of operands.
 */
export interface QueryPredicate {
  /** The operator of the predicate, like `match?`, `eq?`, `set!`, etc. */
  operator: string;

  /** The operands of the predicate, which are either captures or strings. */
  operands: PredicateStep[];
}

/**
 * A particular {@link Node} that has been captured with a particular name within a
 * {@link Query}.
 */
export interface QueryCapture {
  /** The index of the pattern that matched. */
  patternIndex: number;

  /** The name of the capture */
  name: string;

  /** The captured node */
  node: Node;

  /** The properties for predicates declared with the operator `set!`. */
  setProperties?: QueryProperties;

  /** The properties for predicates declared with the operator `is?`. */
  assertedProperties?: QueryProperties;

  /** The properties for predicates declared with the operator `is-not?`. */
  refutedProperties?: QueryProperties;
}

/** A match of a {@link Query} to a particular set of {@link Node}s. */
export interface QueryMatch {
  /** @deprecated Use `patternIndex` instead, this will be removed in 0.26. */
  pattern: number;

  /** The index of the pattern that matched. */
  patternIndex: number;

  /** The captures associated with the match. */
  captures: QueryCapture[];

  /** The properties for predicates declared with the operator `set!`. */
  setProperties?: QueryProperties;

  /** The properties for predicates declared with the operator `is?`. */
  assertedProperties?: QueryProperties;

  /** The properties for predicates declared with the operator `is-not?`. */
  refutedProperties?: QueryProperties;
}

/** A quantifier for captures */
export const CaptureQuantifier = {
  Zero: 0,
  ZeroOrOne: 1,
  ZeroOrMore: 2,
  One: 3,
  OneOrMore: 4
} as const;

/** A quantifier for captures */
export type CaptureQuantifier = typeof CaptureQuantifier[keyof typeof CaptureQuantifier];

/**
 * Predicates are represented as a single array of steps. There are two
 * types of steps, which correspond to the two legal values for
 * the `type` field:
 *
 * - `capture` - Steps with this type represent names
 *    of captures. The `name` field is the name of the capture.
 *
 * - `string` - Steps with this type represent literal
 *    strings. The `value` field is the string value.
 */
export type PredicateStep =
  | { type: 'capture', name: string }
  | { type: 'string', value: string };

/**
 * @internal
 *
 * A function that checks if a given set of captures matches a particular
 * condition. This is used in the built-in `eq?`, `match?`, and `any-of?`
 * predicates.
 */
export type TextPredicate = (captures: QueryCapture[]) => boolean;

export class Query {
  /** @internal */
  private [0] = 0; // Internal handle for WASM

  /** @internal */
  private exceededMatchLimit: boolean;

  /** @internal */
  private textPredicates: TextPredicate[][];

  /** The names of the captures used in the query. */
  readonly captureNames: string[];

  /** The quantifiers of the captures used in the query. */
  readonly captureQuantifiers: CaptureQuantifier[][];

  /**
   * The other user-defined predicates associated with the given index.
   *
   * This includes predicates with operators other than:
   * - `match?`
   * - `eq?` and `not-eq?`
   * - `any-of?` and `not-any-of?`
   * - `is?` and `is-not?`
   * - `set!`
   */
  readonly predicates: QueryPredicate[][];

  /** The properties for predicates with the operator `set!`. */
  readonly setProperties: QueryProperties[];

  /** The properties for predicates with the operator `is?`. */
  readonly assertedProperties: QueryProperties[];

  /** The properties for predicates with the operator `is-not?`. */
  readonly refutedProperties: QueryProperties[];

  /** The maximum number of in-progress matches for this cursor. */
  matchLimit?: number;

  /** @internal */
  constructor(
    internal: Internal,
    address: number,
    captureNames: string[],
    captureQuantifiers: CaptureQuantifier[][],
    textPredicates: TextPredicate[][],
    predicates: QueryPredicate[][],
    setProperties: QueryProperties[],
    assertedProperties: QueryProperties[],
    refutedProperties: QueryProperties[],
  ) {
    assertInternal(internal);
    this[0] = address;
    this.captureNames = captureNames;
    this.captureQuantifiers = captureQuantifiers;
    this.textPredicates = textPredicates;
    this.predicates = predicates;
    this.setProperties = setProperties;
    this.assertedProperties = assertedProperties;
    this.refutedProperties = refutedProperties;
    this.exceededMatchLimit = false;
  }

  /** Delete the query, freeing its resources. */
  delete(): void {
    C._ts_query_delete(this[0]);
    this[0] = 0;
  }

  /**
   * Iterate over all of the matches in the order that they were found.
   *
   * Each match contains the index of the pattern that matched, and a list of
   * captures. Because multiple patterns can match the same set of nodes,
   * one match may contain captures that appear *before* some of the
   * captures from a previous match.
   *
   * @param {Node} node - The node to execute the query on.
   *
   * @param {QueryOptions} options - Options for query execution.
   */
  matches(
    node: Node,
    options: QueryOptions = {}
  ): QueryMatch[] {
    const startPosition = options.startPosition ?? ZERO_POINT;
    const endPosition = options.endPosition ?? ZERO_POINT;
    const startIndex = options.startIndex ?? 0;
    const endIndex = options.endIndex ?? 0;
    const matchLimit = options.matchLimit ?? 0xFFFFFFFF;
    const maxStartDepth = options.maxStartDepth ?? 0xFFFFFFFF;
    const timeoutMicros = options.timeoutMicros ?? 0;
    const progressCallback = options.progressCallback;

    if (typeof matchLimit !== 'number') {
      throw new Error('Arguments must be numbers');
    }
    this.matchLimit = matchLimit;

    if (endIndex !== 0 && startIndex > endIndex) {
      throw new Error('`startIndex` cannot be greater than `endIndex`');
    }

    if (endPosition !== ZERO_POINT && (
      startPosition.row > endPosition.row ||
      (startPosition.row === endPosition.row && startPosition.column > endPosition.column)
    )) {
      throw new Error('`startPosition` cannot be greater than `endPosition`');
    }

    if (progressCallback) {
      C.currentQueryProgressCallback = progressCallback;
    }

    marshalNode(node);

    C._ts_query_matches_wasm(
      this[0],
      node.tree[0],
      startPosition.row,
      startPosition.column,
      endPosition.row,
      endPosition.column,
      startIndex,
      endIndex,
      matchLimit,
      maxStartDepth,
      timeoutMicros,
    );

    const rawCount = C.getValue(TRANSFER_BUFFER, 'i32');
    const startAddress = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const didExceedMatchLimit = C.getValue(TRANSFER_BUFFER + 2 * SIZE_OF_INT, 'i32');
    const result = new Array<QueryMatch>(rawCount);
    this.exceededMatchLimit = Boolean(didExceedMatchLimit);

    let filteredCount = 0;
    let address = startAddress;
    for (let i = 0; i < rawCount; i++) {
      const patternIndex = C.getValue(address, 'i32');
      address += SIZE_OF_INT;
      const captureCount = C.getValue(address, 'i32');
      address += SIZE_OF_INT;

      const captures = new Array<QueryCapture>(captureCount);
      address = unmarshalCaptures(this, node.tree, address, patternIndex, captures);

      if (this.textPredicates[patternIndex].every((p) => p(captures))) {
        result[filteredCount] = { pattern: patternIndex, patternIndex, captures };
        const setProperties = this.setProperties[patternIndex];
        result[filteredCount].setProperties = setProperties;
        const assertedProperties = this.assertedProperties[patternIndex];
        result[filteredCount].assertedProperties = assertedProperties;
        const refutedProperties = this.refutedProperties[patternIndex];
        result[filteredCount].refutedProperties = refutedProperties;
        filteredCount++;
      }
    }
    result.length = filteredCount;

    C._free(startAddress);
    C.currentQueryProgressCallback = null;
    return result;
  }

  /**
   * Iterate over all of the individual captures in the order that they
   * appear.
   *
   * This is useful if you don't care about which pattern matched, and just
   * want a single, ordered sequence of captures.
   *
   * @param {Node} node - The node to execute the query on.
   *
   * @param {QueryOptions} options - Options for query execution.
   */
  captures(
    node: Node,
    options: QueryOptions = {}
  ): QueryCapture[] {
    const startPosition = options.startPosition ?? ZERO_POINT;
    const endPosition = options.endPosition ?? ZERO_POINT;
    const startIndex = options.startIndex ?? 0;
    const endIndex = options.endIndex ?? 0;
    const matchLimit = options.matchLimit ?? 0xFFFFFFFF;
    const maxStartDepth = options.maxStartDepth ?? 0xFFFFFFFF;
    const timeoutMicros = options.timeoutMicros ?? 0;
    const progressCallback = options.progressCallback;

    if (typeof matchLimit !== 'number') {
      throw new Error('Arguments must be numbers');
    }
    this.matchLimit = matchLimit;

    if (endIndex !== 0 && startIndex > endIndex) {
      throw new Error('`startIndex` cannot be greater than `endIndex`');
    }

    if (endPosition !== ZERO_POINT && (
      startPosition.row > endPosition.row ||
      (startPosition.row === endPosition.row && startPosition.column > endPosition.column)
    )) {
      throw new Error('`startPosition` cannot be greater than `endPosition`');
    }

    if (progressCallback) {
      C.currentQueryProgressCallback = progressCallback;
    }

    marshalNode(node);

    C._ts_query_captures_wasm(
      this[0],
      node.tree[0],
      startPosition.row,
      startPosition.column,
      endPosition.row,
      endPosition.column,
      startIndex,
      endIndex,
      matchLimit,
      maxStartDepth,
      timeoutMicros,
    );

    const count = C.getValue(TRANSFER_BUFFER, 'i32');
    const startAddress = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const didExceedMatchLimit = C.getValue(TRANSFER_BUFFER + 2 * SIZE_OF_INT, 'i32');
    const result = new Array<QueryCapture>();
    this.exceededMatchLimit = Boolean(didExceedMatchLimit);

    const captures = new Array<QueryCapture>();
    let address = startAddress;
    for (let i = 0; i < count; i++) {
      const patternIndex = C.getValue(address, 'i32');
      address += SIZE_OF_INT;
      const captureCount = C.getValue(address, 'i32');
      address += SIZE_OF_INT;
      const captureIndex = C.getValue(address, 'i32');
      address += SIZE_OF_INT;

      captures.length = captureCount;
      address = unmarshalCaptures(this, node.tree, address, patternIndex, captures);

      if (this.textPredicates[patternIndex].every(p => p(captures))) {
        const capture = captures[captureIndex];
        const setProperties = this.setProperties[patternIndex];
        capture.setProperties = setProperties;
        const assertedProperties = this.assertedProperties[patternIndex];
        capture.assertedProperties = assertedProperties;
        const refutedProperties = this.refutedProperties[patternIndex];
        capture.refutedProperties = refutedProperties;
        result.push(capture);
      }
    }

    C._free(startAddress);
    C.currentQueryProgressCallback = null;
    return result;
  }

  /** Get the predicates for a given pattern. */
  predicatesForPattern(patternIndex: number): QueryPredicate[] {
    return this.predicates[patternIndex];
  }

  /**
   * Disable a certain capture within a query.
   *
   * This prevents the capture from being returned in matches, and also
   * avoids any resource usage associated with recording the capture.
   */
  disableCapture(captureName: string): void {
    const captureNameLength = C.lengthBytesUTF8(captureName);
    const captureNameAddress = C._malloc(captureNameLength + 1);
    C.stringToUTF8(captureName, captureNameAddress, captureNameLength + 1);
    C._ts_query_disable_capture(this[0], captureNameAddress, captureNameLength);
    C._free(captureNameAddress);
  }

  /**
   * Disable a certain pattern within a query.
   *
   * This prevents the pattern from matching, and also avoids any resource
   * usage associated with the pattern. This throws an error if the pattern
   * index is out of bounds.
   */
  disablePattern(patternIndex: number): void {
    if (patternIndex >= this.predicates.length) {
      throw new Error(
        `Pattern index is ${patternIndex} but the pattern count is ${this.predicates.length}`
      );
    }
    C._ts_query_disable_pattern(this[0], patternIndex);
  }

  /**
   * Check if, on its last execution, this cursor exceeded its maximum number
   * of in-progress matches.
   */
  didExceedMatchLimit(): boolean {
    return this.exceededMatchLimit;
  }

  /** Get the byte offset where the given pattern starts in the query's source. */
  startIndexForPattern(patternIndex: number): number {
    if (patternIndex >= this.predicates.length) {
      throw new Error(
        `Pattern index is ${patternIndex} but the pattern count is ${this.predicates.length}`
      );
    }
    return C._ts_query_start_byte_for_pattern(this[0], patternIndex);
  }

  /** Get the byte offset where the given pattern ends in the query's source. */
  endIndexForPattern(patternIndex: number): number {
    if (patternIndex >= this.predicates.length) {
      throw new Error(
        `Pattern index is ${patternIndex} but the pattern count is ${this.predicates.length}`
      );
    }
    return C._ts_query_end_byte_for_pattern(this[0], patternIndex);
  }

  /** Get the number of patterns in the query. */
  patternCount(): number {
    return C._ts_query_pattern_count(this[0]);
  }

  /** Get the index for a given capture name. */
  captureIndexForName(captureName: string): number {
    return this.captureNames.indexOf(captureName);
  }

  /** Check if a given pattern within a query has a single root node. */
  isPatternRooted(patternIndex: number): boolean {
    return C._ts_query_is_pattern_rooted(this[0], patternIndex) === 1;
  }

  /** Check if a given pattern within a query has a single root node. */
  isPatternNonLocal(patternIndex: number): boolean {
    return C._ts_query_is_pattern_non_local(this[0], patternIndex) === 1;
  }

  /**
   * Check if a given step in a query is 'definite'.
   *
   * A query step is 'definite' if its parent pattern will be guaranteed to
   * match successfully once it reaches the step.
   */
  isPatternGuaranteedAtStep(byteIndex: number): boolean {
    return C._ts_query_is_pattern_guaranteed_at_step(this[0], byteIndex) === 1;
  }
}
