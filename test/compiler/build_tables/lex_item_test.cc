#include "test_helper.h"
#include "compiler/build_tables/lex_item.h"
#include "compiler/rule.h"
#include "helpers/stream_methods.h"

using namespace rules;
using namespace build_tables;
typedef LexItemSet::Transition Transition;

START_TEST

describe("LexItem", []() {
  describe("completion_status()", [&]() {
    it("indicates whether the item is done and its precedence", [&]() {
      LexItem item1(Symbol::terminal(0), CharacterSet({'a', 'b', 'c'}));
      AssertThat(item1.completion_status().is_done, IsFalse());
      AssertThat(item1.completion_status().precedence, Equals(PrecedenceRange()));

      MetadataParams params;
      params.precedence = 3;
      params.has_precedence = true;
      params.is_string = 1;
      LexItem item2(Symbol::terminal(0), Choice{{
        Metadata{Blank{}, params},
        CharacterSet({'a', 'b', 'c'}),
      }});

      AssertThat(item2.completion_status().is_done, IsTrue());
      AssertThat(item2.completion_status().precedence, Equals(PrecedenceRange(3)));

      LexItem item3(Symbol::terminal(0), Choice{{
        Blank{},
        Repeat{CharacterSet({' ', '\t'})},
      }});
      AssertThat(item3.completion_status().is_done, IsTrue());
      AssertThat(item3.completion_status().precedence, Equals(PrecedenceRange()));
    });
  });
});

