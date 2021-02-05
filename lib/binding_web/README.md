Web Tree-sitter
===============

[![Build Status](https://travis-ci.org/tree-sitter/tree-sitter.svg?branch=master)](https://travis-ci.org/tree-sitter/tree-sitter)

WebAssembly bindings to the [Tree-sitter](https://github.com/tree-sitter/tree-sitter) parsing library.

### Setup

You can download the the `tree-sitter.js` and `tree-sitter.wasm` files from [the latest GitHub release](https://github.com/tree-sitter/tree-sitter/releases/latest) and load them using a standalone script:

```html
<script src="/the/path/to/tree-sitter.js"/>

<script>
  const Parser = window.TreeSitter;
  Parser.init().then(() => { /* the library is ready */ });
</script>
```

You can also install [the `web-tree-sitter` module](https://www.npmjs.com/package/web-tree-sitter) from NPM and load it using a system like Webpack:

```js
const Parser = require('web-tree-sitter');
Parser.init().then(() => { /* the library is ready */ });
```

### Basic Usage

First, create a parser:

```js
const parser = new Parser;
```

Then assign a language to the parser. Tree-sitter languages are packaged as individual `.wasm` files (more on this below):

```js
const JavaScript = await Parser.Language.load('/path/to/tree-sitter-javascript.wasm');
parser.setLanguage(JavaScript);
```

Now you can parse source code:

```js
const sourceCode = 'let x = 1; console.log(x);';
const tree = parser.parse(sourceCode);
```

and inspect the syntax tree.

```javascript
console.log(tree.rootNode.toString());

// (program
//   (lexical_declaration
//     (variable_declarator (identifier) (number)))
//   (expression_statement
//     (call_expression
//       (member_expression (identifier) (property_identifier))
//       (arguments (identifier)))))

const callExpression = tree.rootNode.child(1).firstChild;
console.log(callExpression);

// { type: 'call_expression',
//   startPosition: {row: 0, column: 16},
//   endPosition: {row: 0, column: 30},
//   startIndex: 0,
//   endIndex: 30 }
```

### Editing

If your source code *changes*, you can update the syntax tree. This will take less time than the first parse.

```javascript
// Replace 'let' with 'const'
const newSourceCode = 'const x = 1; console.log(x);';

tree.edit({
  startIndex: 0,
  oldEndIndex: 3,
  newEndIndex: 5,
  startPosition: {row: 0, column: 0},
  oldEndPosition: {row: 0, column: 3},
  newEndPosition: {row: 0, column: 5},
});

const newTree = parser.parse(newSourceCode, tree);
```

### Parsing Text From a Custom Data Structure

If your text is stored in a data structure other than a single string, you can parse it by supplying a callback to `parse` instead of a string:

```javascript
const sourceLines = [
  'let x = 1;',
  'console.log(x);'
];

const tree = parser.parse((index, position) => {
  let line = sourceLines[position.row];
  if (line) return line.slice(position.column);
});
```

### Generate .wasm language files

The following example shows how to generate `.wasm` file for tree-sitter JavaScript grammar.

**IMPORTANT**: [emscripten](https://emscripten.org/docs/getting_started/downloads.html) or [docker](https://www.docker.com/) need to be installed.

First install `tree-sitter-cli` and the tree-sitter language for which to generate `.wasm` (`tree-sitter-javascript` in this example):

```sh
npm install --save-dev tree-sitter-cli tree-sitter-javascript
```

Then just use tree-sitter cli tool to generate the `.wasm`. 

```sh
npx tree-sitter build-wasm node_modules/tree-sitter-javascript
```

If everything is fine, file `tree-sitter-javascript.wasm` should be generated in current directory.

#### Running .wasm in Node.js

Notice that executing `.wasm` files in node.js is considerably slower than running [node.js bindings](https://github.com/tree-sitter/node-tree-sitter). However could be useful for testing purposes:

```javascript
const Parser = require('web-tree-sitter');

(async () => {
  await Parser.init();
  const parser = new Parser();
  const Lang = await Parser.Language.load('tree-sitter-javascript.wasm');
  parser.setLanguage(Lang);
  const tree = parser.parse('let x = 1;');
  console.log(tree.rootNode.toString());
})();
```
