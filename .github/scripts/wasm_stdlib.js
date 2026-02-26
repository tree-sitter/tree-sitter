module.exports = async ({ github, context, core }) => {
  if (context.eventName !== 'pull_request') return;

  const prNumber = context.payload.pull_request.number;
  const owner = context.repo.owner;
  const repo = context.repo.repo;

  const { data: files } = await github.rest.pulls.listFiles({
    owner,
    repo,
    pull_number: prNumber
  });

  const changedFiles = files.map(file => file.filename);

  const wasmStdLibSrc = 'crates/language/wasm/';
  const dirChanged = changedFiles.some(file => file.startsWith(wasmStdLibSrc));

  if (!dirChanged) return;

  const wasmStdLibHeader = 'lib/src/wasm/wasm-stdlib.h';
  const requiredChanged = changedFiles.includes(wasmStdLibHeader);

  if (!requiredChanged) core.setFailed(`Changes detected in ${wasmStdLibSrc} but ${wasmStdLibHeader} was not modified.`);
};
