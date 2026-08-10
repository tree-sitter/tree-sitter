import { C, Internal, assertInternal } from './constants';
import { Language } from './language';
import { newFinalizer } from './finalization_registry';

const finalizer = newFinalizer((address: number) => {
  C._ts_lookahead_iterator_delete(address);
});

export class LookaheadIterator implements Iterable<string> {
  /** @internal */
  private [0] = 0; // Internal handle for Wasm

  /** @internal */
  private language: Language;

  /** @internal */
  private positioned = false;

  /** @internal */
  constructor(internal: Internal, address: number, language: Language) {
    assertInternal(internal);
    this[0] = address;
    this.language = language;
    finalizer?.register(this, address, this);
  }

  /**
   * Get the current symbol of the lookahead iterator.
   *
   * Returns `null` if the iterator is not positioned on a symbol:
   *
   * - Before the first iteration step
   * - After the iterator is exhausted
   * - After a {@link reset} or {@link resetState} call
   */
  get currentTypeId(): number | null {
    return this.positioned ?
      C._ts_lookahead_iterator_current_symbol(this[0]) : null;
  }

  /**
   * Get the current symbol name of the lookahead iterator.
   *
   * Returns `null` if the iterator is not positioned on a symbol.
   */
  get currentType(): string | null {
    const id = this.currentTypeId;
    if (id === null) return null;
    // `Language.types` only holds regular and anonymous symbols, so auxiliary
    // ones (i.e. `end`) fall back to the language's own name table.
    return this.language.types[id] ??
      C.UTF8ToString(C._ts_language_symbol_name(this.language[0], id));
  }

  /** Delete the lookahead iterator, freeing its resources. */
  delete(): void {
    finalizer?.unregister(this);
    C._ts_lookahead_iterator_delete(this[0]);
    this[0] = 0;
  }


  /**
   * Reset the lookahead iterator.
   *
   * This returns `true` if the language was set successfully and `false`
   * otherwise.
   */
  reset(language: Language, stateId: number): boolean {
    if (C._ts_lookahead_iterator_reset(this[0], language[0], stateId)) {
      this.language = language;
      this.positioned = false;
      return true;
    }
    return false;
  }

  /**
   * Reset the lookahead iterator to another state.
   *
   * This returns `true` if the iterator was reset to the given state and
   * `false` otherwise.
   */
  resetState(stateId: number): boolean {
    if (!C._ts_lookahead_iterator_reset_state(this[0], stateId)) return false;
    this.positioned = false;
    return true;
  }

  /**
   * Returns an iterator that iterates over the symbols of the lookahead iterator.
   *
   * The iterator will yield the current symbol name as a string for each step
   * until there are no more symbols to iterate over.
   */
  [Symbol.iterator](): Iterator<string> {
    return {
      next: (): IteratorResult<string> => {
        this.positioned = Boolean(C._ts_lookahead_iterator_next(this[0]));
        const value = this.currentType;
        return value === null
          ? { done: true, value: '' }
          : { done: false, value };
      }
    };
  }
}
