import esbuild from 'esbuild';
import fs from 'fs/promises';

const format = process.env.CJS ? 'cjs' : 'esm';
const debug = process.argv.includes('--debug');
const outfile = `${debug ? 'debug/' : ''}tree-sitter.${format === 'esm' ? 'js' : 'cjs'}`;

await esbuild.build({
  entryPoints: ['src/index.ts'],
  bundle: true,
  platform: 'node',
  format,
  outfile,
  sourcemap: true,
  sourcesContent: true,
  keepNames: true,
  external: ['fs/*', 'fs/promises'],
  resolveExtensions: ['.ts', '.js', format === 'esm' ? '.mjs' : '.cjs'],
});

// Copy the generated WASM files to the appropriate spot, as esbuild doesn't "bundle" WASM files
const outputWasmName = `${debug ? 'debug/' : ''}tree-sitter.wasm`;
await fs.copyFile(`lib/tree-sitter.wasm`, outputWasmName);
await fs.copyFile(`lib/tree-sitter.wasm.map`, `${outputWasmName}.map`);
