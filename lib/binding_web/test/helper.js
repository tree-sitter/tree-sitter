const TreeSitter = require(`..`);

function languageURL(name) {
  return require.resolve(`../../../target/release/tree-sitter-${name}.wasm`);
}

module.exports = TreeSitter().then(async (module) => ({
  Parser: module.Parser,
  languageURL,
  JavaScript: await module.Parser.Language.load(languageURL('javascript')),
}));
