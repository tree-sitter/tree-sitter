module.exports = async ({ github, context, core }) => {
  if (context.eventName !== 'pull_request') return;

  const prNumber = context.payload.pull_request.number;
  const owner = context.repo.owner;
  const repo = context.repo.repo;

  const files = await github.paginate(github.rest.pulls.listFiles, {
    owner,
    repo,
    pull_number: prNumber,
    per_page: 100
  });

  const changedFiles = files.map(file => file.filename);

  const wasmStdLibSources = [
    'lib/src/wasm-stdlib/external_scanner_allocator.c',
    'lib/src/wasm-stdlib/imports.txt',
    'lib/src/wasm-stdlib/libc.c',
    'lib/src/wasm-stdlib/stdio.c'
  ];
  const dirChanged = changedFiles.some(file =>
    wasmStdLibSources.includes(file) ||
    file.startsWith('lib/src/wasm-stdlib/libc/ctype/') ||
    file.startsWith('lib/src/wasm-stdlib/libc/string/')
  );

  if (!dirChanged) return;

  const wasmStdLibHeader = 'lib/src/wasm-stdlib/external_scanner_stdlib.h';
  const requiredChanged = changedFiles.includes(wasmStdLibHeader);

  if (!requiredChanged) core.setFailed(`Changes detected in the Wasm stdlib sources but ${wasmStdLibHeader} was not modified.`);
};
