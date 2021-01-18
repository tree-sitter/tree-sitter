declare module 'web-tree-sitter' {
  class Parser {
    static init(): Promise<void>;
    delete();
    parse(input: string | Parser.Input, previousTree?: Parser.Tree, options?: Parser.Options): Parser.Tree | null;
    getLanguage(): Parser.Language | null;
    setLanguage(language?: Parser.Language): void;
    getLogger(): Parser.Logger | null;
    setLogger(logFunc?: Parser.Logger): void;
    reset(): void;
    getTimeoutMicros(): number;
    setTimeoutMicros(timeout: number);
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
      startPosition: Point;
      endPosition: Point;
      startIndex: number;
      endIndex: number;
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
      id: number;
      tree: Tree;
      type: string;
      typeId: number;
      text: string;
      startPosition: Point;
      endPosition: Point;
      startIndex: number;
      endIndex: number;
      parent: SyntaxNode | null;
      children: SyntaxNode[];
      namedChildren: SyntaxNode[];
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

      hasChanges(): boolean;
      hasError(): boolean;
      equals(other: SyntaxNode): boolean;
      isMissing(): boolean;
      isNamed(): boolean;
      toString(): string;
      child(index: number): SyntaxNode | null;
      namedChild(index: number): SyntaxNode | null;
      childForFieldId(fieldId: number): SyntaxNode | null;
      childForFieldName(fieldName: string): SyntaxNode | null;

      descendantForIndex(index: number): SyntaxNode | null;
      descendantForIndex(startIndex: number, endIndex: number): SyntaxNode | null;
      descendantsOfType(type: string | string[], startPosition?: Point, endPosition?: Point): SyntaxNode[];
      namedDescendantForIndex(index: number): SyntaxNode | null;
      namedDescendantForIndex(startIndex: number, endIndex: number): SyntaxNode | null;
      descendantForPosition(position: Point): SyntaxNode | null;
      descendantForPosition(startPosition: Point, endPosition: Point): SyntaxNode | null;
      namedDescendantForPosition(position: Point): SyntaxNode | null;
      namedDescendantForPosition(startPosition: Point, endPosition: Point): SyntaxNode | null;

      walk(): TreeCursor;
    }

    export interface TreeCursor {
      nodeType: string;
      nodeText: string;
      nodeIsMissing: boolean;
      nodeIsNamed: boolean;
      startPosition: Point;
      endPosition: Point;
      startIndex: number;
      endIndex: number;

      reset(node: SyntaxNode);
      delete();
      currentNode(): SyntaxNode;
      currentFieldId(): number | null;
      currentFieldName(): string | null;
      gotoParent(): boolean;
      gotoFirstChild(): boolean;
      gotoNextSibling(): boolean;
    }

    export interface Tree {
      readonly rootNode: SyntaxNode;

      copy(): Tree;
      delete();
      edit(delta: Edit): Tree;
      walk(): TreeCursor;
      getChangedRanges(other: Tree): Range[];
      getLanguage(): Language;
    }

    class Language {
      static load(input: string | Uint8Array): Promise<Language>;

      readonly version: number;
      readonly fieldCount: number;

      fieldNameForId(fieldId: number): string | null;
      fieldIdForName(fieldName: string): number | null;
      query(source: string): Query;
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

      delete();
      matches(node: SyntaxNode, startPosition?: Point, endPosition?: Point): QueryMatch[];
      captures(node: SyntaxNode, startPosition?: Point, endPosition?: Point): QueryCapture[];
      predicatesForPattern(patternIndex: number): PredicateResult[];
    }
  }

  export = Parser
}
