const Parser = require(`..`);

function languageURL(name) {
  return require.resolve(`../../../target/release/tree-sitter-${name}.wasm`);
}

module.exports = Parser.init().then(async () => ({
  Parser,
  languageURL,
  JavaScript: await Parser.Language.load(languageURL('javascript')),
}));
