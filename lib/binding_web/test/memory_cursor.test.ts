import { describe, expect, it } from 'vitest';

const cleanups = new Map<object, () => void>();

// Run each cleanup on demand, as the GC would once its target became unreachable.
globalThis.FinalizationRegistry = class<T> {
  constructor(private readonly cleanup: (heldValue: T) => void) {}

  register(target: object, heldValue: T) {
    cleanups.set(target, () => {
      this.cleanup(heldValue);
    });
  }

  unregister(token: object) {
    return cleanups.delete(token);
  }
} as unknown as typeof FinalizationRegistry;

function collect(target: object) {
  cleanups.get(target)!();
  cleanups.delete(target);
}

describe('TreeCursor finalizer', () => {
  it('frees the collected cursor, not the last marshalled one', async () => {
    const { JavaScript } = await (await import('./helper')).default;
    const { Parser } = await import('../src');
    const parser = new Parser();
    parser.setLanguage(JavaScript);
    const tree = parser.parse('a * b + c / d')!;

    const cursor = tree.walk();
    cursor.gotoFirstChild();
    cursor.gotoFirstChild();
    cursor.gotoFirstChild();
    const garbage = tree.walk();
    // Leave `cursor` in the transfer buffer when `garbage` is collected.
    expect(cursor.currentDepth).toBe(3);
    collect(garbage);

    // If the finalizer freed `cursor`'s stack, this cursor reuses it.
    const other = tree.walk();
    other.gotoFirstChild();
    other.gotoFirstChild();
    other.gotoLastChild();
    expect(other.nodeText).toBe('c / d');
    expect(cursor.nodeText).toBe('a * b');
  });

  it('frees the collected cursor, not the tree', async () => {
    const { JavaScript } = await (await import('./helper')).default;
    const { Parser } = await import('../src');
    const parser = new Parser();
    parser.setLanguage(JavaScript);
    const tree = parser.parse('a * b')!;

    const garbage = tree.walk();
    const expected = tree.rootNode.toString();
    collect(garbage);
    expect(tree.rootNode.toString()).toBe(expected);
  });
});
