type Rule =
  | string
  | RegExp
  | {
      /** @internal */
      _ruleBrand: never;
    };

interface BaseGrammar<Keys extends string> {
  name: string;

  extras?: ($: Record<Keys, Rule>) => Rule[];

  externals?: ($: Record<Keys, Rule>) => Rule[];

  conflicts?: ($: Record<Keys, Rule>) => Rule[][];

  inline?: ($: Record<Keys, Rule>) => Rule[];

  rules: Record<Keys, ($: Record<Keys, Rule>) => Rule>;
}

declare function blank(): Rule;
declare function field(name: string, rule: Rule): Rule;
declare function choice(...elements: Rule[]): Rule;
declare function optional(rule: Rule): Rule;
declare function prec(precedence: number, rule: Rule): Rule;
declare namespace prec {
  function left(precedence: number, rule: Rule): Rule;
  function right(precedence: number, rule: Rule): Rule;
  function dynamic(precedence: number, rule: Rule): Rule;
}
declare function repeat(rule: Rule): Rule;
declare function repeat1(rule: Rule): Rule;
declare function seq(...elements: Rule[]): Rule;
declare function sym(name: string): Rule;
declare function token(value: string | RegExp): Rule;
declare namespace token {
  function immediate(value: string | RegExp): Rule;
}

declare function grammar<T extends string>(
  baseGrammar: BaseGrammar<T>
): any;
