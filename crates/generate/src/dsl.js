// Module grammars export opaque rule handles and default-export configuration.
// Expression constructors and the legacy grammar() API precede this file in
// the embedded DSL. Neither implementation depends on Node-specific APIs.
const ruleDefinitions = new WeakMap();

function makeRuleHandle(definition) {
  const handle = Object.freeze({});
  ruleDefinitions.set(handle, definition);
  return handle;
}

function rule(build) {
  if (build === undefined) {
    return makeRuleHandle({ symbol: Symbol(), alias: true });
  }
  if (typeof build !== "function") {
    throw new TypeError("rule() expects a zero-argument function, or no arguments for an alias-only symbol.");
  }
  return makeRuleHandle({ symbol: Symbol(), build });
}

function external() {
  return makeRuleHandle({ symbol: Symbol(), external: true });
}

function override(base, build) {
  const definition = ruleDefinitions.get(base);
  if (!definition || !definition.build) {
    throw new TypeError("override() expects an inherited rule handle with a body as its first argument.");
  }
  if (typeof build !== "function") {
    throw new TypeError("override() expects a zero-argument function as its second argument.");
  }
  return makeRuleHandle({ symbol: definition.symbol, build, base });
}

function withContext(description, operation) {
  try {
    return operation();
  } catch (error) {
    // Keep the original exception and its source stack, including helper calls.
    if (error instanceof Error) {
      error.message = `${description}: ${error.message}`;
      throw error;
    }
    throw new Error(`${description}: ${String(error)}`);
  }
}

function moduleConfiguration(module) {
  const config = module?.default;
  if (!config || typeof config !== "object" || Array.isArray(config) || config.grammar) {
    throw new TypeError("A module grammar must default-export a configuration object and named-export its rule() handles.");
  }
  if (typeof config.name !== "string" || !/^[a-zA-Z_]\w*$/.test(config.name)) {
    throw new Error("Grammar's 'name' must be a string starting with a letter or underscore and containing only word characters.");
  }
  const options = new Set([
    "name", "start", "extends", "extras", "externals", "word", "conflicts",
    "inline", "supertypes", "precedences", "reserved",
  ]);
  for (const name of Object.keys(config)) {
    if (!options.has(name)) {
      throw new Error(`Unknown module grammar option '${name}'. Rules must be named exports, not a 'rules' property.`);
    }
  }
  return config;
}

// Collect definitions without evaluating bodies. In particular, an overridden
// base body must not run, and compiling a derived grammar must not mutate its
// base. Symbol identity survives overriding; the active builder does not.
function collectModule(module, ancestors = new Set()) {
  if (ancestors.has(module)) {
    throw new Error("Cyclic module grammar inheritance.");
  }
  const config = moduleConfiguration(module);
  ancestors.add(module);
  const base = config.extends === undefined ? undefined : collectModule(config.extends, ancestors);
  ancestors.delete(module);

  const rules = new Map(base?.rules);
  const symbols = new Map(base?.symbols);
  for (const name of Object.keys(module)) {
    if (name === "default") continue;
    if (!/^[a-zA-Z_]\w*$/.test(name)) {
      throw new Error(`Invalid exported rule name '${name}'.`);
    }
    const handle = module[name];
    const definition = ruleDefinitions.get(handle);
    if (!definition) {
      throw new TypeError(`Export '${name}' is not a rule handle. Use rule(() => ...), or keep helpers unexported.`);
    }
    const previousName = symbols.get(definition.symbol);
    if (previousName !== undefined && previousName !== name) {
      throw new Error(`The same rule is exported as both '${previousName}' and '${name}'. Each symbol must have one name.`);
    }
    const previous = rules.get(name);
    if (previous !== undefined && previous !== handle) {
      if (!definition.base || ruleDefinitions.get(previous).symbol !== definition.symbol) {
        throw new Error(`Rule '${name}' replaces an inherited rule without override().`);
      }
    }
    if (definition.base && !base?.symbols.has(definition.symbol)) {
      throw new Error(`Override '${name}' does not belong to the grammar specified by 'extends'.`);
    }
    rules.set(name, handle);
    symbols.set(definition.symbol, name);
  }

  for (const source of [base?.config.reserved, config.reserved]) {
    if (source !== undefined && (!source || typeof source !== "object" || Array.isArray(source))) {
      throw new TypeError("Grammar's 'reserved' property must be an object of expression arrays.");
    }
  }
  return {
    rules,
    symbols,
    inherits: base?.config.name,
    config: {
      ...base?.config,
      ...config,
      reserved: { ...base?.config.reserved, ...config.reserved },
    },
  };
}

