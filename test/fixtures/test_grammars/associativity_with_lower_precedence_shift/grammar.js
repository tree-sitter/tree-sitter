module.exports = grammar({
    name: 'associativity_with_lower_precedence_shift',
  
    rules: {
      expression: $ => choice(
        $.addition,
        $.superaddition,    // comment out this line to make test pass
        $.number
      ),
      addition: $ => prec.right(1, seq($.expression, "+", $.expression)),
      superaddition: $ => prec.right(seq($.expression, "+", "+", $.expression)),
      number: $ => "1"
    }
  });
  