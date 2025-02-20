import { createBundle } from 'dts-buddy';

for (let ext of ['ts', 'cts']) {
  await createBundle({
    project: 'tsconfig.json',
    output: `web-tree-sitter.d.${ext}`,
    modules: {
      'web-tree-sitter': 'src/index.ts'
    },
    compilerOptions: {
      stripInternal: true,
    },
  });
}
