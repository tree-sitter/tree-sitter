declare module 'web-tree-sitter' {
  class Parser {
    static init(): Promise<void>;
    delete(): void;
    parse(input: string | Parser.Input, previousTree?: Parser.Tree, options?: Parser.Options): Parser.Tree;
    getLanguage(): any;
    setLanguage(language: any): void;
    getLogger(): Parser.Logger;
    setLogger(logFunc: Parser.Logger): void;
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
      text: string;
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

      descendantForIndex(index: number): SyntaxNode;
      descendantForIndex(startIndex: number, endIndex: number): SyntaxNode;
      descendantsOfType(type: string | Array<string>, startPosition?: Point, endPosition?: Point): Array<SyntaxNode>;
      namedDescendantForIndex(index: number): SyntaxNode;
      namedDescendantForIndex(startIndex: number, endIndex: number): SyntaxNode;
      descendantForPosition(position: Point): SyntaxNode;
      descendantForPosition(startPosition: Point, endPosition: Point): SyntaxNode;
      namedDescendantForPosition(position: Point): SyntaxNode;
      namedDescendantForPosition(startPosition: Point, endPosition: Point): SyntaxNode;

      walk(): TreeCursor;
    }

    export interface TreeCursor {
      nodeType: string;
      nodeText: string;
      nodeIsNamed: boolean;
      startPosition: Point;
      endPosition: Point;
      startIndex: number;
      endIndex: number;

      reset(node: SyntaxNode): void;
      delete(): void;
      currentNode(): SyntaxNode;
      currentFieldId(): number;
      currentFieldName(): string;
      gotoParent(): boolean;
      gotoFirstChild(): boolean;
      gotoFirstChildForIndex(index: number): boolean;
      gotoNextSibling(): boolean;
    }

    export interface Tree {
      readonly rootNode: SyntaxNode;

      copy(): Tree;
      delete(): void;
      edit(delta: Edit): Tree;
      walk(): TreeCursor;
      getChangedRanges(other: Tree): Range[];
      getEditedRange(other: Tree): Range;
      getLanguage(): any;
    }

    class Language {
      static load(input: string | Uint8Array): Promise<Language>;

      readonly version: number;
      readonly fieldCount: number;
      readonly nodeTypeCount: number;

      fieldNameForId(fieldId: number): string | null;
      fieldIdForName(fieldName: string): number | null;
      idForNodeType(type: string, named: boolean): number;
      nodeTypeForId(typeId: number): string | null;
      nodeTypeIsNamed(typeId: number): boolean;
      nodeTypeIsVisible(typeId: number): boolean;
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

      delete(): void;
      matches(node: SyntaxNode, startPosition?: Point, endPosition?: Point): QueryMatch[];
      captures(node: SyntaxNode, startPosition?: Point, endPosition?: Point): QueryCapture[];
      predicatesForPattern(patternIndex: number): PredicateResult[];
    }
  }

  export = Parser
}
