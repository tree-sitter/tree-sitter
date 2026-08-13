import { parentPort, workerData } from 'node:worker_threads';

const PAGE_SIZE = 64 * 1024;
const SIDE_MODULE_DATA_PAGES = 32;
const SIDE_MODULE_STACK_PAGES = 16;
const SIDE_MODULE_TABLE_ELEMENTS = 1024;
const RUNTIME_STACK_PAGES = 16;

const { control, runtimeModule, languageModule, memory } = workerData;
const runtime = await WebAssembly.instantiate(runtimeModule, {
  env: {
    memory,
    request_parse() {
      throw new Error('parsing worker unexpectedly requested a parse');
    },
    pause_worker() {
      parentPort.postMessage({ parsing: true });
      Atomics.wait(control, 0, 0);
    },
  },
});
const {
  __stack_pointer: stackPointer,
  __indirect_function_table: table,
  allocate_language_memory: allocateLanguageMemory,
  allocate_source: allocateSource,
  initialize,
  parse_and_return: parseAndReturn,
} = runtime.exports;

if (!(table instanceof WebAssembly.Table)) {
  throw new Error('Rust test module did not export its indirect function table');
}
if (!(stackPointer instanceof WebAssembly.Global)) {
  throw new Error('Rust test module did not export its stack pointer');
}
for (const [name, value] of [
  ['allocate_language_memory', allocateLanguageMemory],
  ['allocate_source', allocateSource],
  ['initialize', initialize],
  ['parse_and_return', parseAndReturn],
]) {
  if (typeof value !== 'function') {
    throw new Error(`Rust test module did not export ${name}`);
  }
}
initialize();

const runtimeStackBase = allocateLanguageMemory(RUNTIME_STACK_PAGES * PAGE_SIZE, PAGE_SIZE);
if (!runtimeStackBase) {
  throw new Error('Rust test module failed to allocate the worker runtime stack');
}
stackPointer.value = runtimeStackBase + RUNTIME_STACK_PAGES * PAGE_SIZE;

const memoryBase = allocateLanguageMemory(
  (SIDE_MODULE_DATA_PAGES + SIDE_MODULE_STACK_PAGES) * PAGE_SIZE,
  PAGE_SIZE,
);
if (!memoryBase) {
  throw new Error('Rust test module failed to allocate language memory');
}
const tableBase = table.length;
table.grow(SIDE_MODULE_TABLE_ELEMENTS);

const imports = {
  env: {
    memory,
    __indirect_function_table: table,
    __memory_base: new WebAssembly.Global({ value: 'i32', mutable: false }, memoryBase),
    __table_base: new WebAssembly.Global({ value: 'i32', mutable: false }, tableBase),
    __stack_pointer: new WebAssembly.Global(
      { value: 'i32', mutable: true },
      memoryBase + (SIDE_MODULE_DATA_PAGES + SIDE_MODULE_STACK_PAGES) * PAGE_SIZE,
    ),
  },
};

const language = await WebAssembly.instantiate(languageModule, imports);
if (typeof language.exports.__wasm_apply_data_relocs === 'function') {
  language.exports.__wasm_apply_data_relocs();
}
const languageFunction = Object.entries(language.exports).find(
  ([name, value]) => /^tree_sitter_\w+$/.test(name) && typeof value === 'function',
);
if (!languageFunction) {
  throw new Error('language module did not export a tree_sitter_* function');
}
const languageAddress = languageFunction[1]();

parentPort.postMessage({ ready: true });

parentPort.on('message', message => {
  if (
    typeof message?.text !== 'string' ||
    (message.oldTree !== undefined &&
      (!Number.isInteger(message.oldTree) || message.oldTree === 0))
  ) {
    throw new Error('expected a text string and an optional oldTree');
  }
  const source = new TextEncoder().encode(message.text);
  const sourceAddress = allocateSource(source.length);
  if (!sourceAddress) {
    throw new Error('parsing worker failed to allocate source text');
  }
  new Uint8Array(memory.buffer, sourceAddress, source.length).set(source);
  const tree = parseAndReturn(
    languageAddress,
    sourceAddress,
    source.length,
    message.oldTree ?? 0,
  );
  if (tree === 0) {
    throw new Error('parsing worker failed to parse JavaScript');
  }
  parentPort.postMessage({ tree });
});
