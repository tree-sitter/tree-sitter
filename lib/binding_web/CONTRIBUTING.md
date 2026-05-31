# Contributing

## Code of Conduct

Contributors to Tree-sitter should abide by the [Contributor Covenant][covenant].

## Developing Web-tree-sitter

### Prerequisites

To make changes to Web-tree-sitter, you should have:

1. Install [Rust](https://www.rust-lang.org/tools/install)
2. Install [Node.js](https://nodejs.org/en/download)
3. Install [Docker](https://www.docker.com/products/docker-desktop) or [podman](https://podman.io)

### Building

1. Clone and open the repository:

```sh
git clone https://github.com/tree-sitter/tree-sitter
cd ./tree-sitter
```

2. Fetch and build the grammars that are used for testing:

```sh
cargo xtask fetch-fixtures
```

3. Update the generated parser.c files:

```sh
cargo xtask generate-fixtures
```

4. Build the Wasm modules:

```sh
cargo xtask generate-fixtures --wasm
```

5. Navigate to the web binding directory

```
cd tree-sitter/lib/binding_web
```

6. Install the dependencies:

```sh
npm install
```

7. Build the library:

```sh
npm run build
```

> [!NOTE]
> By default, the build process will emit an ES6 module. If you need a CommonJS module, export `CJS` to `true`, or just
> run `CJS=true npm run build` (or the equivalent command for Windows).

> [!TIP]
> To build the library with debug information, you can run `npm run build:debug`. The `CJS` environment variable is still
> taken into account.

8. Run the tests

```sh
npm test
```

> [!NOTE]
> We use `vitest` to run the tests. If you want to run a specific test, you can use the `-t` flag to pass in a pattern.
> If you want to run a specific file, you can just pass the name of the file as is. For example, to run the `parser` tests
> in `test/parser.test.ts`, you can run `npm test parser`. To run tests that have the name `descendant` somewhere, run
> `npm test -- -t descendant`.
>
> For coverage information, you can run `npm test -- --coverage`.


### Putting it together

#### The C side

There are several components that come together to build the final JS and Wasm files. First, we use `emscripten` in our
xtask located at `xtask/src/build_wasm.rs` from the root directory to compile the Wasm files. Note that it's also possible to use a local version of Emscripten, the build script will check if you [have it installed](https://emscripten.org/docs/getting_started/index.html) before falling back to Dockeror Podman. This Wasm module is output into the
local `lib` folder, and is used only in [`src/bindings.ts`][bindings.ts] to handle loading the Wasm module. The C code that
is compiled into the Wasm module is located in at [`lib/tree-sitter.c`][tree-sitter.c], and contains all the necessary
glue code to interact with the JS environment. If you need to update the imported functions from the tree-sitter library,
or anywhere else, you must update [`lib/exports.txt`][exports.txt]. Lastly, the type information for the Wasm module is
located at [`lib/tree-sitter.d.ts`][tree-sitter.d.ts], and can be updated by running `cargo xtask build-wasm --emit-tsd`
from the root directory.

#### The TypeScript side

The TypeScript library is a higher level abstraction over the Wasm module, and is located in `src`. This is where the
public API is defined, and where the Wasm module is loaded and initialized. The TypeScript library is built into a single
ES6 (or CommonJS) module, and is output into the same directory as `package.json`. If you need to update the public API,
you can do so by editing the files in `src`.

If you make changes to the library that require updating the type definitions, such as adding a new public API method,
you should run:

```sh
npm run build:dts
```

This uses [`dts-buddy`][dts-buddy] to generate `web-tree-sitter.d.ts` from the public types in `src`. Additionally, a sourcemap
is generated for the `.d.ts` file, which enables `go-to definition` and other editor integrations to take you straight
to the TypeScript source code.

This TypeScript code is then compiled into a single JavaScript file with `esbuild`. The build configuration for this can
be found in [`script/build.js`][build.js], but this shouldn't need to be updated. This step is responsible for emitting
the final JS and Wasm files that are shipped with the library, as well as their sourcemaps.



### Debugging

You might have noticed that when you ran `npm build`, the build process generated a couple of [sourcemaps][sourcemap]:
`web-tree-sitter.js.map` and `web-tree-sitter.wasm.map`. These sourcemaps can be used to debug the library in the browser, and are
shipped with the library on both NPM and the GitHub releases.

#### Tweaking the Emscripten build

If you're trying to tweak the Emscripten build, or are trying to debug an issue, the code for this lies in `xtask/src/build_wasm.rs`
file mentioned earlier, namely in the `run_wasm` function.

[bindings.ts]: src/bindings.ts
[build.js]: script/build.js
[covenant]: https://www.contributor-covenant.org/version/1/4/code-of-conduct
[dts-buddy]: https://github.com/Rich-Harris/dts-buddy
[exports.txt]: lib/exports.txt
[sourcemap]: https://developer.mozilla.org/en-US/docs/Glossary/Source_map
[tree-sitter.c]: lib/tree-sitter.c
[tree-sitter.d.ts]: lib/tree-sitter.d.ts
