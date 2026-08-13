import fs from 'node:fs/promises';
import { Worker } from 'node:worker_threads';

const MEMORY_PAGES = 256;
const MAX_MEMORY_PAGES = 4096;
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
for (const name of ['initialize', 'edit_and_publish', 'inspect_new_tree_and_publish']) {
  if (typeof uiRuntime.exports[name] !== 'function') {
    throw new Error(`Rust test module did not export ${name}`);
  }
}
uiRuntime.exports.initialize();

const worker = new Worker(new URL('./worker.mjs', import.meta.url), {
  workerData: { runtimeModule, languageModule, memory },
});

try {
  await new Promise((resolve, reject) => {
    let finished = false;
    worker.once('error', reject);
    worker.once('exit', code => {
      if (!finished) {
        reject(new Error(`worker exited before completing the test with code ${code}`));
      }
    });
    worker.on('message', message => {
      try {
        if (message.type === 'initial-tree-ready') {
          const result = uiRuntime.exports.edit_and_publish();
          if (result !== 0) {
            reject(new Error(`UI thread failed to edit the initial tree: ${result}`));
            return;
          }
          worker.postMessage({ type: 'edited-tree-ready', source: UPDATED_SOURCE });
        } else if (message.type === 'new-tree-ready') {
          const result = uiRuntime.exports.inspect_new_tree_and_publish();
          if (result !== 0) {
            reject(new Error(`UI thread failed to inspect the new tree: ${result}`));
            return;
          }
          worker.postMessage({ type: 'new-tree-returned' });
        } else if (message.type === 'done') {
          finished = true;
          if (message.result === 0) {
            resolve();
          } else {
            reject(new Error(`parsing worker returned ${message.result}`));
          }
        }
      } catch (error) {
        reject(error);
      }
    });
  });
} finally {
  await worker.terminate();
}
