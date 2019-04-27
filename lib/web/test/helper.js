const release = '../../../target/release'
const Parser = require(`${release}/tree-sitter.js`);
const JavaScript = require.resolve(`${release}/tree-sitter-javascript.wasm`);

module.exports = Parser.init().then(async () => ({
  Parser,
  JavaScript: await Parser.Language.load(JavaScript),
}));
