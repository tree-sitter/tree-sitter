declare module 'web-tree-sitter' {
  class Parser {
    /**
     *
     * @param moduleOptions Optional emscripten module-object, see https://emscripten.org/docs/api_reference/module.html
     */
    static init(moduleOptions?: object): Promise<void>;
    delete(): void;
    parse(input: string | Parser.Input, previousTree?: Parser.Tree, options?: Parser.Options): Parser.Tree;
    reset(): void;
    getLanguage(): Parser.Language;
    setLanguage(language?: Parser.Language | undefined | null): void;
    getLogger(): Parser.Logger;
    setLogger(logFunc?: Parser.Logger | undefined | null): void;
    setTimeoutMicros(value: number): void;
    getTimeoutMicros(): number;
  }

  namespace Parser {
    export type Options = {
      includedRanges?: Range[];
    };

    export type Point = {
      row: number;
      column: number;
    };

    export type Range = {
      startIndex: number,
      endIndex: number,
      startPosition: Point,
      endPosition: Point
    };

    export type Edit = {
      startIndex: number;
      oldEndIndex: number;
      newEndIndex: number;
      startPosition: Point;
      oldEndPosition: Point;
      newEndPosition: Point;
    };

    export type Logger = (
      message: string,
      params: { [param: string]: string },
      type: "parse" | "lex"
    ) => void;

    export type Input = (
      startIndex: number,
      startPoint?: Point,
      endIndex?: number,
    ) => string | null;

    export interface SyntaxNode {
      grammarId: number;
      tree: Tree;
      type: string;
      typeId: number;
      grammarType: string;
      isNamed: boolean;
      isMissing: boolean;
      hasChanges: boolean;
      hasError: boolean;
      isError: boolean;
      text: string;
      parseState: number;
      nextParseState: number;
      startPosition: Point;
      endPosition: Point;
      startIndex: number;
      endIndex: number;
      parent: SyntaxNode | null;
      children: Array<SyntaxNode>;
      namedChildren: Array<SyntaxNode>;
      childCount: number;
      namedChildCount: number;
      firstChild: SyntaxNode | null;
      firstNamedChild: SyntaxNode | null;
      lastChild: SyntaxNode | null;
      lastNamedChild: SyntaxNode | null;
      nextSibling: SyntaxNode | null;
      nextNamedSibling: SyntaxNode | null;
      previousSibling: SyntaxNode | null;
      previousNamedSibling: SyntaxNode | null;

      equals(other: SyntaxNode): boolean;
      toString(): string;
      child(index: number): SyntaxNode | null;
      namedChild(index: number): SyntaxNode | null;
      childForFieldId(fieldId: number): SyntaxNode | null;
      childForFieldName(fieldName: string): SyntaxNode | null;

      descendantForIndex(index: number): SyntaxNode;
      descendantForIndex(startIndex: number, endIndex: number): SyntaxNode;
      namedDescendantForIndex(index: number): SyntaxNode;
      namedDescendantForIndex(startIndex: number, endIndex: number): SyntaxNode;
      descendantForPosition(position: Point): SyntaxNode;
      descendantForPosition(startPosition: Point, endPosition: Point): SyntaxNode;
      namedDescendantForPosition(position: Point): SyntaxNode;
      namedDescendantForPosition(startPosition: Point, endPosition: Point): SyntaxNode;
      descendantsOfType(types: String | Array<String>, startPosition?: Point, endPosition?: Point): Array<SyntaxNode>;

      walk(): TreeCursor;
    }

    export interface TreeCursor {
      nodeType: string;
      nodeTypeId: number;
      nodeStateId: number;
      nodeText: string;
      nodeId: number;
      nodeIsNamed: boolean;
      nodeIsMissing: boolean;
      startPosition: Point;
      endPosition: Point;
      startIndex: number;
      endIndex: number;
      readonly currentNode: SyntaxNode;
      readonly currentFieldId: number;
      readonly currentFieldName: string;

      reset(node: SyntaxNode): void;
      resetTo(cursor: TreeCursor): void;
      delete(): void;
      gotoParent(): boolean;
      gotoFirstChild(): boolean;
      gotoLastChild(): boolean;
      gotoFirstChildForIndex(index: number): boolean;
      gotoNextSibling(): boolean;
      gotoPreviousSibling(): boolean;
    }

    export interface Tree {
      readonly rootNode: SyntaxNode;

      copy(): Tree;
      delete(): void;
      edit(delta: Edit): Tree;
      walk(): TreeCursor;
      getChangedRanges(other: Tree): Range[];
      getEditedRange(other: Tree): Range;
      getLanguage(): Language;
    }

    class Language {
      static load(input: string | Uint8Array): Promise<Language>;

      readonly version: number;
      readonly fieldCount: number;
      readonly stateCount: number;
      readonly nodeTypeCount: number;

      fieldNameForId(fieldId: number): string | null;
      fieldIdForName(fieldName: string): number | null;
      idForNodeType(type: string, named: boolean): number;
      nodeTypeForId(typeId: number): string | null;
      nodeTypeIsNamed(typeId: number): boolean;
      nodeTypeIsVisible(typeId: number): boolean;
      nextState(stateId: number, typeId: number): number;
      query(source: string): Query;
      lookaheadIterator(stateId: number): LookaheadIterable | null;
    }

    class LookaheadIterable {
      readonly language: Language;
      readonly currentTypeId: number;
      readonly currentType: string;

      delete(): void;
      resetState(stateId: number): boolean;
      reset(language: Language, stateId: number): boolean;
      [Symbol.iterator](): Iterator<string>;
    }

    interface QueryCapture {
      name: string;
      node: SyntaxNode;
    }

    interface QueryMatch {
      pattern: number;
      captures: QueryCapture[];
    }

    interface PredicateResult {
      operator: string;
      operands: { name: string; type: string }[];
    }

    class Query {
      captureNames: string[];

      delete(): void;
      matches(node: SyntaxNode, startPosition?: Point, endPosition?: Point): QueryMatch[];
      captures(node: SyntaxNode, startPosition?: Point, endPosition?: Point): QueryCapture[];
      predicatesForPattern(patternIndex: number): PredicateResult[];
    }
  }

  export = Parser
}
