#!/usr/bin/env node

const fs = require('fs');
const path = require('path');

const wasmInputFiles = [
  '../../script/build-wasm',
  ...list('src/wasm-binding'),
  ...list('../include/tree_sitter'),
  ...list('../src')
];
const wasmOutputFiles = ['build-wasm/tree-sitter-c.js', 'build-wasm/tree-sitter.wasm'];
verifyFresh(wasmInputFiles, wasmOutputFiles, 'script/build-wasm');

const jsInputFiles = [...list('build-wasm'), 'src/ts/tree-sitter.ts', 'rollup.config.js', 'tsconfig.json'];
const jsOutputFiles = ['lib/tree-sitter.js', 'lib/tree-sitter.wasm', 'lib/src/ts/tree-sitter.d.ts'];
verifyFresh(jsInputFiles, jsOutputFiles, 'npm run build');

function verifyFresh(inputs, outputs, scriptName) {
  const outputMtime = Math.min(...outputs.map(mtime));

  for (const inputFile of inputs) {
    if (mtime(inputFile) > outputMtime) {
      console.log(`File '${inputFile}' has changed. Re-run '${scriptName}'.`);
      process.exit(1);
    }
  }
}

function list(dir) {
  return fs
    .readdirSync(path.join(__dirname, dir), 'utf8')
    .filter(p => !p.startsWith('.'))
    .map(p => path.join(dir, p));
}

function mtime(p) {
  return fs.statSync(path.join(__dirname, p)).mtime;
}
