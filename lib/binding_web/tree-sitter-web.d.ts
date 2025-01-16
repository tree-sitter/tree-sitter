declare module "web-tree-sitter" {
  class Parser {
    /**
     *
     * @param moduleOptions Optional emscripten module-object, see https://emscripten.org/docs/api_reference/module.html
     */
    static init(moduleOptions?: object): Promise<void>;
    delete(): void;
    parse(
      input: string | Parser.Input,
      oldTree?: Parser.Tree | null,
      options?: Parser.Options,
    ): Parser.Tree;
    getIncludedRanges(): Parser.Range[];
    getTimeoutMicros(): number;
    setTimeoutMicros(timeout: number): void;
    reset(): void;
    getLanguage(): Parser.Language;
    setLanguage(language?: Parser.Language | null): void;
    getLogger(): Parser.Logger;
    setLogger(logFunc?: Parser.Logger | false | null): void;
  }

  namespace Parser {
    export interface Options {
      includedRanges?: Range[];
      progressCallback?: (state: Parser.State) => boolean;
    }

    export interface State {
      currentOffset: number;
    }

    export interface Point {
      row: number;
      column: number;
    }

    export interface Range {
      startIndex: number;
      endIndex: number;
      startPosition: Point;
      endPosition: Point;
    }

    export interface Edit {
      startIndex: number;
      oldEndIndex: number;
      newEndIndex: number;
      startPosition: Point;
      oldEndPosition: Point;
      newEndPosition: Point;
    }

    export type Logger = (
      message: string,
      params: Record<string, string>,
      type: "parse" | "lex",
    ) => void;

    export type Input = (index: number, position?: Point) => string | null | undefined;

    export interface SyntaxNode {
      tree: Tree;
      id: number;
      typeId: number;
      grammarId: number;
      type: string;
      grammarType: string;
      isNamed: boolean;
      isMissing: boolean;
      isExtra: boolean;
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
      descendantCount: number;

      equals(other: SyntaxNode): boolean;
      toString(): string;
      child(index: number): SyntaxNode | null;
      namedChild(index: number): SyntaxNode | null;
      childForFieldName(fieldName: string): SyntaxNode | null;
      childForFieldId(fieldId: number): SyntaxNode | null;
      fieldNameForChild(childIndex: number): string | null;
      fieldNameForNamedChild(childIndex: number): string | null;
      childrenForFieldName(fieldName: string): SyntaxNode[];
      childrenForFieldId(fieldId: number): SyntaxNode[];
      firstChildForIndex(index: number): SyntaxNode | null;
      firstNamedChildForIndex(index: number): SyntaxNode | null;

      descendantForIndex(...args: [index: number] | [startIndex: number, endIndex: number]): SyntaxNode;
      namedDescendantForIndex(...args: [index: number] | [startIndex: number, endIndex: number]): SyntaxNode;
      descendantForPosition(...args: [position: Point] | [startPosition: Point, endPosition: Point]): SyntaxNode;
      namedDescendantForPosition(...args: [position: Point] | [startPosition: Point, endPosition: Point]): SyntaxNode;
      descendantsOfType(
        types: string | string[],
        startPosition?: Point,
        endPosition?: Point,
      ): SyntaxNode[];

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
      readonly currentFieldName: string;
      readonly currentFieldId: number;
      readonly currentDepth: number;
      readonly currentDescendantIndex: number;

      copy(): TreeCursor;
      reset(node: SyntaxNode): void;
      resetTo(cursor: TreeCursor): void;
      delete(): void;
      gotoParent(): boolean;
      gotoFirstChild(): boolean;
      gotoLastChild(): boolean;
      gotoFirstChildForIndex(goalIndex: number): boolean;
      gotoFirstChildForPosition(goalPosition: Point): boolean;
      gotoNextSibling(): boolean;
      gotoPreviousSibling(): boolean;
      gotoDescendant(goalDescendantIndex: number): void;
    }

    export interface Tree {
      readonly rootNode: SyntaxNode;

      rootNodeWithOffset(offsetBytes: number, offsetExtent: Point): SyntaxNode;
      copy(): Tree;
      delete(): void;
      edit(edit: Edit): void;
      walk(): TreeCursor;
      getChangedRanges(other: Tree): Range[];
      getIncludedRanges(): Range[];
      getLanguage(): Language;
    }

    export type Properties = Record<string, string | null>;

    export interface QueryCapture {
      name: string;
      text?: string;
      node: SyntaxNode;
      setProperties?: Properties;
      assertedProperties?: Properties;
      refutedProperties?: Properties;
    }

    export interface QueryMatch {
      pattern: number;
      captures: QueryCapture[];
    }

    export interface QueryState {
      currentOffset: number;
    }

    export interface QueryOptions {
      startPosition?: Point;
      endPosition?: Point;
      startIndex?: number;
      endIndex?: number;
      matchLimit?: number;
      maxStartDepth?: number;
      timeoutMicros?: number;
      progressCallback?: (state: QueryState) => boolean;
    }

    export interface Predicate {
      operator: string;
      operands: PredicateStep[];
    }

    type PredicateStep =
      | { type: 'string'; value: string }
      | { type: 'capture'; name: string };


    export interface PredicateResult {
      operator: string;
      operands: { name: string; type: string }[];
    }

    export const CaptureQuantifier = {
      Zero: 0,
      ZeroOrOne: 1,
      ZeroOrMore: 2,
      One: 3,
      OneOrMore: 4
    } as const;

    export type CaptureQuantifier = typeof CaptureQuantifier[keyof typeof CaptureQuantifier];

    export class Query {
      readonly captureNames: string[];
      readonly captureQuantifiers: CaptureQuantifier[][];
      readonly predicates: Predicate[][];
      readonly setProperties: Properties[];
      readonly assertedProperties: Properties[];
      readonly refutedProperties: Properties[];
      readonly matchLimit?: number;

      delete(): void;
      captures(node: SyntaxNode, options?: QueryOptions): QueryCapture[];
      matches(node: SyntaxNode, options?: QueryOptions): QueryMatch[];
      predicatesForPattern(patternIndex: number): PredicateResult[];
      disableCapture(captureName: string): void;
      disablePattern(patternIndex: number): void;
      isPatternGuaranteedAtStep(byteOffset: number): boolean;
      isPatternRooted(patternIndex: number): boolean;
      isPatternNonLocal(patternIndex: number): boolean;
      startIndexForPattern(patternIndex: number): number;
      endIndexForPattern(patternIndex: number): number;
      didExceedMatchLimit(): boolean;
    }

    class Language {
      static load(input: string | Uint8Array): Promise<Language>;

      readonly name: string | null;
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
      get supertypes(): number[];
      subtypes(supertype: number): number[];
      nextState(stateId: number, typeId: number): number;
      query(source: string): Query;
      lookaheadIterator(stateId: number): LookaheadIterable | null;
    }

    export class LookaheadIterable {
      readonly language: Language;
      readonly currentTypeId: number;
      readonly currentType: string;

      delete(): void;
      reset(language: Language, stateId: number): boolean;
      resetState(stateId: number): boolean;
      [Symbol.iterator](): Iterator<string>;
    }
  }

  export = Parser;
}
