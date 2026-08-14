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
    'lib/src/wasm/external_scanner_allocator.c',
    'lib/src/wasm/stdlib-symbols.txt'
  ];
  const dirChanged = changedFiles.some(file => wasmStdLibSources.includes(file));

  if (!dirChanged) return;

  const wasmStdLibHeader = 'lib/src/wasm/wasm-stdlib.h';
  const requiredChanged = changedFiles.includes(wasmStdLibHeader);

  if (!requiredChanged) core.setFailed(`Changes detected in the Wasm stdlib sources but ${wasmStdLibHeader} was not modified.`);
};
