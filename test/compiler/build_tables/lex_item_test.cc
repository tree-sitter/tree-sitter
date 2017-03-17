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
        CharacterSet{{ 'a', 'b', 'c' }}
      }});

      AssertThat(item2.completion_status().is_done, IsTrue());
      AssertThat(item2.completion_status().precedence, Equals(PrecedenceRange(3)));

      LexItem item3(Symbol::terminal(0), Choice{{
        Blank{},
        Repeat{CharacterSet{{ ' ', '\t' }}},
      }});
      AssertThat(item3.completion_status().is_done, IsTrue());
      AssertThat(item3.completion_status().precedence, Equals(PrecedenceRange()));
    });
  });
});

describe("LexItemSet::transitions()", [&]() {
  it("handles single characters", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), CharacterSet{{ 'x' }}),
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
          CharacterSet().include('x'),
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
      LexItem(Symbol::non_terminal(1), Seq::build({
        CharacterSet{{ 'w' }},
        CharacterSet{{ 'x' }},
        CharacterSet{{ 'y' }},
        CharacterSet{{ 'z' }},
      })),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('w'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Seq::build({
                CharacterSet{{ 'x' }},
                CharacterSet{{ 'y' }},
                CharacterSet{{ 'z' }},
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
      LexItem(Symbol::non_terminal(1), Seq::build({
        Metadata::prec(3, Seq::build({
          CharacterSet{{ 'v' }},
          Metadata::prec(4, Seq::build({
            CharacterSet{{ 'w' }},
            CharacterSet{{ 'x' }} })),
          CharacterSet{{ 'y' }} })),
        CharacterSet{{ 'z' }},
      })),
    });

    auto transitions = item_set.transitions();

    AssertThat(
      transitions,
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('v'),
          Transition{
            // The outer precedence is now 'active', because we are within its
            // contained rule.
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Seq::build({
                Metadata::active_prec(3, Seq::build({
                  Metadata::prec(4, Seq::build({
                    CharacterSet{{ 'w' }},
                    CharacterSet{{ 'x' }}
                  })),
                  CharacterSet{{ 'y' }}
                })),
                CharacterSet{{ 'z' }},
              })),
            }),

            // No precedence is applied upon entering a rule.
            PrecedenceRange(),
            false
          }
        }
      })));

    LexItemSet item_set2 = transitions[CharacterSet().include('v')].destination;
    transitions = item_set2.transitions();

    AssertThat(
      transitions,
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('w'),
          Transition{
            // The inner precedence is now 'active'
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Seq::build({
                Metadata::active_prec(3, Seq::build({
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

    LexItemSet item_set3 = transitions[CharacterSet().include('w')].destination;
    transitions = item_set3.transitions();

    AssertThat(
      transitions,
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('x'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Seq::build({
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

    LexItemSet item_set4 = transitions[CharacterSet().include('x')].destination;
    transitions = item_set4.transitions();

    AssertThat(
      transitions,
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('y'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet{{ 'z' }}),
            }),
            PrecedenceRange(3),
            false
          }
        }
      })));
  });

  it("handles sequences where the left hand side can be blank", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Seq::build({
        Choice::build({
          CharacterSet{{ 'x' }},
          Blank{},
        }),
        CharacterSet{{ 'y' }},
        CharacterSet{{ 'z' }},
      })),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('x'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Seq::build({
                CharacterSet{{ 'y' }},
                CharacterSet{{ 'z' }},
              })),
            }),
            PrecedenceRange(),
            false
          }
        },
        {
          CharacterSet().include('y'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet{{ 'z' }}),
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
      LexItem(Symbol::non_terminal(1), Repeat{Seq::build({
        CharacterSet{{ 'a' }},
        CharacterSet{{ 'b' }},
      })}),
      LexItem(Symbol::non_terminal(2), Repeat{CharacterSet{{'c'}}}),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('a'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Seq::build({
                CharacterSet{{ 'b' }},
                Repeat{Seq::build({
                  CharacterSet{{ 'a' }},
                  CharacterSet{{ 'b' }},
                })}
              })),
              LexItem(Symbol::non_terminal(1), CharacterSet{{ 'b' }}),
            }),
            PrecedenceRange(),
            false
          }
        },
        {
          CharacterSet().include('c'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(2), Repeat{CharacterSet{{ 'c' }}}),
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
      LexItem(Symbol::non_terminal(1), Metadata::active_prec(-1, Repeat{CharacterSet{{ 'a' }}}))
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('a'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(-1, Repeat{CharacterSet{{ 'a' }}})),
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
      LexItem(Symbol::non_terminal(1), Choice::build({
        Metadata::active_prec(2, Seq::build({
          CharacterSet{{ 'a', 'b', 'c', 'd'  }},
          CharacterSet{{ 'x' }},
        })),
        Metadata::active_prec(3, Seq::build({
          CharacterSet{{ 'c', 'd', 'e', 'f' }},
          CharacterSet{{ 'y' }},
        })),
      }))
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('a', 'b'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(2, CharacterSet{{ 'x' }})),
            }),
            PrecedenceRange(2),
            false
          }
        },
        {
          CharacterSet().include('c', 'd'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(2, CharacterSet{{ 'x' }})),
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(3, CharacterSet{{ 'y' }})),
            }),
            PrecedenceRange(2, 3),
            false
          }
        },
        {
          CharacterSet().include('e', 'f'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), Metadata::active_prec(3, CharacterSet{{ 'y' }})),
            }),
            PrecedenceRange(3),
            false
          }
        },
      })));
  });

  it("handles choices between a subset and a superset of characters", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Choice::build({
        Seq::build({
          CharacterSet{{ 'b', 'c', 'd' }},
          CharacterSet{{ 'x' }},
        }),
        Seq::build({
          CharacterSet{{ 'a', 'b', 'c', 'd', 'e', 'f' }},
          CharacterSet{{ 'y' }},
        }),
      })),
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include('a').include('e', 'f'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet{{ 'y' }}),
            }),
            PrecedenceRange(),
            false
          }
        },
        {
          CharacterSet().include('b', 'd'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet{{ 'x' }}),
              LexItem(Symbol::non_terminal(1), CharacterSet{{ 'y' }}),
            }),
            PrecedenceRange(),
            false
          }
        },
      })));
  });

  it("handles choices between whitelisted and blacklisted character sets", [&]() {
    LexItemSet item_set({
      LexItem(Symbol::non_terminal(1), Seq::build({
        Choice::build({
          CharacterSet().include_all().exclude('/'),
          Seq::build({
            CharacterSet{{ '\\' }},
            CharacterSet{{ '/' }},
          }),
        }),
        CharacterSet{{ '/' }},
      }))
    });

    AssertThat(
      item_set.transitions(),
      Equals(LexItemSet::TransitionMap({
        {
          CharacterSet().include_all().exclude('/').exclude('\\'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet{{ '/' }}),
            }),
            PrecedenceRange(),
            false
          }
        },
        {
          CharacterSet().include('\\'),
          Transition{
            LexItemSet({
              LexItem(Symbol::non_terminal(1), CharacterSet{{ '/' }}),
              LexItem(Symbol::non_terminal(1), Seq::build({ CharacterSet{{ '/' }}, CharacterSet{{ '/' }} })),
            }),
            PrecedenceRange(),
            false
          }
        },
      })));
  });

  it("handles different items with overlapping character sets", [&]() {
    LexItemSet set1({
      LexItem(Symbol::non_terminal(1), CharacterSet{{ 'a', 'b', 'c', 'd', 'e', 'f' }}),
      LexItem(Symbol::non_terminal(2), CharacterSet{{ 'e', 'f', 'g', 'h', 'i' }})
    });

    AssertThat(set1.transitions(), Equals(LexItemSet::TransitionMap({
      {
        CharacterSet().include('a', 'd'),
        Transition{
          LexItemSet({
            LexItem(Symbol::non_terminal(1), Blank{}),
          }),
          PrecedenceRange(),
          false
        }
      },
      {
        CharacterSet().include('e', 'f'),
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
        CharacterSet().include('g', 'i'),
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
