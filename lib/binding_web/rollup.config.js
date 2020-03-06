import copy from 'rollup-plugin-copy';
import typescript from 'rollup-plugin-typescript2';
import { terser } from 'rollup-plugin-terser';

export default {
  input: 'src/ts/tree-sitter.ts',
  output: {
    file: 'lib/tree-sitter.js',
    format: 'umd',
    name: 'TreeSitter'
  },
  plugins: [
    typescript(),
    terser(),
    copy({
      targets: [{ src: 'build-wasm/tree-sitter.wasm', dest: 'lib' }]
    })
  ]
};
