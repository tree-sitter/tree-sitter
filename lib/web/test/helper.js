const release = '../../../target/release'
const Parser = require(`${release}/tree-sitter.js`);
const JavaScript = require.resolve(`${release}/tree-sitter-javascript.wasm`);
const Python = require.resolve(`${release}/tree-sitter-python.wasm`);

module.exports = Parser.init().then(async () => ({
  Parser,
  JavaScript: await Parser.Language.load(JavaScript),
  Python: await Parser.Language.load(Python)
}));
