import { C, INTERNAL, LogCallback, ParseCallback, Range, SIZE_OF_INT, SIZE_OF_RANGE, setModule } from './constants';
import { Language } from './language';
import { marshalRange, unmarshalRange } from './marshal';
import { checkModule, initializeBinding } from './bindings';
import { Tree } from './tree';

export interface ParseOptions {
  includedRanges?: Range[];
  progressCallback?: (state: ParseState) => void;
}

export interface ParseState {
  currentOffset: number;
}

// Global variable for transferring data across the FFI boundary
export let TRANSFER_BUFFER: number;

let VERSION: number;
let MIN_COMPATIBLE_VERSION: number;

export class Parser {
  /** @internal */
  private [0] = 0; // Internal handle for WASM

  /** @internal */
  private [1] = 0; // Internal handle for WASM

  /** @internal */
  private language: Language | null = null;

  /** @internal */
  private logCallback: LogCallback | null = null;

  /**
   * This must always be called before creating a Parser.
   */
  static async init(moduleOptions?: EmscriptenModule) {
    setModule(await initializeBinding(moduleOptions));
    TRANSFER_BUFFER = C._ts_init();
    VERSION = C.getValue(TRANSFER_BUFFER, 'i32');
    MIN_COMPATIBLE_VERSION = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
  }

  constructor() {
    this.initialize();
  }

  initialize() {
    if (!checkModule()) {
      throw new Error("cannot construct a Parser before calling `init()`");
    }
    C._ts_parser_new_wasm();
    this[0] = C.getValue(TRANSFER_BUFFER, 'i32');
    this[1] = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
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
    callback: string | ParseCallback,
    oldTree?: Tree | null,
    options: ParseOptions = {}
  ): Tree {
    if (typeof callback === 'string') {
      C.currentParseCallback = (index: number) => callback.slice(index);
    } else if (typeof callback === 'function') {
      C.currentParseCallback = callback;
    } else {
      throw new Error('Argument must be a string or a function');
    }

    if (options.progressCallback) {
      C.currentProgressCallback = options.progressCallback;
    } else {
      C.currentProgressCallback = null;
    }

    if (this.logCallback) {
      C.currentLogCallback = this.logCallback;
      C._ts_parser_enable_logger_wasm(this[0], 1);
    } else {
      C.currentLogCallback = null;
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
      C.currentParseCallback = null;
      C.currentLogCallback = null;
      C.currentProgressCallback = null;
      throw new Error('Parsing failed');
    }

    if (!this.language) {
      throw new Error('Parser must have a language to parse');
    }

    const result = new Tree(INTERNAL, treeAddress, this.language, C.currentParseCallback);
    C.currentParseCallback = null;
    C.currentLogCallback = null;
    C.currentProgressCallback = null;
    return result;
  }

  reset(): void {
    C._ts_parser_reset(this[0]);
  }

  getIncludedRanges(): Range[] {
    C._ts_parser_included_ranges_wasm(this[0]);
    const count = C.getValue(TRANSFER_BUFFER, 'i32');
    const buffer = C.getValue(TRANSFER_BUFFER + SIZE_OF_INT, 'i32');
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
    C._ts_parser_set_timeout_micros(this[0], 0, timeout);
  }

  setLogger(callback: LogCallback | boolean | null): this {
    if (!callback) {
      this.logCallback = null;
    } else if (typeof callback !== 'function') {
      throw new Error('Logger callback must be a function');
    } else {
      this.logCallback = callback;
    }
    return this;
  }

  getLogger(): LogCallback | null {
    return this.logCallback;
  }
}
