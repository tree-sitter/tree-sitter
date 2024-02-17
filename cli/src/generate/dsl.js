function alias(rule, value) {
  const result = {
    type: "ALIAS",
    content: normalize(rule),
    named: false,
    value: null
  };

  switch (value.constructor) {
    case String:
      result.named = false;
      result.value = value;
      return result;
    case ReferenceError:
      result.named = true;
      result.value = value.symbol.name;
      return result;
    case Object:
      if (typeof value.type === 'string' && value.type === 'SYMBOL') {
        result.named = true;
        result.value = value.name;
        return result;
      }
  }

  throw new Error('Invalid alias value ' + value);
}

function blank() {
  return {
    type: "BLANK"
  };
}

function field(name, rule) {
  return {
    type: "FIELD",
    name: name,
    content: normalize(rule)
  }
}

function choice(...elements) {
  return {
    type: "CHOICE",
    members: elements.map(normalize)
  };
}

function optional(value) {
  checkArguments(arguments.length, optional, 'optional');
  return choice(value, blank());
}

function prec(number, rule) {
  checkPrecedence(number);
  checkArguments(
    arguments.length - 1,
    prec,
    'prec',
    ' and a precedence argument'
  );

  return {
    type: "PREC",
    value: number,
    content: normalize(rule)
  };
}

prec.left = function(number, rule) {
  if (rule == null) {
    rule = number;
    number = 0;
  }

  checkPrecedence(number);
  checkArguments(
    arguments.length - 1,
    prec.left,
    'prec.left',
    ' and an optional precedence argument'
  );

  return {
    type: "PREC_LEFT",
    value: number,
    content: normalize(rule)
  };
}

prec.right = function(number, rule) {
  if (rule == null) {
    rule = number;
    number = 0;
  }

  checkPrecedence(number);
  checkArguments(
    arguments.length - 1,
    prec.right,
    'prec.right',
    ' and an optional precedence argument'
  );

  return {
    type: "PREC_RIGHT",
    value: number,
    content: normalize(rule)
  };
}

prec.dynamic = function(number, rule) {
  checkPrecedence(number);
  checkArguments(
    arguments.length - 1,
    prec.dynamic,
    'prec.dynamic',
    ' and a precedence argument'
  );

  return {
    type: "PREC_DYNAMIC",
    value: number,
    content: normalize(rule)
  };
}

function repeat(rule) {
  checkArguments(arguments.length, repeat, 'repeat');
  return {
    type: "REPEAT",
    content: normalize(rule)
  };
}

function repeat1(rule) {
  checkArguments(arguments.length, repeat1, 'repeat1');
  return {
    type: "REPEAT1",
    content: normalize(rule)
  };
}

function seq(...elements) {
  return {
    type: "SEQ",
    members: elements.map(normalize)
  };
}

function sym(name) {
  return {
    type: "SYMBOL",
    name: name
  };
}

function token(value) {
  checkArguments(arguments.length, token, 'token', '', 'literal');
  return {
    type: "TOKEN",
    content: normalize(value)
  };
}

token.immediate = function(value) {
  checkArguments(arguments.length, token.immediate, 'token.immediate', '', 'literal');
  return {
    type: "IMMEDIATE_TOKEN",
    content: normalize(value)
  };
}

function normalize(value) {
  if (typeof value == "undefined")
    throw new Error("Undefined symbol");

  switch (value.constructor) {
    case String:
      return {
        type: 'STRING',
        value
      };
    case RegExp:
      return value.flags ? {
        type: 'PATTERN',
        value: value.source,
        flags: value.flags
      } : {
        type: 'PATTERN',
        value: value.source
      };
    case ReferenceError:
      throw value
    default:
      if (typeof value.type === 'string') {
        return value;
      } else {
        throw new TypeError("Invalid rule: " + value.toString());
      }
  }
}

function RuleBuilder(ruleMap) {
  return new Proxy({}, {
    get(target, propertyName) {
      const symbol = sym(propertyName);

      if (!ruleMap || ruleMap.hasOwnProperty(propertyName)) {
        return symbol;
      } else {
        const error = new ReferenceError(`Undefined symbol '${propertyName}'`);
        error.symbol = symbol;
        return error;
      }
    }
  })
}

