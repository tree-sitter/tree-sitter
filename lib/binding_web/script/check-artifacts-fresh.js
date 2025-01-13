const fs = require('fs');
const path = require('path');

const inputFiles = [
  'lib/binding.c',
  'binding.js',
  'wasm/exports.txt',
  'wasm/imports.js',
  'prefix.js',
  ...list('../include/tree_sitter'),
  ...list('../src'),
];

const outputFiles = ['tree-sitter.js', 'tree-sitter.wasm'];

const outputMtime = Math.min(...outputFiles.map(mtime));

for (const inputFile of inputFiles) {
  if (mtime(inputFile) > outputMtime) {
    console.log(`File '${inputFile}' has changed. Re-run 'script/build-wasm'.`);
    process.exit(1);
  }
}

function list(dir) {
  return fs
    .readdirSync(path.join(__dirname, dir), 'utf8')
    .filter((p) => !p.startsWith('.'))
    .map((p) => path.join(dir, p));
}

function mtime(p) {
  return fs.statSync(path.join(__dirname, p)).mtime;
}
