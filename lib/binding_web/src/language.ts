import { C, INTERNAL, Internal, assertInternal, SIZE_OF_INT, SIZE_OF_SHORT } from './constants';
import { LookaheadIterator } from './lookahead_iterator';
import { Node } from './node';
import { TRANSFER_BUFFER } from './parser';
import { CaptureQuantifier, Predicate, PredicateStep, Properties, Query, TextPredicate } from './query';

const PREDICATE_STEP_TYPE_CAPTURE = 1;
const PREDICATE_STEP_TYPE_STRING = 2;

const QUERY_WORD_REGEX = /[\w-]+/g;
const LANGUAGE_FUNCTION_REGEX = /^tree_sitter_\w+$/;

export class Language {
  private [0]: number; // Internal handle for WASM
  public types: string[];
  public fields: (string | null)[];

  constructor(internal: Internal, address: number) {
    assertInternal(internal);
    this[0] = address;
    this.types = new Array<string>(C._ts_language_symbol_count(this[0]));
    for (let i = 0, n = this.types.length; i < n; i++) {
      if (C._ts_language_symbol_type(this[0], i) < 2) {
        this.types[i] = C.UTF8ToString(C._ts_language_symbol_name(this[0], i));
      }
    }
    this.fields = new Array<string>(C._ts_language_field_count(this[0]) + 1);
    for (let i = 0, n = this.fields.length; i < n; i++) {
      const fieldName = C._ts_language_field_name_for_id(this[0], i);
      if (fieldName !== 0) {
        this.fields[i] = C.UTF8ToString(fieldName);
      } else {
        this.fields[i] = null;
      }
    }
  }

  get name(): string | null {
    const ptr = C._ts_language_name(this[0]);
    if (ptr === 0) return null;
    return C.UTF8ToString(ptr);
  }

  get version(): number {
    return C._ts_language_version(this[0]);
  }

  get fieldCount(): number {
    return this.fields.length - 1;
  }

  get stateCount(): number {
    return C._ts_language_state_count(this[0]);
  }

  fieldIdForName(fieldName: string): number | null {
    const result = this.fields.indexOf(fieldName);
    return result !== -1 ? result : null;
  }

  fieldNameForId(fieldId: number): string | null {
    return this.fields[fieldId] ?? null;
  }

  idForNodeType(type: string, named: boolean): number | null {
    const typeLength = C.lengthBytesUTF8(type);
    const typeAddress = C._malloc(typeLength + 1);
    C.stringToUTF8(type, typeAddress, typeLength + 1);
    const result = C._ts_language_symbol_for_name(this[0], typeAddress, typeLength, named ? 1 : 0);
    C._free(typeAddress);
    return result || null;
  }

  get nodeTypeCount(): number {
    return C._ts_language_symbol_count(this[0]);
  }

  nodeTypeForId(typeId: number): string | null {
    const name = C._ts_language_symbol_name(this[0], typeId);
    return name ? C.UTF8ToString(name) : null;
  }

  nodeTypeIsNamed(typeId: number): boolean {
    return C._ts_language_type_is_named_wasm(this[0], typeId) ? true : false;
  }

  nodeTypeIsVisible(typeId: number): boolean {
    return C._ts_language_type_is_visible_wasm(this[0], typeId) ? true : false;
  }

  get supertypes(): number[] {
    C._ts_language_supertypes_wasm(this[0]);
    const count = C.getValue(TRANSFER_BUFFER, 'i32');
    const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array<number>(count);

    if (count > 0) {
      let address = buffer;
      for (let i = 0; i < count; i++) {
        result[i] = C.getValue(address, 'i16');
        address += SIZE_OF_SHORT;
      }
    }

    return result;
  }

  subtypes(supertype: number): number[] {
    C._ts_language_subtypes_wasm(this[0], supertype);
    const count = C.getValue(TRANSFER_BUFFER, 'i32');
    const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array<number>(count);

    if (count > 0) {
      let address = buffer;
      for (let i = 0; i < count; i++) {
        result[i] = C.getValue(address, 'i16');
        address += SIZE_OF_SHORT;
      }
    }

    return result;
  }

  nextState(stateId: number, typeId: number): number {
    return C._ts_language_next_state(this[0], stateId, typeId);
  }

