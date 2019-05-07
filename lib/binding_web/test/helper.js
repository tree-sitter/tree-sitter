const release = '../../../target/release'
const Parser = require(`${release}/tree-sitter.js`);
const languageURL = name => require.resolve(`${release}/tree-sitter-${name}.wasm`);

module.exports = Parser.init().then(async () => ({
  Parser,
  languageURL,
  JavaScript: await Parser.Language.load(languageURL('javascript')),
}));
