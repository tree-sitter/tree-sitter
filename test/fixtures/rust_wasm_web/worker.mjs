import { parentPort, workerData } from 'node:worker_threads';

const PAGE_SIZE = 64 * 1024;
const SIDE_MODULE_DATA_PAGES = 32;
const SIDE_MODULE_STACK_PAGES = 16;
const SIDE_MODULE_TABLE_ELEMENTS = 1024;
const RUNTIME_STACK_PAGES = 16;

const { control, runtimeModule, languageModules, memory } = workerData;

const runtime = await WebAssembly.instantiate(runtimeModule, {
  env: {
    memory,
    request_parse() {
      throw new Error('parsing worker unexpectedly requested a parse');
    },
    log() {
      throw new Error('parsing worker unexpectedly logged UI progress');
    },
    notify_parsing_started() {
      parentPort.postMessage({ parsing: true });
      Atomics.wait(control, 0, 0);
    },
  },
});

const {
  __stack_pointer: stackPointer,
  __indirect_function_table: table,
  allocate_language_memory: allocateLanguageMemory,
  run_parse: runParse,
} = runtime.exports;

const runtimeStackBase = allocateLanguageMemory(RUNTIME_STACK_PAGES * PAGE_SIZE, PAGE_SIZE);
if (!runtimeStackBase) {
  throw new Error('Rust test module failed to allocate the worker runtime stack');
}
stackPointer.value = runtimeStackBase + RUNTIME_STACK_PAGES * PAGE_SIZE;

function loadLanguage(languageModule) {
  const memoryBase = allocateLanguageMemory(
    (SIDE_MODULE_DATA_PAGES + SIDE_MODULE_STACK_PAGES) * PAGE_SIZE,
    PAGE_SIZE,
  );
  const tableBase = table.length;
  table.grow(SIDE_MODULE_TABLE_ELEMENTS);

  const env = {
    memory,
    __indirect_function_table: table,
    __memory_base: new WebAssembly.Global({ value: 'i32', mutable: false }, memoryBase),
    __table_base: new WebAssembly.Global({ value: 'i32', mutable: false }, tableBase),
    __stack_pointer: new WebAssembly.Global(
      { value: 'i32', mutable: true },
      memoryBase + (SIDE_MODULE_DATA_PAGES + SIDE_MODULE_STACK_PAGES) * PAGE_SIZE,
    ),
  };
  for (const { module, name, kind } of WebAssembly.Module.imports(languageModule)) {
    if (module === 'env' && kind === 'function') {
      const implementation = runtime.exports[name];
      if (typeof implementation !== 'function') {
        throw new Error(`Rust test module does not export ${name}`);
      }
      env[name] = implementation;
    }
  }

  return WebAssembly.instantiate(languageModule, { env }).then(language => {
    if (typeof language.exports.__wasm_apply_data_relocs === 'function') {
      language.exports.__wasm_apply_data_relocs();
    }
    const languageFunction = Object.entries(language.exports).find(
      ([name, value]) => /^tree_sitter_\w+$/.test(name) && typeof value === 'function',
    );
    if (!languageFunction) {
      throw new Error('language module did not export a tree_sitter_* function');
    }
    return languageFunction[1]();
  });
}

const languageAddresses = await Promise.all(languageModules.map(loadLanguage));

parentPort.postMessage({ ready: true });

parentPort.on('message', message => {
  const languageAddress =
    message.languageId === 0 ? 0 : languageAddresses[message.languageId - 1];
  const tree = runParse(
    languageAddress,
    message.sourceAddress,
    message.sourceLength,
    message.oldTree ?? 0,
  );
  if (tree === 0) {
    throw new Error(`parsing worker failed to parse language ${message.languageId}`);
  }
  parentPort.postMessage({ tree });
});
