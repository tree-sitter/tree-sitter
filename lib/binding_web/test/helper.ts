import TSParser from "web-tree-sitter";

// @ts-ignore
const Parser: typeof TSParser = await import('..').then(m => m.default);

// https://github.com/tree-sitter/tree-sitter/blob/master/xtask/src/fetch.rs#L15
type LanguageName = "bash" | "c" | "cpp" | "embedded-template" | "go" | "html" | "java" | "javascript" | "jsdoc" | "json" | "php" | "python" | "ruby" | "rust" | "typescript";

function languageURL(name: LanguageName): string {
  return new URL(`../../../target/release/tree-sitter-${name}.wasm`, import.meta.url).pathname;
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
