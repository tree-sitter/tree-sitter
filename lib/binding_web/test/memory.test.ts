import { describe, expect, it } from 'vitest';
import { gc, event, Finalizer } from './memory';

// hijack finalization registry before import web-tree-sitter
globalThis.FinalizationRegistry = Finalizer;

describe('Memory Management', () => {
  describe('call .delete()', () => {
    it('test free memory manually', async () => {
      const timer = setInterval(() => {
        gc();
      }, 100);
      let done = 0; 
      event.on('gc', () => {
        done++;
      });
      await (async () => {
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
      })();
      // wait for gc
      await new Promise((resolve) => setTimeout(resolve, 1000));
      clearInterval(timer);
      // expect no gc event fired
      expect(done).toBe(0);
    });
  });

  describe('do not call .delete()', () => {
    it('test free memory automatically', async () => {
      const timer = setInterval(() => {
        gc();
      }, 100);
      let done = 0;
      const promise = new Promise((resolve) => {
        event.on('gc', () => {
          if (++done === 7) {
            resolve(undefined);
            clearInterval(timer);
          }
          console.log('free memory times: ', done);
        });
      });
      await (async () => {
        const { JavaScript } = await (await import('./helper')).default;
        const  { Parser, Query } = await import('../src');
        const parser = new Parser(); // 1
        parser.setLanguage(JavaScript);
        const tree = parser.parse('1+1')!; // 2
        tree.copy(); // 3
        const cursor = tree.walk(); // 4
        cursor.copy(); // 5
        JavaScript.lookaheadIterator(cursor.currentNode.nextParseState)!; // 6
        new Query(JavaScript, '(identifier) @element'); // 7
      })();
      await promise;
    });
  });
});
