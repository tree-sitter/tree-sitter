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

let worker;
const uiRuntime = await WebAssembly.instantiate(runtimeModule, {
  env: {
    memory,
    request_parse(sourceAddress, sourceLength, oldTree) {
      const source = new TextDecoder().decode(
        new Uint8Array(memory.buffer, sourceAddress, sourceLength),
      );
      worker.postMessage(oldTree ? { text: source, oldTree: true } : { text: source });
    },
  },
});
for (const name of ['initialize', 'start', 'tree_ready']) {
  if (typeof uiRuntime.exports[name] !== 'function') {
    throw new Error(`Rust test module did not export ${name}`);
  }
}
uiRuntime.exports.initialize();

worker = new Worker(new URL('./worker.mjs', import.meta.url), {
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
        if (message?.tree !== true) {
          throw new Error('worker did not return a tree');
        }
        if (uiRuntime.exports.tree_ready()) {
          finished = true;
          resolve();
        }
      } catch (error) {
        reject(error);
      }
    });
    uiRuntime.exports.start();
  });
} finally {
  await worker.terminate();
}
