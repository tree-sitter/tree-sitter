declare module 'web-tree-sitter' {
  class Parser {
    static init(): Promise<void>;
    delete(): void;
    parse(input: string | Parser.Input, previousTree?: Parser.Tree): Parser.Tree;
    getLanguage(): any;
    setLanguage(language: any): void;
    getLogger(): Parser.Logger;
    setLogger(logFunc: Parser.Logger): void;
  }

  namespace Parser {
    export type Point = {
      row: number;
      column: number;
    };

    export type Range = {
      start: Point;
      end: Point;
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
      params: {[param: string]: string},
      type: "parse" | "lex"
    ) => void;

    export interface Input {
      seek(index: number): void;
      read(): any;
    }

    export interface SyntaxNode {
      tree: Tree;
      type: string;
      isNamed: boolean;
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
      toString(): string;
      child(index: number): SyntaxNode | null;
      namedChild(index: number): SyntaxNode | null;

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
    namespace Language {
        function load(url: string): Promise<any>
    }
  }

  export = Parser
}
