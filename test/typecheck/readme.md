Typecheck
=========

This npm project is for testing dsl.d.ts definition.

To run the test, run command `npm run typecheck`.

Currently only checking if `// @ts-check` included in top of the file. If all files are ready for typechecking, remove these directives and add `"checkJs": true` to `test/fixtures/test_grammars/tsconfig.json`.
