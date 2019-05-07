tree-sitter.wasm
================

[![Build Status](https://travis-ci.org/tree-sitter/tree-sitter.svg?branch=master)](https://travis-ci.org/tree-sitter/tree-sitter)

Wasm bindings to the [Tree-sitter](https://github.com/tree-sitter/tree-sitter) parsing library.

### Basic Usage

You can either load the library as a standalone script:

```html
<script src="/public/js/tree-sitter.js"/>

<script>
  const Parser = window.TreeSitter;
  Parser.init().then(() => { /* the library is ready */ });
</script>
```

or using a packaging system like Webpack:

```js
const Parser = require('tree-sitter');
Parser.init().then(() => { /* the library is ready */ });
```

Create a parser:

```js
const parser = new Parser;
```

Then assign a language to the parser. Tree-sitter languages are packaged as individual `.wasm` files:

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
