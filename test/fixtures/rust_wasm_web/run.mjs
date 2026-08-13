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
let pendingRequest = 0;
const uiRuntime = await WebAssembly.instantiate(runtimeModule, {
  env: {
    memory,
    request_parse(sourceAddress, sourceLength, oldTree, requestAddress) {
      if (pendingRequest !== 0) {
        throw new Error('Rust requested another parse before the prior request completed');
      }
      const source = new TextDecoder().decode(
        new Uint8Array(memory.buffer, sourceAddress, sourceLength),
      );
      pendingRequest = requestAddress;
      worker.postMessage(oldTree ? { text: source, oldTree } : { text: source });
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
        if (!Number.isInteger(message?.tree) || message.tree === 0) {
          throw new Error('worker did not return a tree');
        }
        const request = pendingRequest;
        if (request === 0) {
          throw new Error('worker returned a tree without a pending request');
        }
        pendingRequest = 0;
        if (uiRuntime.exports.tree_ready(request, message.tree)) {
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
