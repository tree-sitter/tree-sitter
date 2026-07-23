export default grammar({
    name: 'associativity_left_with_lower_precedence_shift',

    rules: {
        expression: $ => choice(
            $.addition,
            $.superaddition,
            $.number,
        ),

        addition: $ => prec.left(1, seq($.expression, '+', $.expression)),
        superaddition: $ => prec.right(seq($.expression, '+', '+', $.expression)),

        number: _ => '1',
    }
});
