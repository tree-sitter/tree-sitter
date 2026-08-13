import { parentPort, workerData } from 'node:worker_threads';

const PAGE_SIZE = 64 * 1024;
const SIDE_MODULE_DATA_PAGES = 32;
const SIDE_MODULE_STACK_PAGES = 16;
const SIDE_MODULE_TABLE_ELEMENTS = 1024;

const { runtimeModule, languageModule, memory } = workerData;
const runtime = await WebAssembly.instantiate(runtimeModule, { env: { memory } });
const {
  __indirect_function_table: table,
  allocate_language_memory: allocateLanguageMemory,
  parse,
  reuse_and_delete: reuseAndDelete,
} = runtime.exports;

if (!(table instanceof WebAssembly.Table)) {
  throw new Error('Rust test module did not export its indirect function table');
}
for (const [name, value] of [
  ['allocate_language_memory', allocateLanguageMemory],
  ['parse', parse],
  ['reuse_and_delete', reuseAndDelete],
]) {
  if (typeof value !== 'function') {
    throw new Error(`Rust test module did not export ${name}`);
  }
}

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

const tree = parse(languageAddress);
if (!tree) {
  throw new Error('parsing worker failed to create a Rust Tree');
}
parentPort.postMessage({ type: 'tree', tree });

parentPort.once('message', message => {
  if (message.type !== 'tree') {
    throw new Error(`unexpected worker message ${message.type}`);
  }
  parentPort.postMessage({
    type: 'done',
    result: reuseAndDelete(languageAddress, message.tree),
  });
});
