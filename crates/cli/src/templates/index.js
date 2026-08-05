import { readFileSync } from "node:fs";
import { fileURLToPath } from "node:url";

const root = fileURLToPath(new URL("../..", import.meta.url));

const binding = typeof process.versions.bun === "string"
  // Support `bun build --compile` by being statically analyzable enough to find the .node file at build-time
  ? await import(`${root}/prebuilds/${process.platform}-${process.arch}/tree-sitter-KEBAB_PARSER_NAME.node`)
  : (await import("node-gyp-build")).default(root);

try {
  const nodeTypes = await import(`${root}/src/node-types.json`, { with: { type: "json" } });
  binding.nodeTypeInfo = nodeTypes.default;
} catch { }

const queries = [
  ["HIGHLIGHTS_QUERY", `${root}/HIGHLIGHTS_QUERY_PATH`],
  ["INJECTIONS_QUERY", `${root}/INJECTIONS_QUERY_PATH`],
  ["LOCALS_QUERY", `${root}/LOCALS_QUERY_PATH`],
  ["TAGS_QUERY", `${root}/TAGS_QUERY_PATH`],
];

for (const [prop, path] of queries) {
  Object.defineProperty(binding, prop, {
    configurable: true,
    enumerable: true,
    get() {
      delete binding[prop];
      try {
        binding[prop] = readFileSync(path, "utf8");
      } catch { }
      return binding[prop];
    }
  });
}

export default binding;
