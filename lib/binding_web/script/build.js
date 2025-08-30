import esbuild from 'esbuild';
import fs from 'fs/promises';

const format = process.env.CJS ? 'cjs' : 'esm';
const debug = process.argv.includes('--debug');
const outfile = `${debug ? 'debug/' : ''}web-tree-sitter.${format === 'esm' ? 'js' : 'cjs'}`;

async function processWasmSourceMap(inputPath, outputPath) {
  const mapContent = await fs.readFile(inputPath, 'utf8');
  const sourceMap = JSON.parse(mapContent);

  const isTreeSitterSource = (source) => 
    source.includes('../../src/') || source === 'tree-sitter.c';

  const normalizePath = (source) => {
    if (source.includes('../../src/')) {
      return source.replace('../../src/', debug ? '../lib/' : 'lib/');
    } else if (source === 'tree-sitter.c') {
      return debug ? '../lib/tree-sitter.c' : 'lib/tree-sitter.c';
    }
    return source;
  };

  const filtered = sourceMap.sources
    .map((source, index) => ({ source, content: sourceMap.sourcesContent?.[index] }))
    .filter(item => isTreeSitterSource(item.source))
    .map(item => ({ source: normalizePath(item.source), content: item.content }));

  sourceMap.sources = filtered.map(item => item.source);
  sourceMap.sourcesContent = filtered.map(item => item.content);

  await fs.writeFile(outputPath, JSON.stringify(sourceMap, null, 2));
}

async function build() {
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

  // Copy the Wasm files to the appropriate spot, as esbuild doesn't "bundle" Wasm files
  const outputWasmName = `${debug ? 'debug/' : ''}web-tree-sitter.wasm`;
  await fs.copyFile('lib/web-tree-sitter.wasm', outputWasmName);

  await processWasmSourceMap('lib/web-tree-sitter.wasm.map', `${outputWasmName}.map`);
}

build().catch(console.error);
