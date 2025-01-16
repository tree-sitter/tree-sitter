import type { default as ParserType } from 'web-tree-sitter';
import path from 'path';

// @ts-expect-error We're intentionally importing ../tree-sitter.js
// eslint-disable-next-line @typescript-eslint/no-unsafe-assignment, @typescript-eslint/no-unsafe-return, @typescript-eslint/no-unsafe-member-access
const Parser: typeof ParserType = await import('..').then(m => m.default);

// https://github.com/tree-sitter/tree-sitter/blob/master/xtask/src/fetch.rs#L15
export type LanguageName = 'bash' | 'c' | 'cpp' | 'embedded-template' | 'go' | 'html' | 'java' | 'javascript' | 'jsdoc' | 'json' | 'php' | 'python' | 'ruby' | 'rust' | 'typescript' | 'tsx';

function languageURL(name: LanguageName): string {
  const basePath = process.cwd();
  return path.join(basePath, `../../target/release/tree-sitter-${name}.wasm`);
}

export default Parser.init().then(async () => ({
  Parser,
  languageURL,
  C: await Parser.Language.load(languageURL('c')),
  EmbeddedTemplate: await Parser.Language.load(languageURL('embedded-template')),
  HTML: await Parser.Language.load(languageURL('html')),
  JavaScript: await Parser.Language.load(languageURL('javascript')),
  JSON: await Parser.Language.load(languageURL('json')),
  Python: await Parser.Language.load(languageURL('python')),
  Rust: await Parser.Language.load(languageURL('rust')),
}));
