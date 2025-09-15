const root = new URL("../..", import.meta.url).pathname;

const binding = typeof process.versions.bun === "string"
  // Support `bun build --compile` by being statically analyzable enough to find the .node file at build-time
  ? await import(`../../prebuilds/${process.platform}-${process.arch}/tree-sitter-KEBAB_PARSER_NAME.node`)
  : await import("node-gyp-build");

const result = binding.default ? binding.default(root) : binding(root);

try {
  const nodeTypeInfo = await import("../../src/node-types.json", {assert: {type: "json"}});
  result.nodeTypeInfo = nodeTypeInfo.default;
} catch (_) {}

export default result;
