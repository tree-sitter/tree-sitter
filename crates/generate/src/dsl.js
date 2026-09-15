// Module grammars export opaque rule handles and default-export configuration.
// Expression constructors and the legacy grammar() API precede this file in
// the embedded DSL. Neither implementation depends on Node-specific APIs.
const ruleDefinitions = new WeakMap();
let nextRuleOrder = 0;

// Error.stack is not standardized, but is supported by Node, Bun, Deno, and
// QuickJS. Filter by source identity, never by function names: grammar helpers
// can legitimately be named "normalize", "rule", etc. The bootstrap's identity
// is assigned by the sourceURL below and by the embedded QuickJS loader.
function grammarStack(error) {
  let stack = error?.stack;
  if (typeof stack !== "string") return [];

  // V8 includes the error heading; QuickJS normally supplies frames only.
  const heading = String(error);
  if (stack.startsWith(heading)) stack = stack.slice(heading.length);
  // A user may have changed error.message after materializing .stack. Select
  // frames independently of that heading, rather than reporting the stale text.
  const frames = stack.split(/\r?\n/).filter(line =>
    /^\s*at(?:\s|$)/.test(line) || /^[^\n]*@.+:\d+(?::\d+)?$/.test(line));
  const result = [];
  let internalCaller = false;
  for (let index = frames.length - 1; index >= 0; index--) {
    const frame = frames[index];
    if (!frame.trim()) continue;
    const internal = /(?:\(|@|\s)tree-sitter:grammar-dsl(?::\d+){0,2}\)?$/.test(frame)
      || /(?:\(|@|\s)node:internal\//.test(frame);
    const native = /\((?:native|<anonymous>|\[native code\])\)$/.test(frame);
    if (internal || (native && internalCaller)) {
      internalCaller = true;
    } else {
      internalCaller = false;
      result.push(frame);
    }
  }
  return result.reverse();
}

function diagnosticError(thrown, description, fallbackStack = [], seen = new Map()) {
  if (seen.has(thrown)) return seen.get(thrown);
  const message = thrown instanceof Error ? thrown.message : String(thrown);
  const error = new Error(description ? `${description}: ${message}` : message);
  if (thrown instanceof Error) error.name = thrown.name;
  const frames = grammarStack(thrown);
  // Copy rather than mutate user exceptions, which may be frozen. Rebuild the
  // heading as well, so materializing a stack before adding context is harmless.
  error.stack = [String(error), ...(frames.length ? frames : fallbackStack)].join("\n");
  if (thrown instanceof Error) {
    seen.set(thrown, error);
    if ("cause" in thrown) {
      error.cause = diagnosticError(thrown.cause, undefined, [], seen);
    }
    if (Array.isArray(thrown.errors)) {
      error.errors = thrown.errors.map(member => diagnosticError(member, undefined, [], seen));
    }
  }
  return error;
}

function formatDiagnostic(error, ancestors = new Set()) {
  if (ancestors.has(error)) return "[Circular error]";
  ancestors.add(error);
  let output = error.stack;
  if ("cause" in error) {
    output += `\nCaused by:\n${formatDiagnostic(error.cause, ancestors)}`;
  }
  if (Array.isArray(error.errors)) {
    error.errors.forEach((member, index) => {
      output += `\nAggregate error ${index + 1}:\n${formatDiagnostic(member, ancestors)}`;
    });
  }
  ancestors.delete(error);
  return output;
}

function makeRuleHandle(definition) {
  const handle = Object.freeze({});
  definition.order = nextRuleOrder++;
  definition.declarationStack = grammarStack(new Error());
  ruleDefinitions.set(handle, definition);
  return handle;
}

function rule(build) {
  if (build === undefined) {
    return makeRuleHandle({ alias: true });
  }
  if (typeof build !== "function") {
    throw new TypeError("rule() expects a zero-argument function, or no arguments for an alias-only symbol.");
  }
  return makeRuleHandle({ build });
}

function external() {
  return makeRuleHandle({ external: true });
}

function withContext(description, operation, fallbackStack) {
  try {
    return operation();
  } catch (error) {
    throw diagnosticError(error, description, fallbackStack);
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
  const exports = Object.entries(module).filter(([name]) => name !== "default").map(([name, handle]) => {
    if (!/^[a-zA-Z_]\w*$/.test(name)) {
      throw new Error(`Invalid exported rule name '${name}'.`);
    }
    const definition = ruleDefinitions.get(handle);
    if (!definition) {
      throw new TypeError(`Export '${name}' is not a rule handle. Use rule(() => ...), or keep helpers unexported.`);
    }
    return { name, handle, definition };
  });
  // Namespace keys are alphabetized, but rule order breaks lexical ties. Use
  // declaration/construction order; Map.set keeps inherited override slots.
  exports.sort((left, right) => left.definition.order - right.definition.order);
  for (const { name, handle } of exports) {
    const previousName = symbols.get(handle);
    if (previousName !== undefined && previousName !== name) {
      throw new Error(`The same rule is exported as both '${previousName}' and '${name}'. Each symbol must have one name.`);
    }
    const previous = rules.get(name);
    if (previous?.handle === handle) continue;
    // Keep predecessor records separate from handles. A handle may be re-exported
    // in another inheritance layer without changing its original definition.
    rules.set(name, { handle, previous });
    symbols.set(handle, name);
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
    const name = symbols.get(handle);
    if (name === undefined) {
      let message = "Unregistered rule handle. Export the rule from this grammar, or inherit its module with 'extends'.";
      if (definition.declarationStack.length) {
        message += "\nUnexported rule declared at:";
      }
      throw diagnosticError(new Error(message), undefined, definition.declarationStack);
    }
    return name;
  }

  function checkReference(name) {
    const definition = ruleDefinitions.get(rules.get(name)?.handle);
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
    if (ruleDefinitions.get(rules.get(name).handle).external) {
      throw new Error("The start rule must have a body, not be an external token.");
    }
    return name;
  });

  const externals = option("externals", [], value =>
    array(value, "Externals").map(resolve));
  const externalNames = new Set(externals.filter(e => e.type === "SYMBOL").map(e => e.name));
  for (const [name, { handle }] of rules) {
    if (ruleDefinitions.get(handle).external && !externalNames.has(name)) {
      throw new Error(`External token '${name}' must be listed in 'externals' to specify its scanner order.`);
    }
  }

  const evaluated = new Map();
  const evaluating = new Set();
  function evaluate(record, inherited = false) {
    if (evaluated.has(record)) {
      const result = evaluated.get(record);
      if ("error" in result) throw result.error;
      return result.body;
    }
    const name = symbolName(record.handle);
    const definition = ruleDefinitions.get(record.handle);
    if (evaluating.has(record)) {
      throw new Error(`Recursive original() evaluation for rule '${name}'.`);
    }
    evaluating.add(record);
    try {
      const body = withContext(inherited ? `Original body of rule '${name}'` : `Rule '${name}'`, () => {
        // Previous bodies are evaluated only on demand. Resolve again to give
        // the callback its own copy, so edits cannot mutate cached/base bodies.
        const original = () => {
          if (!record.previous || !ruleDefinitions.get(record.previous.handle).build) {
            throw new Error(`Rule '${name}' has no inherited body.`);
          }
          return resolve(evaluate(record.previous, true));
        };
        const value = definition.build(original);
        if (value === undefined) {
          throw new Error("Returned undefined. Did you forget to return the rule expression?");
        }
        return resolve(value);
      }, definition.declarationStack);
      evaluated.set(record, { body });
      return body;
    } catch (error) {
      evaluated.set(record, { error });
      throw error;
    } finally {
      evaluating.delete(record);
    }
  }

  // The JSON format uses the first rule as the start rule. Other rules keep
  // declaration order, independently of how the module enumerates its exports.
  const orderedRules = new Map([[start, rules.get(start)], ...rules]);
  const bodies = [];
  for (const [name, record] of orderedRules) {
    const definition = ruleDefinitions.get(record.handle);
    if (definition.external || definition.alias) continue;
    bodies.push([name, evaluate(record)]);
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
  sym, token, grammar, field, RustRegex, rule, external,
});

try {
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
} catch (thrown) {
  const error = diagnosticError(thrown);
  const report = formatDiagnostic(error);
  if (globalThis.native) {
    error.stack = report;
    throw error;
  } else if (globalThis.process) {
    // Node retains syntax-error source excerpts outside .stack. Preserve that
    // metadata when possible: parser errors originate in the imported source,
    // not in our diagnostic wrapper.
    if (thrown instanceof SyntaxError && !("cause" in thrown) && !Array.isArray(thrown.errors)) {
      let canRethrow = false;
      try {
        Object.defineProperty(thrown, "stack", {
          value: report, configurable: true, writable: true,
        });
        canRethrow = true;
      } catch {
        // A frozen/custom error can still be reported below without mutation.
      }
      if (canRethrow) throw thrown;
    }
    // Do not let the engine's uncaught-exception reporter print the internal
    // throw site/source excerpt after we have removed it from the stack.
    process.stderr.write(`${report}\n`);
    process.exitCode = 1;
  } else if (globalThis.Deno) {
    Deno.stderr.writeSync(new TextEncoder().encode(`${report}\n`));
    Deno.exitCode = 1;
  } else {
    throw error;
  }
}

//# sourceURL=tree-sitter:grammar-dsl
