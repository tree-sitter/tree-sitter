import { C, Internal, assertInternal } from './constants';
import { Language } from './language';

export class LookaheadIterator implements Iterable<string> {
  private [0]: number; // Internal handle for WASM
  private language: Language;

  constructor(internal: Internal, address: number, language: Language) {
    assertInternal(internal);
    this[0] = address;
    this.language = language;
  }

  get currentTypeId(): number {
    return C._ts_lookahead_iterator_current_symbol(this[0]);
  }

  get currentType(): string {
    return this.language.types[this.currentTypeId] || 'ERROR';
  }

  delete(): void {
    C._ts_lookahead_iterator_delete(this[0]);
    this[0] = 0;
  }

  resetState(stateId: number): boolean {
    return Boolean(C._ts_lookahead_iterator_reset_state(this[0], stateId));
  }

  reset(language: Language, stateId: number): boolean {
    if (C._ts_lookahead_iterator_reset(this[0], language[0], stateId)) {
      this.language = language;
      return true;
    }
    return false;
  }

  [Symbol.iterator](): Iterator<string> {
    return {
      next: (): IteratorResult<string> => {
        if (C._ts_lookahead_iterator_next(this[0])) {
          return { done: false, value: this.currentType };
        }
        return { done: true, value: '' };
      }
    };
  }
}
