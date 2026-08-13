import fs from 'node:fs/promises';
import { Worker } from 'node:worker_threads';

const MEMORY_PAGES = 256;
const MAX_MEMORY_PAGES = 4096;
const INITIAL_SOURCE = '{"value": 1}';
const UPDATED_SOURCE = '{"value": [1, 2, 3], "nested": {"enabled": true}}';

const [runtimePath, languagePath] = process.argv.slice(2);
if (!runtimePath || !languagePath) {
  throw new Error('usage: node run.mjs <runtime.wasm> <language.wasm>');
}

const runtimeModule = await WebAssembly.compile(await fs.readFile(runtimePath));
const languageModule = await WebAssembly.compile(await fs.readFile(languagePath));
const memory = new WebAssembly.Memory({
  initial: MEMORY_PAGES,
  maximum: MAX_MEMORY_PAGES,
  shared: true,
});
if (!(memory.buffer instanceof SharedArrayBuffer)) {
  throw new Error('WebAssembly memory is not shared');
}

const uiRuntime = await WebAssembly.instantiate(runtimeModule, { env: { memory } });
for (const name of ['initialize', 'inspect_initial_tree', 'edit_tree', 'inspect_new_tree']) {
  if (typeof uiRuntime.exports[name] !== 'function') {
    throw new Error(`Rust test module did not export ${name}`);
  }
}
uiRuntime.exports.initialize();

const worker = new Worker(new URL('./worker.mjs', import.meta.url), {
  workerData: { runtimeModule, languageModule, memory },
});

function requestParse(request) {
  return new Promise((resolve, reject) => {
    const onError = error => {
      worker.off('message', onMessage);
      reject(error);
    };
    const onMessage = message => {
      worker.off('error', onError);
      if (message?.tree === true) {
        resolve(message.tree);
      } else {
        reject(new Error('worker did not return a tree'));
      }
    };
    worker.once('error', onError);
    worker.once('message', onMessage);
    worker.postMessage(request);
  });
}

function check(result, operation) {
  if (result !== 0) {
    throw new Error(`UI thread failed to ${operation}: ${result}`);
  }
}

try {
  let tree = await requestParse({ text: INITIAL_SOURCE });
  check(uiRuntime.exports.inspect_initial_tree(), 'inspect the initial tree');
  check(uiRuntime.exports.edit_tree(), 'edit the initial tree');
  tree = await requestParse({ text: UPDATED_SOURCE, oldTree: tree });
  check(uiRuntime.exports.inspect_new_tree(), 'inspect the new tree');
} finally {
  await worker.terminate();
}