function grammar(baseGrammar, options) {
  if (!options) {
    options = baseGrammar;
    baseGrammar = {
      name: null,
      rules: {},
      extras: [normalize(/\s/)],
      conflicts: [],
      externals: [],
      inline: [],
      supertypes: [],
      precedences: [],
    };
  } else {
    baseGrammar = baseGrammar.grammar;
  }

  let externals = baseGrammar.externals;
  if (options.externals) {
    if (typeof options.externals !== "function") {
      throw new Error("Grammar's 'externals' property must be a function.");
    }

    const externalsRuleBuilder = RuleBuilder(null)
    const externalRules = options.externals.call(externalsRuleBuilder, externalsRuleBuilder, baseGrammar.externals);

    if (!Array.isArray(externalRules)) {
      throw new Error("Grammar's 'externals' property must return an array of rules.");
    }

    externals = externalRules.map(normalize);
  }

  const ruleMap = {};
  for (const key in options.rules) {
    ruleMap[key] = true;
  }
  for (const key in baseGrammar.rules) {
    ruleMap[key] = true;
  }
  for (const external of externals) {
    if (typeof external.name === 'string') {
      ruleMap[external.name] = true;
    }
  }

  const ruleBuilder = RuleBuilder(ruleMap);

  const name = options.name;
  if (typeof name !== "string") {
    throw new Error("Grammar's 'name' property must be a string.");
  }

  if (!/^[a-zA-Z_]\w*$/.test(name)) {
    throw new Error("Grammar's 'name' property must not start with a digit and cannot contain non-word characters.");
  }

  let rules = Object.assign({}, baseGrammar.rules);
  if (options.rules) {
    if (typeof options.rules !== "object") {
      throw new Error("Grammar's 'rules' property must be an object.");
    }

    for (const ruleName in options.rules) {
      const ruleFn = options.rules[ruleName];
      if (typeof ruleFn !== "function") {
        throw new Error("Grammar rules must all be functions. '" + ruleName + "' rule is not.");
      }
      rules[ruleName] = normalize(ruleFn.call(ruleBuilder, ruleBuilder, baseGrammar.rules[ruleName]));
    }
  }

  let extras = baseGrammar.extras.slice();
  if (options.extras) {
    if (typeof options.extras !== "function") {
      throw new Error("Grammar's 'extras' property must be a function.");
    }

    extras = options.extras
      .call(ruleBuilder, ruleBuilder, baseGrammar.extras)

    if (!Array.isArray(extras)) {
      throw new Error("Grammar's 'extras' function must return an array.")
    }

    extras = extras.map(normalize);
  }

  let word = baseGrammar.word;
  if (options.word) {
    word = options.word.call(ruleBuilder, ruleBuilder).name;
    if (typeof word != 'string') {
      throw new Error("Grammar's 'word' property must be a named rule.");
    }

    if (word === 'ReferenceError') {
      throw new Error("Grammar's 'word' property must be a valid rule name.");
    }
  }

  let conflicts = baseGrammar.conflicts;
  if (options.conflicts) {
    if (typeof options.conflicts !== "function") {
      throw new Error("Grammar's 'conflicts' property must be a function.");
    }

    const baseConflictRules = baseGrammar.conflicts.map(conflict => conflict.map(sym));
    const conflictRules = options.conflicts.call(ruleBuilder, ruleBuilder, baseConflictRules);

    if (!Array.isArray(conflictRules)) {
      throw new Error("Grammar's conflicts must be an array of arrays of rules.");
    }

    conflicts = conflictRules.map(conflictSet => {
      if (!Array.isArray(conflictSet)) {
        throw new Error("Grammar's conflicts must be an array of arrays of rules.");
      }

      return conflictSet.map(symbol => normalize(symbol).name);
    });
  }

  let inline = baseGrammar.inline;
  if (options.inline) {
    if (typeof options.inline !== "function") {
      throw new Error("Grammar's 'inline' property must be a function.");
    }

    const baseInlineRules = baseGrammar.inline.map(sym);
    const inlineRules = options.inline.call(ruleBuilder, ruleBuilder, baseInlineRules);

    if (!Array.isArray(inlineRules)) {
      throw new Error("Grammar's inline must be an array of rules.");
    }

    inline = inlineRules.filter((symbol, index, self) => {
      if (self.findIndex(s => s.name === symbol.name) !== index) {
        console.log(`Warning: duplicate inline rule '${symbol.name}'`);
        return false;
      }
      if (symbol.name === 'ReferenceError') {
        console.log(`Warning: inline rule '${symbol.symbol.name}' is not defined.`);
        return false;
      }
      return true;
    }).map(symbol => symbol.name);
  }

  let supertypes = baseGrammar.supertypes;
  if (options.supertypes) {
    if (typeof options.supertypes !== "function") {
      throw new Error("Grammar's 'supertypes' property must be a function.");
    }

    const baseSupertypeRules = baseGrammar.supertypes.map(sym);
    const supertypeRules = options.supertypes.call(ruleBuilder, ruleBuilder, baseSupertypeRules);

    if (!Array.isArray(supertypeRules)) {
      throw new Error("Grammar's supertypes must be an array of rules.");
    }

    supertypes = supertypeRules.map(symbol => symbol.name);
  }

  let precedences = baseGrammar.precedences;
  if (options.precedences) {
    if (typeof options.precedences !== "function") {
      throw new Error("Grammar's 'precedences' property must be a function");
    }
    precedences = options.precedences.call(ruleBuilder, ruleBuilder, baseGrammar.precedences);
    if (!Array.isArray(precedences)) {
      throw new Error("Grammar's precedences must be an array of arrays of rules.");
    }
    precedences = precedences.map(list => {
      if (!Array.isArray(list)) {
        throw new Error("Grammar's precedences must be an array of arrays of rules.");
      }
      return list.map(normalize);
    });
  }

  if (Object.keys(rules).length == 0) {
    throw new Error("Grammar must have at least one rule.");
  }

  return { grammar: { name, word, rules, extras, conflicts, precedences, externals, inline, supertypes } };
}

function checkArguments(ruleCount, caller, callerName, suffix = '', argType = 'rule') {
  if (ruleCount > 1) {
    const error = new Error([
      `The \`${callerName}\` function only takes one ${argType} argument${suffix}.`,
      `You passed in multiple ${argType}s. Did you mean to call \`seq\`?\n`
    ].join('\n'));
    Error.captureStackTrace(error, caller);
    throw error
  }
}

function checkPrecedence(value) {
  if (value == null) {
    throw new Error('Missing precedence value');
  }
}

global.alias = alias;
global.blank = blank;
global.choice = choice;
global.optional = optional;
global.prec = prec;
global.repeat = repeat;
global.repeat1 = repeat1;
global.seq = seq;
global.sym = sym;
global.token = token;
global.grammar = grammar;
global.field = field;

const result = require(process.env.TREE_SITTER_GRAMMAR_PATH);
process.stdout.write(JSON.stringify(result.grammar, null, null));
