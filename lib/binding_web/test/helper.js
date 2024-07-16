const Parser = require(`..`);

function languageURL(name) {
  return require.resolve(`../../../target/release/tree-sitter-${name}.wasm`);
}

module.exports = Parser.init().then(async () => ({
  Parser,
  languageURL,
  EmbeddedTemplate: await Parser.Language.load(languageURL('embedded-template')),
  HTML: await Parser.Language.load(languageURL('html')),
  JavaScript: await Parser.Language.load(languageURL('javascript')),
  JSON: await Parser.Language.load(languageURL('json')),
  Python: await Parser.Language.load(languageURL('python')),
}));
