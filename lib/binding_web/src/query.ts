import { Internal, assertInternal, Point, ZERO_POINT, SIZE_OF_INT, C } from './constants';
import { Node } from './node';
import { marshalNode, unmarshalCaptures } from './marshal';
import { TRANSFER_BUFFER } from './parser';

// @ts-ignore
let currentQueryProgressCallback: ((percent: number) => void) | null = null;

interface QueryOptions {
  startPosition?: Point;
  endPosition?: Point;
  startIndex?: number;
  endIndex?: number;
  matchLimit?: number;
  maxStartDepth?: number;
  timeoutMicros?: number;
  progressCallback?: (percent: number) => void;
}

export interface Properties {
  [key: string]: string | null;
}

export interface Predicate {
  operator: string;
  operands: PredicateStep[];
}

export interface Capture {
  name: string;
  node: Node;
  setProperties?: Properties;
  assertedProperties?: Properties;
  refutedProperties?: Properties;
}

export const CaptureQuantifier = {
  Zero: 0,
  ZeroOrOne: 1,
  ZeroOrMore: 2,
  One: 3,
  OneOrMore: 4
} as const;

export type CaptureQuantifier = typeof CaptureQuantifier[keyof typeof CaptureQuantifier];

export interface QueryMatch {
  pattern: number;
  captures: Capture[];
  setProperties?: Properties;
  assertedProperties?: Properties;
  refutedProperties?: Properties;
}

export type PredicateStep =
  | { type: 'string'; value: string }
  | { type: 'capture'; value?: string, name: string };

export type TextPredicate = (captures: Array<Capture>) => boolean;

export class Query {
  private [0]: number; // Internal handle for WASM
  private exceededMatchLimit: boolean;
  private textPredicates: TextPredicate[][];

  readonly captureNames: string[];
  readonly captureQuantifiers: number[][];
  readonly predicates: Predicate[][];
  readonly setProperties: Properties[];
  readonly assertedProperties: Properties[];
  readonly refutedProperties: Properties[];
  matchLimit?: number;

