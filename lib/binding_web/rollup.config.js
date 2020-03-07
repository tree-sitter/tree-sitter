import copy from 'rollup-plugin-copy';
import { terser } from 'rollup-plugin-terser'

const isProduction = process.env.BUILD === 'production';

export default {
  input: 'src/js/binding.js',
  output: {
    file: 'lib/tree-sitter.js',
    format: 'umd',
    name: 'TreeSitter'
  },
  plugins: [
    isProduction && terser({
      keep_classnames: true
    }),
    copy({
      targets: [
          { src: 'build-wasm/tree-sitter.wasm', dest: 'lib' },
          { src: 'src/ts/tree-sitter-web.d.ts', dest: 'lib' }
        ]
    })
  ]
};
