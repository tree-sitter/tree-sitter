import { type MainModule } from '../lib/tree-sitter';

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

export function isPoint(point?: Point): point is Point {
  return (
    !!point &&
    typeof (point).row === 'number' &&
    typeof (point).column === 'number'
  );
}

export function setModule(module: MainModule) {
  C = module;
}

export let C: MainModule;
