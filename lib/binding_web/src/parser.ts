import { C, INTERNAL, Point, Range, SIZE_OF_INT, SIZE_OF_RANGE } from './constants';
import { Language } from './language';
import { marshalRange, unmarshalRange } from './marshal';
import { Tree } from './tree';

interface ParseOptions {
  includedRanges?: Range[];
  progressCallback?: (percent: number) => void;
}

type ParseCallback = ((index: number, position: Point) => string) | string;
type LogCallback = ((message: string, type: number, row: number, column: number) => void) | null;

// Global variable for transferring data across the FFI boundary
export let TRANSFER_BUFFER: number;

let VERSION: number;
let MIN_COMPATIBLE_VERSION: number;

let currentParseCallback: ((index: number, position: Point) => string) | null = null;
// eslint-disable-next-line @typescript-eslint/no-unused-vars
let currentLogCallback: LogCallback = null;
// eslint-disable-next-line @typescript-eslint/no-unused-vars
let currentProgressCallback: ((percent: number) => void) | null = null;

export class ParserImpl {
  protected [0] = 0;
  protected [1] = 0;
  protected language: Language | null = null;
  protected logCallback: LogCallback = null;
  static Language: typeof Language;

  static init() {
    TRANSFER_BUFFER = C._ts_init();
    VERSION = getValue(TRANSFER_BUFFER, 'i32');
    MIN_COMPATIBLE_VERSION = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
  }

  initialize() {
    C._ts_parser_new_wasm();
    this[0] = getValue(TRANSFER_BUFFER, 'i32');
    this[1] = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
  }

  delete() {
    C._ts_parser_delete(this[0]);
    C._free(this[1]);
    this[0] = 0;
    this[1] = 0;
  }

  setLanguage(language: Language | null): this {
    let address: number;
    if (!language) {
      address = 0;
      this.language = null;
    } else if (language.constructor === Language) {
      address = language[0];
      const version = C._ts_language_version(address);
      if (version < MIN_COMPATIBLE_VERSION || VERSION < version) {
        throw new Error(
          `Incompatible language version ${version}. ` +
          `Compatibility range ${MIN_COMPATIBLE_VERSION} through ${VERSION}.`
        );
      }
      this.language = language;
    } else {
      throw new Error('Argument must be a Language');
    }

    C._ts_parser_set_language(this[0], address);
    return this;
  }

  getLanguage(): Language | null {
    return this.language;
  }

  parse(
    callback: ParseCallback,
    oldTree?: Tree | null,
    options: ParseOptions = {}
  ): Tree {
    if (typeof callback === 'string') {
      currentParseCallback = (index: number) => callback.slice(index);
    } else if (typeof callback === 'function') {
      currentParseCallback = callback;
    } else {
      throw new Error('Argument must be a string or a function');
    }

    if (options.progressCallback) {
      currentProgressCallback = options.progressCallback;
    } else {
      currentProgressCallback = null;
    }

    if (this.logCallback) {
      currentLogCallback = this.logCallback;
      C._ts_parser_enable_logger_wasm(this[0], 1);
    } else {
      currentLogCallback = null;
      C._ts_parser_enable_logger_wasm(this[0], 0);
    }

    let rangeCount = 0;
    let rangeAddress = 0;
    if (options.includedRanges) {
      rangeCount = options.includedRanges.length;
      rangeAddress = C._calloc(rangeCount, SIZE_OF_RANGE);
      let address = rangeAddress;
      for (let i = 0; i < rangeCount; i++) {
        marshalRange(address, options.includedRanges[i]);
        address += SIZE_OF_RANGE;
      }
    }

    const treeAddress = C._ts_parser_parse_wasm(
      this[0],
      this[1],
      oldTree ? oldTree[0] : 0,
      rangeAddress,
      rangeCount
    );

    if (!treeAddress) {
      currentParseCallback = null;
      currentLogCallback = null;
      currentProgressCallback = null;
      throw new Error('Parsing failed');
    }

    if (!this.language) {
      throw new Error('Parser must have a language to parse');
    }

    const result = new Tree(INTERNAL, treeAddress, this.language, currentParseCallback);
    currentParseCallback = null;
    currentLogCallback = null;
    currentProgressCallback = null;
    return result;
  }

  reset(): void {
    C._ts_parser_reset(this[0]);
  }

  getIncludedRanges(): Range[] {
    C._ts_parser_included_ranges_wasm(this[0]);
    const count = getValue(TRANSFER_BUFFER, 'i32');
    const buffer = getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
    const result = new Array<Range>(count);

    if (count > 0) {
      let address = buffer;
      for (let i = 0; i < count; i++) {
        result[i] = unmarshalRange(address);
        address += SIZE_OF_RANGE;
      }
      C._free(buffer);
    }

    return result;
  }

  getTimeoutMicros(): number {
    return C._ts_parser_timeout_micros(this[0]);
  }

  setTimeoutMicros(timeout: number): void {
    C._ts_parser_set_timeout_micros(this[0], timeout);
  }

  setLogger(callback: LogCallback): this {
    if (!callback) {
      this.logCallback = null;
    } else if (typeof callback !== 'function') {
      throw new Error('Logger callback must be a function');
    } else {
      this.logCallback = callback;
    }
    return this;
  }

  getLogger(): LogCallback {
    return this.logCallback;
  }
}