function compileModule(module) {
  const { rules, symbols, config, inherits } = collectModule(module);
  function symbolName(handle) {
    const definition = ruleDefinitions.get(handle);
    if (!definition) {
      throw new TypeError("Expected a rule handle.");
    }
    const name = symbols.get(definition.symbol);
    if (name === undefined) {
      throw new Error("Unregistered rule handle. Export the rule from this grammar, or inherit its module with 'extends'.");
    }
    return name;
  }

  function checkReference(name) {
    const definition = ruleDefinitions.get(rules.get(name));
    if (!definition) {
      throw new Error(`Undefined symbol '${name}'.`);
    }
    if (definition.alias) {
      throw new Error(`Symbol '${name}' has no rule body. Symbols declared with rule() may only be used as alias targets.`);
    }
    return name;
  }

  function referenceName(handle) {
    return checkReference(symbolName(handle));
  }

  // Expressions can be built during module initialization (e.g. in extras), so
  // constructors preserve handles until this grammar's registry is complete.
  function resolve(value) {
    if (ruleDefinitions.has(value)) {
      return sym(referenceName(value));
    }
    const expression = normalize(value);
    const result = { ...expression };
    if ("content" in expression) result.content = resolve(expression.content);
    if ("members" in expression) result.members = expression.members.map(resolve);
    if (expression.type === "ALIAS" && ruleDefinitions.has(expression.value)) {
      result.value = symbolName(expression.value);
    }
    if (expression.type === "SYMBOL") {
      checkReference(expression.name);
    }
    return result;
  }

  function array(value, description) {
    if (!Array.isArray(value)) {
      throw new TypeError(`${description} must be an array.`);
    }
    return value;
  }

  function option(name, fallback, convert) {
    return withContext(`Grammar option '${name}'`, () =>
      convert(config[name] === undefined ? fallback : config[name]));
  }

  const start = withContext("Grammar option 'start'", () => {
    if (config.start === undefined) {
      throw new Error("Specify a start rule handle. Module export order does not determine the start rule.");
    }
    const name = referenceName(config.start);
    if (ruleDefinitions.get(rules.get(name)).external) {
      throw new Error("The start rule must have a body, not be an external token.");
    }
    return name;
  });

  const externals = option("externals", [], value =>
    array(value, "Externals").map(resolve));
  const externalNames = new Set(externals.filter(e => e.type === "SYMBOL").map(e => e.name));
  for (const [name, handle] of rules) {
    if (ruleDefinitions.get(handle).external && !externalNames.has(name)) {
      throw new Error(`External token '${name}' must be listed in 'externals' to specify its scanner order.`);
    }
  }

  // The generator's JSON format uses the first rule as the start rule. Module
  // namespace keys are sorted, so explicitly emit the selected rule first.
  const orderedRules = new Map([[start, rules.get(start)], ...rules]);
  const bodies = [];
  for (const [name, handle] of orderedRules) {
    const definition = ruleDefinitions.get(handle);
    if (definition.external || definition.alias) continue;
    const body = withContext(`Rule '${name}'`, () => {
      const value = definition.build();
      if (value === undefined) {
        throw new Error("Returned undefined. Did you forget to return the rule expression?");
      }
      return resolve(value);
    });
    bodies.push([name, body]);
  }

  return {
    name: config.name,
    inherits,
    rules: Object.fromEntries(bodies),
    extras: option("extras", [/\s/], value => array(value, "Extras").map(resolve)),
    externals,
    word: config.word === undefined ? undefined : option("word", undefined, referenceName),
    conflicts: option("conflicts", [], value => array(value, "Conflicts").map(
      set => array(set, "Each conflict set").map(referenceName))),
    inline: option("inline", [], value => array(value, "Inline rules").map(referenceName)),
    supertypes: option("supertypes", [], value => array(value, "Supertypes").map(referenceName)),
    precedences: option("precedences", [], value => array(value, "Precedences").map(
      list => array(list, "Each precedence list").map(entry => {
        if (typeof entry === "string") return normalize(entry);
        return sym(referenceName(entry));
      }))),
    reserved: option("reserved", {}, value => Object.fromEntries(
      Object.entries(value).map(([name, entries]) =>
        [name, array(entries, `Reserved word set '${name}'`).map(resolve)]))),
  };
}

function getEnv(name) {
  if (globalThis.native) return globalThis.__ts_grammar_path;
  if (globalThis.process) return process.env[name]; // Node/Bun
  if (globalThis.Deno) return Deno.env.get(name); // Deno
  throw Error("Unsupported JS runtime");
}

Object.assign(globalThis, {
  alias, blank, eof, choice, optional, prec, repeat, repeat1, reserved, seq,
  sym, token, grammar, field, RustRegex, rule, override, external,
});

const grammarPath = getEnv("TREE_SITTER_GRAMMAR_PATH");
const result = await import(grammarPath);

// Detect the API from evaluated exports, not source syntax or file extension:
// both legacy and module grammars can be authored as ES modules.
// A module rule can itself be named "grammar", so a truthy export is not enough.
const legacyGrammar = [
  result.default?.grammar,
  result.grammar,
  globalThis.native && Object.keys(result).length === 0
    ? globalThis.module?.exports?.grammar
    : undefined,
].find(value => value && typeof value.name === "string"
  && value.rules && typeof value.rules === "object");
const grammarObj = legacyGrammar ?? compileModule(result);
const output = JSON.stringify({
  "$schema": "https://tree-sitter.github.io/tree-sitter/assets/schemas/grammar.schema.json",
  ...grammarObj,
});

if (globalThis.native) {
  globalThis.output = output;
} else if (globalThis.process) { // Node/Bun
  process.stdout.write(output);
} else if (globalThis.Deno) { // Deno
  Deno.stdout.writeSync(new TextEncoder().encode(output));
} else {
  throw Error("Unsupported JS runtime");
}