  lookaheadIterator(stateId: number): LookaheadIterator | null {
    const address = C._ts_lookahead_iterator_new(this[0], stateId);
    if (address) return new LookaheadIterator(INTERNAL, address, this);
    return null;
  }

  query(source: string): Query {
    const sourceLength = C.lengthBytesUTF8(source);
    const sourceAddress = C._malloc(sourceLength + 1);
    C.stringToUTF8(source, sourceAddress, sourceLength + 1);
    const address = C._ts_query_new(
      this[0],
      sourceAddress,
      sourceLength,
      TRANSFER_BUFFER,
      TRANSFER_BUFFER + SIZE_OF_INT
    );

    if (!address) {
      const errorId = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
      const errorByte = C.getValue(TRANSFER_BUFFER, 'i32');
      const errorIndex = C.UTF8ToString(sourceAddress, errorByte).length;
      const suffix = source.slice(errorIndex, errorIndex + 100).split('\n')[0];
      let word = suffix.match(QUERY_WORD_REGEX)?.[0] ?? '';
      let error: Error;

      switch (errorId) {
        case 2:
          error = new RangeError(`Bad node name '${word}'`);
          break;
        case 3:
          error = new RangeError(`Bad field name '${word}'`);
          break;
        case 4:
          error = new RangeError(`Bad capture name @${word}`);
          break;
        case 5:
          error = new TypeError(`Bad pattern structure at offset ${errorIndex}: '${suffix}'...`);
          word = '';
          break;
        default:
          error = new SyntaxError(`Bad syntax at offset ${errorIndex}: '${suffix}'...`);
          word = '';
          break;
      }

      // eslint-disable-next-line @typescript-eslint/no-explicit-any, @typescript-eslint/no-unsafe-member-access
      (error as any).index = errorIndex;
      // eslint-disable-next-line @typescript-eslint/no-explicit-any, @typescript-eslint/no-unsafe-member-access
      (error as any).length = word.length;
      C._free(sourceAddress);
      throw error;
    }

    const stringCount = C._ts_query_string_count(address);
    const captureCount = C._ts_query_capture_count(address);
    const patternCount = C._ts_query_pattern_count(address);
    const captureNames = new Array<string>(captureCount);
    const captureQuantifiers = new Array<CaptureQuantifier[]>(patternCount);
    const stringValues = new Array<string>(stringCount);

    for (let i = 0; i < captureCount; i++) {
      const nameAddress = C._ts_query_capture_name_for_id(
        address,
        i,
        TRANSFER_BUFFER
      );
      const nameLength = C.getValue(TRANSFER_BUFFER, 'i32');
      captureNames[i] = C.UTF8ToString(nameAddress, nameLength);
    }

    for (let i = 0; i < patternCount; i++) {
      const captureQuantifiersArray = new Array<CaptureQuantifier>(captureCount);
      for (let j = 0; j < captureCount; j++) {
        const quantifier = C._ts_query_capture_quantifier_for_id(address, i, j);
        captureQuantifiersArray[j] = quantifier as CaptureQuantifier;
      }
      captureQuantifiers[i] = captureQuantifiersArray;
    }

    for (let i = 0; i < stringCount; i++) {
      const valueAddress = C._ts_query_string_value_for_id(
        address,
        i,
        TRANSFER_BUFFER
      );
      const nameLength = C.getValue(TRANSFER_BUFFER, 'i32');
      stringValues[i] = C.UTF8ToString(valueAddress, nameLength);
    }

    const setProperties = new Array<Properties>(patternCount);
    const assertedProperties = new Array<Properties>(patternCount);
    const refutedProperties = new Array<Properties>(patternCount);
    const predicates = new Array<Predicate[]>(patternCount);
    const textPredicates = new Array<TextPredicate[]>(patternCount);

    for (let i = 0; i < patternCount; i++) {
      const predicatesAddress = C._ts_query_predicates_for_pattern(
        address,
        i,
        TRANSFER_BUFFER
      );
      const stepCount = C.getValue(TRANSFER_BUFFER, 'i32');

      predicates[i] = [];
      textPredicates[i] = [];

      const steps: PredicateStep[] = [];
      let stepAddress = predicatesAddress;
      for (let j = 0; j < stepCount; j++) {
        const stepType = C.getValue(stepAddress, 'i32');
        stepAddress += SIZE_OF_INT;
        const stepValueId: number = C.getValue(stepAddress, 'i32');
        stepAddress += SIZE_OF_INT;

        if (stepType === PREDICATE_STEP_TYPE_CAPTURE) {
          const name = captureNames[stepValueId];
          steps.push({ type: 'capture', name });
        } else if (stepType === PREDICATE_STEP_TYPE_STRING) {
          steps.push({ type: 'string', value: stringValues[stepValueId] });
        } else if (steps.length > 0) {
          if (steps[0].type !== 'string') {
            throw new Error('Predicates must begin with a literal value');
          }

          const operator = steps[0].value;
          let isPositive = true;
          let matchAll = true;
          let captureName: string | undefined;

          switch (operator) {
            case 'any-not-eq?':
            case 'not-eq?':
              isPositive = false;
            case 'any-eq?':
            case 'eq?': {
              if (steps.length !== 3) {
                throw new Error(
                  `Wrong number of arguments to \`#${operator}\` predicate. Expected 2, got ${steps.length - 1}`
                );
              }
              if (steps[1].type !== 'capture') {
                throw new Error(
                  `First argument of \`#${operator}\` predicate must be a capture. Got "${steps[1].value}"`
                );
              }
              matchAll = !operator.startsWith('any-');
              if (steps[2].type === 'capture') {
                const captureName1 = steps[1].name;
                const captureName2 = steps[2].name;
                textPredicates[i].push((captures) => {
                  const nodes1: Node[] = [];
                  const nodes2: Node[] = [];
                  for (const c of captures) {
                    if (c.name === captureName1) nodes1.push(c.node);
                    if (c.name === captureName2) nodes2.push(c.node);
                  }
                  const compare = (n1: { text: string }, n2: { text: string }, positive: boolean) => {
                    return positive ? n1.text === n2.text : n1.text !== n2.text;
                  };
                  return matchAll
                    ? nodes1.every((n1) => nodes2.some((n2) => compare(n1, n2, isPositive)))
                    : nodes1.some((n1) => nodes2.some((n2) => compare(n1, n2, isPositive)));
                });
              } else {
                captureName = steps[1].name;
                const stringValue = steps[2].value;
                const matches = (n: Node) => n.text === stringValue;
                const doesNotMatch = (n: Node) => n.text !== stringValue;
                textPredicates[i].push((captures) => {
                  const nodes = [];
                  for (const c of captures) {
                    if (c.name === captureName) nodes.push(c.node);
                  }
                  const test = isPositive ? matches : doesNotMatch;
                  return matchAll ?
                    nodes.every(test) :
                    nodes.some(test);
                });
              }
              break;
            }

            case 'any-not-match?':
            case 'not-match?':
              isPositive = false;
            case 'any-match?':
            case 'match?': {
              if (steps.length !== 3) {
                throw new Error(
                  `Wrong number of arguments to \`#${operator}\` predicate. Expected 2, got ${steps.length - 1}.`,
                );
              }
              if (steps[1].type !== 'capture') {
                throw new Error(
                  `First argument of \`#${operator}\` predicate must be a capture. Got "${steps[1].value}".`,
                );
              }
              if (steps[2].type !== 'string') {
                throw new Error(
                  `Second argument of \`#${operator}\` predicate must be a string. Got @${steps[2].value}.`,
                );
              }
              captureName = steps[1].name;
              const regex = new RegExp(steps[2].value);
              matchAll = !operator.startsWith('any-');
              textPredicates[i].push((captures) => {
                const nodes = [];
                for (const c of captures) {
                  if (c.name === captureName) nodes.push(c.node.text);
                }
                const test = (text: string, positive: boolean) => {
                  return positive ?
                    regex.test(text) :
                    !regex.test(text);
                };
                if (nodes.length === 0) return !isPositive;
                return matchAll ?
                  nodes.every((text) => test(text, isPositive)) :
                  nodes.some((text) => test(text, isPositive));
              });
              break;
            }

            case 'set!': {
              if (steps.length < 2 || steps.length > 3) {
                throw new Error(
                  `Wrong number of arguments to \`#set!\` predicate. Expected 1 or 2. Got ${steps.length - 1}.`,
                );
              }
              if (steps.some((s) => s.type !== 'string')) {
                throw new Error(
                  `Arguments to \`#set!\` predicate must be a strings.".`,
                );
              }
              if (!setProperties[i]) setProperties[i] = {};
              setProperties[i][steps[1].value!] = steps[2]?.value ?? null;
              break;
            }

            case 'is?':
            case 'is-not?': {
              if (steps.length < 2 || steps.length > 3) {
                throw new Error(
                  `Wrong number of arguments to \`#${operator}\` predicate. Expected 1 or 2. Got ${steps.length - 1}.`,
                );
              }
              if (steps.some((s) => s.type !== 'string')) {
                throw new Error(
                  `Arguments to \`#${operator}\` predicate must be a strings.".`,
                );
              }
              const properties = operator === 'is?' ? assertedProperties : refutedProperties;
              if (!properties[i]) properties[i] = {};
              properties[i][steps[1].value!] = steps[2]?.value ?? null;
              break;
            }

            case 'not-any-of?':
              isPositive = false;
            case 'any-of?': {
              if (steps.length < 2) {
                throw new Error(
                  `Wrong number of arguments to \`#${operator}\` predicate. Expected at least 1. Got ${steps.length - 1}.`,
                );
              }
              if (steps[1].type !== 'capture') {
                throw new Error(
                  `First argument of \`#${operator}\` predicate must be a capture. Got "${steps[1].value}".`,
                );
              }
              for (let i = 2; i < steps.length; i++) {
                if (steps[i].type !== 'string') {
                  throw new Error(
                    `Arguments to \`#${operator}\` predicate must be a strings.".`,
                  );
                }
              }
              captureName = steps[1].name;
              const values = steps.slice(2).map((s) => s.value);
              textPredicates[i].push((captures) => {
                const nodes = [];
                for (const c of captures) {
                  if (c.name === captureName) nodes.push(c.node.text);
                }
                if (nodes.length === 0) return !isPositive;
                return nodes.every((text) => values.includes(text)) === isPositive;
              });
              break;
            }

            default:
              predicates[i].push({ operator, operands: steps.slice(1) });
          }

          steps.length = 0;
        }
      }

      Object.freeze(setProperties[i]);
      Object.freeze(assertedProperties[i]);
      Object.freeze(refutedProperties[i]);
    }

    C._free(sourceAddress);
    return new Query(
      INTERNAL,
      address,
      captureNames,
      captureQuantifiers,
      textPredicates,
      predicates,
      setProperties,
      assertedProperties,
      refutedProperties,
    );
  }