  constructor(
    internal: Internal,
    address: number,
    captureNames: string[],
    captureQuantifiers: number[][],
    textPredicates: TextPredicate[][],
    predicates: Predicate[][],
    setProperties: Properties[],
    assertedProperties: Properties[],
    refutedProperties: Properties[],
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

  delete(): void {
    C._ts_query_delete(this[0]);
    this[0] = 0;
  }

  matches(
    node: Node,
    options: QueryOptions = {}
  ): QueryMatch[] {
    const startPosition = options.startPosition || ZERO_POINT;
    const endPosition = options.endPosition || ZERO_POINT;
    const startIndex = options.startIndex || 0;
    const endIndex = options.endIndex || 0;
    const matchLimit = options.matchLimit || 0xFFFFFFFF;
    const maxStartDepth = options.maxStartDepth || 0xFFFFFFFF;
    const timeoutMicros = options.timeoutMicros || 0;
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
      currentQueryProgressCallback = progressCallback;
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

    const rawCount = getValue(TRANSFER_BUFFER, 'i32');
    const startAddress = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const didExceedMatchLimit = getValue(TRANSFER_BUFFER + 2 * SIZE_OF_INT, 'i32');
    const result = new Array(rawCount);
    this.exceededMatchLimit = Boolean(didExceedMatchLimit);

    let filteredCount = 0;
    let address = startAddress;
    for (let i = 0; i < rawCount; i++) {
      const pattern = getValue(address, 'i32');
      address += SIZE_OF_INT;
      const captureCount = getValue(address, 'i32');
      address += SIZE_OF_INT;

      const captures: Capture[] = new Array(captureCount);
      address = unmarshalCaptures(this, node.tree, address, captures);

      if (this.textPredicates[pattern].every((p) => p(captures))) {
        result[filteredCount] = { pattern, captures };
        const setProperties = this.setProperties[pattern];
        if (setProperties) result[filteredCount].setProperties = setProperties;
        const assertedProperties = this.assertedProperties[pattern];
        if (assertedProperties) result[filteredCount].assertedProperties = assertedProperties;
        const refutedProperties = this.refutedProperties[pattern];
        if (refutedProperties) result[filteredCount].refutedProperties = refutedProperties;
        filteredCount++;
      }
    }
    result.length = filteredCount;

    C._free(startAddress);
    currentQueryProgressCallback = null;
    return result;
  }

  captures(
    node: Node,
    options: QueryOptions = {}
  ): Capture[] {
    const startPosition = options.startPosition || ZERO_POINT;
    const endPosition = options.endPosition || ZERO_POINT;
    const startIndex = options.startIndex || 0;
    const endIndex = options.endIndex || 0;
    const matchLimit = options.matchLimit || 0xFFFFFFFF;
    const maxStartDepth = options.maxStartDepth || 0xFFFFFFFF;
    const timeoutMicros = options.timeoutMicros || 0;
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
      currentQueryProgressCallback = progressCallback;
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

    const count = getValue(TRANSFER_BUFFER, 'i32');
    const startAddress = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const didExceedMatchLimit = getValue(TRANSFER_BUFFER + 2 * SIZE_OF_INT, 'i32');
    const result: Capture[] = [];
    this.exceededMatchLimit = Boolean(didExceedMatchLimit);

    const captures: Capture[] = [];
    let address = startAddress;
    for (let i = 0; i < count; i++) {
      const pattern = getValue(address, 'i32');
      address += SIZE_OF_INT;
      const captureCount = getValue(address, 'i32');
      address += SIZE_OF_INT;
      const captureIndex = getValue(address, 'i32');
      address += SIZE_OF_INT;

      captures.length = captureCount;
      address = unmarshalCaptures(this, node.tree, address, captures);

      if (this.textPredicates[pattern].every((p) => p(captures))) {
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
    currentQueryProgressCallback = null;
    return result;
  }

  predicatesForPattern(patternIndex: number): Predicate[] {
    return this.predicates[patternIndex];
  }

  disableCapture(captureName: string): void {
    const captureNameLength = lengthBytesUTF8(captureName);
    const captureNameAddress = C._malloc(captureNameLength + 1);
    stringToUTF8(captureName, captureNameAddress, captureNameLength + 1);
    C._ts_query_disable_capture(this[0], captureNameAddress, captureNameLength);
    C._free(captureNameAddress);
  }

  disablePattern(patternIndex: number): void {
    if (patternIndex >= this.predicates.length) {
      throw new Error(
        `Pattern index is ${patternIndex} but the pattern count is ${this.predicates.length}`
      );
    }
    C._ts_query_disable_pattern(this[0], patternIndex);
  }

  didExceedMatchLimit(): boolean {
    return this.exceededMatchLimit;
  }

  startIndexForPattern(patternIndex: number): number {
    if (patternIndex >= this.predicates.length) {
      throw new Error(
        `Pattern index is ${patternIndex} but the pattern count is ${this.predicates.length}`
      );
    }
    return C._ts_query_start_byte_for_pattern(this[0], patternIndex);
  }

  endIndexForPattern(patternIndex: number): number {
    if (patternIndex >= this.predicates.length) {
      throw new Error(
        `Pattern index is ${patternIndex} but the pattern count is ${this.predicates.length}`
      );
    }
    return C._ts_query_end_byte_for_pattern(this[0], patternIndex);
  }

  isPatternNonLocal(patternIndex: number): boolean {
    return C._ts_query_is_pattern_non_local(this[0], patternIndex) === 1;
  }

  isPatternRooted(patternIndex: number): boolean {
    return C._ts_query_is_pattern_rooted(this[0], patternIndex) === 1;
  }

  isPatternGuaranteedAtStep(patternIndex: number, stepIndex: number): boolean {
    return C._ts_query_is_pattern_guaranteed_at_step(
      this[0],
      patternIndex,
      stepIndex
    ) === 1;
  }
}
