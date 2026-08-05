import { describe, it, expect } from 'vitest';
import { Edit } from '../src';

describe('Edit', () => {
  it('edits a point after the edit', () => {
    const edit = new Edit({
      startIndex: 5,
      oldEndIndex: 5,
      newEndIndex: 10,
      startPosition: { row: 0, column: 5 },
      oldEndPosition: { row: 0, column: 5 },
      newEndPosition: { row: 0, column: 10 },
    });

    const point = { row: 0, column: 8 };
    const index = 8;
    const result = edit.editPoint(point, index);
    expect(result.point).toEqual({ row: 0, column: 13 });
    expect(result.index).toBe(13);
  });

  it('edits a point before the edit', () => {
    const edit = new Edit({
      startIndex: 5,
      oldEndIndex: 5,
      newEndIndex: 10,
      startPosition: { row: 0, column: 5 },
      oldEndPosition: { row: 0, column: 5 },
      newEndPosition: { row: 0, column: 10 },
    });

    const point = { row: 0, column: 2 };
    const index = 2;
    const result = edit.editPoint(point, index);
    expect(result.point).toEqual({ row: 0, column: 2 });
    expect(result.index).toBe(2);
  });

  it('edits a point at the start of the edit', () => {
    const edit = new Edit({
      startIndex: 5,
      oldEndIndex: 5,
      newEndIndex: 10,
      startPosition: { row: 0, column: 5 },
      oldEndPosition: { row: 0, column: 5 },
      newEndPosition: { row: 0, column: 10 },
    });

    const point = { row: 0, column: 5 };
    const index = 5;
    const result = edit.editPoint(point, index);
    expect(result.point).toEqual({ row: 0, column: 10 });
    expect(result.index).toBe(10);
  });

  it('edits a range after the edit', () => {
    const edit = new Edit({
      startIndex: 10,
      oldEndIndex: 15,
      newEndIndex: 20,
      startPosition: { row: 1, column: 0 },
      oldEndPosition: { row: 1, column: 5 },
      newEndPosition: { row: 2, column: 0 },
    });

    const range = {
      startPosition: { row: 2, column: 0 },
      endPosition: { row: 2, column: 5 },
      startIndex: 20,
      endIndex: 25,
    };
    const result = edit.editRange(range);
    expect(result.startIndex).toBe(25);
    expect(result.endIndex).toBe(30);
    expect(result.startPosition).toEqual({ row: 3, column: 0 });
    expect(result.endPosition).toEqual({ row: 3, column: 5 });
  });

  it('edits a range before the edit', () => {
    const edit = new Edit({
      startIndex: 10,
      oldEndIndex: 15,
      newEndIndex: 20,
      startPosition: { row: 1, column: 0 },
      oldEndPosition: { row: 1, column: 5 },
      newEndPosition: { row: 2, column: 0 },
    });

    const range = {
      startPosition: { row: 0, column: 5 },
      endPosition: { row: 0, column: 8 },
      startIndex: 5,
      endIndex: 8,
    };
    const result = edit.editRange(range);
    expect(result.startIndex).toBe(5);
    expect(result.endIndex).toBe(8);
    expect(result.startPosition).toEqual({ row: 0, column: 5 });
    expect(result.endPosition).toEqual({ row: 0, column: 8 });
  });

  it('edits a range overlapping the edit', () => {
    const edit = new Edit({
      startIndex: 10,
      oldEndIndex: 15,
      newEndIndex: 20,
      startPosition: { row: 1, column: 0 },
      oldEndPosition: { row: 1, column: 5 },
      newEndPosition: { row: 2, column: 0 }
    });

    const range = {
      startPosition: { row: 0, column: 8 },
      endPosition: { row: 1, column: 2 },
      startIndex: 8,
      endIndex: 12,
    };
    const result = edit.editRange(range);
    expect(result.startIndex).toBe(8);
    expect(result.endIndex).toBe(10);
    expect(result.startPosition).toEqual({ row: 0, column: 8 });
    expect(result.endPosition).toEqual({ row: 1, column: 0 });
  });
});