  static async load(input: string | Uint8Array): Promise<Language> {
    let bytes: Promise<Uint8Array>;
    if (input instanceof Uint8Array) {
      bytes = Promise.resolve(input);
    } else {
      if (globalThis.process.versions.node) {
        // eslint-disable-next-line @typescript-eslint/no-unsafe-assignment, @typescript-eslint/no-require-imports
        const fs: typeof import('fs/promises') = require('fs/promises');
        bytes = fs.readFile(input);
      } else {
        bytes = fetch(input)
          .then((response) => response.arrayBuffer()
            .then((buffer) => {
              if (response.ok) {
                return new Uint8Array(buffer);
              } else {
                const body = new TextDecoder('utf-8').decode(buffer);
                throw new Error(`Language.load failed with status ${response.status}.\n\n${body}`);
              }
            }));
      }
    }

    const mod = await C.loadWebAssemblyModule(await bytes, { loadAsync: true });
    const symbolNames = Object.keys(mod);
    const functionName = symbolNames.find((key) => LANGUAGE_FUNCTION_REGEX.test(key) && 
      !key.includes('external_scanner_'));
    if (!functionName) {
        console.log(`Couldn't find language function in WASM file. Symbols:\n${JSON.stringify(symbolNames, null, 2)}`);
        throw new Error('Language.load failed: no language function found in WASM file');
    }
    const languageAddress = mod[functionName]();
    return new Language(INTERNAL, languageAddress);
  }
}
