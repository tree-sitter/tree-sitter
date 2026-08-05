import { describe, it } from 'vitest';

describe('FinalizationRegistry is unsupported', () => {
  it('test FinalizationRegistry is unsupported', async () => {
    // @ts-expect-error: test FinalizationRegistry is not supported
    globalThis.FinalizationRegistry = undefined;
    const { JavaScript } = await (await import('./helper')).default;
    const  { Parser, Query } = await import('../src');
    const parser = new Parser();
    parser.setLanguage(JavaScript);
    const tree = parser.parse('1+1')!;
    const copyTree = tree.copy();
    const cursor = tree.walk();
    const copyCursor = cursor.copy();
    const lookaheadIterator = JavaScript.lookaheadIterator(cursor.currentNode.nextParseState)!;
    const query = new Query(JavaScript, '(identifier) @element');
    parser.delete();
    tree.delete();
    copyTree.delete();
    cursor.delete();
    copyCursor.delete();
    lookaheadIterator.delete();
    query.delete();
  });
});
