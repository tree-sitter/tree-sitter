const Parser = require('../../../target/release/tree-sitter.js');
const Python = require.resolve('../../../target/scratch/tree-sitter-python.wasm');
const JavaScript = require.resolve('../../../target/scratch/tree-sitter-javascript.wasm');

module.exports = Parser.init().then(async () => ({
  Parser,
  JavaScript: await Parser.Language.load(JavaScript),
  Python: await Parser.Language.load(Python)
}));
