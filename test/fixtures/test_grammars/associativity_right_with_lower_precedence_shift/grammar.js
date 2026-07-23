module.exports = grammar({
    name: 'associativity_right_with_lower_precedence_shift',
  
    rules: {
      expression: $ => choice(
        $.addition,
        $.superaddition,
        $.number
      ),
      addition: $ => prec.right(1, seq($.expression, "+", $.expression)),
      superaddition: $ => prec.right(seq($.expression, "+", "+", $.expression)),
      number: _ => "1"
    }
  });
  
