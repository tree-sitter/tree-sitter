import fs from 'node:fs/promises';
import { Worker } from 'node:worker_threads';

const MEMORY_PAGES = 256;
const MAX_MEMORY_PAGES = 4096;

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
if (typeof uiRuntime.exports.inspect !== 'function') {
  throw new Error('Rust test module did not export inspect');
}

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
        if (message.type === 'tree') {
          const tree = uiRuntime.exports.inspect(message.tree);
          if (!tree) {
            reject(new Error('UI thread could not inspect the transferred Rust Tree'));
            return;
          }
          worker.postMessage({ type: 'tree', tree });
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
