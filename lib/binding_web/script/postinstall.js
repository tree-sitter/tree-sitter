import fs from 'fs';
import path from 'path';

const isDebug = process.env.npm_config_web_tree_sitter_debug === 'true';

if (isDebug) {
  // Copy debug versions to root
  fs.copyFileSync(
    path.join(__dirname, '../debug/tree-sitter.js'),
    path.join(__dirname, '../tree-sitter.js')
  );
  fs.copyFileSync(
    path.join(__dirname, '../debug/tree-sitter.wasm'),
    path.join(__dirname, '../tree-sitter.wasm')
  );
  // Copy sourcemaps too
  fs.copyFileSync(
    path.join(__dirname, '../debug/tree-sitter.js.map'),
    path.join(__dirname, '../tree-sitter.js.map')
  );
  fs.copyFileSync(
    path.join(__dirname, '../debug/tree-sitter.wasm.map'),
    path.join(__dirname, '../tree-sitter.wasm.map')
  );
}