describe("LexItemSet::transitions()", [&]() {
  it("handles single characters", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), CharacterSet({'x'})),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet{{'x'}},
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Blank{}),
            }),
            PrecedenceRange(),
            false
          }
        }
      })));
  });

  it("marks transitions that are within the main token (as opposed to separators)", [&]() {
    MetadataParams params;
    params.is_main_token = true;

    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Metadata{CharacterSet{{'x'}}, params}),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'x'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata{Blank{}, params}),
            }),
            PrecedenceRange(),
            true
          }
        }
      })));
  });

  it("handles sequences", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Rule::seq({
        CharacterSet({'w'}),
        CharacterSet({'x'}),
        CharacterSet({'y'}),
        CharacterSet({'z'}),
      })),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'w'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Rule::seq({
                CharacterSet({'x'}),
                CharacterSet({'y'}),
                CharacterSet({'z'}),
              })),
            }),
            PrecedenceRange(),
            false
          }
        }
      })));
  });

  it("handles sequences with nested precedence", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Rule::seq({
        Metadata::prec(3, Rule::seq({
          CharacterSet({'v'}),
          Metadata::prec(4, Rule::seq({
            CharacterSet({'w'}),
            CharacterSet({'x'}) })),
          CharacterSet({'y'}) })),
        CharacterSet({'z'}),
      })),
    });

    auto transitions = item_set.transitions();

    AssertThat(
      transitions,
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'v'}),
          Transition{
            // The outer precedence is now 'active', because we are within its
            // contained rule.
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Rule::seq({
                Metadata::active_prec(3, Rule::seq({
                  Metadata::prec(4, Rule::seq({
                    CharacterSet({'w'}),
                    CharacterSet({'x'})
                  })),
                  CharacterSet({'y'})
                })),
                CharacterSet({'z'}),
              })),
            }),

            // No precedence is applied upon entering a rule.
            PrecedenceRange(),
            false
          }
        }
      })));

    LexItemSet item_set2 = transitions[CharacterSet({'v'})].destination;
    transitions = item_set2.transitions();

    AssertThat(
      transitions,
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'w'}),
          Transition{
            // The inner precedence is now 'active'
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Rule::seq({
                Metadata::active_prec(3, Rule::seq({
                  Metadata::active_prec(4, CharacterSet{{'x'}}),
                  CharacterSet{{'y'}}
                })),
                CharacterSet{{'z'}},
              })),
            }),

            // The outer precedence is applied.
            PrecedenceRange(3),
            false
          }
        }
      })));

    LexItemSet item_set3 = transitions[CharacterSet({'w'})].destination;
    transitions = item_set3.transitions();

    AssertThat(
      transitions,
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'x'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Rule::seq({
                Metadata::active_prec(3, CharacterSet{{'y'}}),
                CharacterSet{{'z'}},
              })),
            }),

            // The inner precedence is applied.
            PrecedenceRange(4),
            false
          }
        }
      })));

    LexItemSet item_set4 = transitions[CharacterSet({'x'})].destination;
    transitions = item_set4.transitions();

    AssertThat(
      transitions,
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'y'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet({'z'})),
            }),
            PrecedenceRange(3),
            false
          }
        }
      })));
  });

  it("handles sequences where the left hand side can be blank", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Rule::seq({
        Rule::choice({
          CharacterSet({'x'}),
          Blank{},
        }),
        CharacterSet({'y'}),
        CharacterSet({'z'}),
      })),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'x'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Rule::seq({
                CharacterSet({'y'}),
                CharacterSet({'z'}),
              })),
            }),
            PrecedenceRange(),
            false
          }
        },
        {
          CharacterSet({'y'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet({'z'})),
            }),
            PrecedenceRange(),
            false
          }
        }
      })));
  });

  it("handles blanks", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Blank{}),
    });

    AssertThat(item_set.transitions(), IsEmpty());
  });

  it("handles repeats", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Repeat{Rule::seq({
        CharacterSet({'a'}),
        CharacterSet({'b'}),
      })}),
      LexItem(Symbol::non_terminal(2), Repeat{CharacterSet{{'c'}}}),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'a'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Rule::seq({
                CharacterSet({'b'}),
                Repeat{Rule::seq({
                  CharacterSet({'a'}),
                  CharacterSet({'b'}),
                })}
              })),
              LexItem(Symbol::non_terminal(1), CharacterSet({'b'})),
            }),
            PrecedenceRange(),
            false
          }
        },
        {
          CharacterSet({'c'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(2), Repeat{CharacterSet({'c'})}),
              LexItem(Symbol::non_terminal(2), Blank{}),
            }),
            PrecedenceRange(),
            false
          }
        }
      })));
  });

  it("handles repeats with precedence", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Metadata::active_prec(-1, Repeat{CharacterSet({'a'})}))
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'a'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(-1, Repeat{CharacterSet({'a'})})),
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(-1, Blank{})),
            }),
            PrecedenceRange(-1),
            false
          }
        }
      })));
  });

  it("handles choices between overlapping character sets", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Rule::choice({
        Metadata::active_prec(2, Rule::seq({
          CharacterSet({'a', 'b', 'c', 'd'}),
          CharacterSet({'x'}),
        })),
        Metadata::active_prec(3, Rule::seq({
          CharacterSet({'c', 'd', 'e', 'f'}),
          CharacterSet({'y'}),
        })),
      }))
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'a', 'b'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(2, CharacterSet({'x'}))),
            }),
            PrecedenceRange(2),
            false
          }
        },
        {
          CharacterSet({'c', 'd'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(2, CharacterSet({'x'}))),
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(3, CharacterSet({'y'}))),
            }),
            PrecedenceRange(2, 3),
            false
          }
        },
        {
          CharacterSet({'e', 'f'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(3, CharacterSet({'y'}))),
            }),
            PrecedenceRange(3),
            false
          }
        },
      })));
  });

  it("handles choices between a subset and a superset of characters", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Rule::choice({
        Rule::seq({
          CharacterSet({'b', 'c', 'd'}),
          CharacterSet({'x'}),
        }),
        Rule::seq({
          CharacterSet({'a', 'b', 'c', 'd', 'e', 'f'}),
          CharacterSet({'y'}),
        }),
      })),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet({'a', 'e', 'f'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet({'y'})),
            }),
            PrecedenceRange(),
            false
          }
        },
        {
          CharacterSet({'b', 'c', 'd'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet({'x'})),
              LexItem(Symbol::non_terminal(1), CharacterSet({'y'})),
            }),
            PrecedenceRange(),
            false
          }
        },
      })));
  });

  it("handles choices between whitelisted and blacklisted character sets", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Rule::seq({
        Rule::choice({
          CharacterSet().include_all().exclude('/'),
          Rule::seq({
            CharacterSet({'\\'}),
            CharacterSet({'/'}),
          }),
        }),
        CharacterSet({'/'}),
      }))
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include_all().exclude('/').exclude('\\'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet({'/'})),
            }),
            PrecedenceRange(),
            false
          }
        },
        {
          CharacterSet({'\\'}),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet({'/'})),
              LexItem(Symbol::non_terminal(1), Rule::seq({CharacterSet({'/'}), CharacterSet({'/'})})),
            }),
            PrecedenceRange(),
            false
          }
        },
      })));
  });

  it("handles different items with overlapping character sets", [&]() {
    LexItemSet set1({
      LexItem(Symbol::non_terminal(1), CharacterSet({'a', 'b', 'c', 'd', 'e', 'f'})),
      LexItem(Symbol::non_terminal(2), CharacterSet({'e', 'f', 'g', 'h', 'i'}))
    });

    AssertThat(set1.transitions(), Equals(LexItemSet::TransitionMap({
      {
        CharacterSet({'a', 'b', 'c', 'd'}),
        Transition{
          LexItemSet({
            LexItem(Symbol::non_terminal(1), Blank{}),
          }),
          PrecedenceRange(),
          false
        }
      },
      {
        CharacterSet({'e', 'f'}),
        Transition{
          LexItemSet({
            LexItem(Symbol::non_terminal(1), Blank{}),
            LexItem(Symbol::non_terminal(2), Blank{}),
          }),
          PrecedenceRange(),
          false
        }
      },
      {
        CharacterSet({'g', 'h', 'i'}),
        Transition{
          LexItemSet({
            LexItem(Symbol::non_terminal(2), Blank{}),
          }),
          PrecedenceRange(),
          false
        }
      },
    })));
  });
});

END_TEST
