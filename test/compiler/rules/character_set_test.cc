#include "test_helper.h"
#include "compiler/rule.h"

using namespace rules;

START_TEST

describe("CharacterSet", []() {
  describe("equality", [&]() {
    it("returns true for identical character sets", [&]() {
      CharacterSet set1 = CharacterSet()
        .include('a', 'd')
        .include('f', 'm');

      CharacterSet set2 = CharacterSet()
        .include('a', 'd')
        .include('f', 'm');

      AssertThat(set1, Equals(set2));
    });

    it("returns false for character sets that include different ranges", [&]() {
      CharacterSet set1 = CharacterSet()
        .include('a', 'd')
        .include('f', 'm');

      CharacterSet set2 = CharacterSet()
        .include('a', 'c')
        .include('f', 'm');

      AssertThat(set1, !Equals(set2));
      AssertThat(set2, !Equals(set1));
    });

    it("returns false for character sets that exclude different ranges", [&]() {
      CharacterSet set1 = CharacterSet()
        .include_all()
        .exclude('a', 'd')
        .exclude('f', 'm');

      CharacterSet set2 = CharacterSet()
        .include_all()
        .exclude('a', 'c')
        .exclude('f', 'm');

      AssertThat(set1, !Equals(set2));
      AssertThat(set2, !Equals(set1));
    });

    it("returns false for character sets with different sign", [&]() {
      CharacterSet set1 = CharacterSet().include_all();
      CharacterSet set2 = CharacterSet();

      AssertThat(set1, !Equals(set2));
      AssertThat(set2, !Equals(set1));
    });
  });

  describe("hashing", [&]() {
    it("returns the same number for identical character sets", [&]() {
      CharacterSet set1 = CharacterSet()
        .include('a', 'd')
        .include('f', 'm');

      CharacterSet set2 = CharacterSet()
        .include('a', 'd')
        .include('f', 'm');

      AssertThat(hash<CharacterSet>()(set1), Equals(hash<CharacterSet>()(set2)));
    });

    it("returns different numbers for character sets that include different ranges", [&]() {
      CharacterSet set1 = CharacterSet()
        .include('a', 'd')
        .include('f', 'm');

      CharacterSet set2 = CharacterSet()
        .include('a', 'c')
        .include('f', 'm');

      AssertThat(hash<CharacterSet>()(set1), !Equals(hash<CharacterSet>()(set2)));
      AssertThat(hash<CharacterSet>()(set2), !Equals(hash<CharacterSet>()(set1)));
    });

    it("returns different numbers for character sets that exclude different ranges", [&]() {
      CharacterSet set1 = CharacterSet()
        .include_all()
        .exclude('a', 'd')
        .exclude('f', 'm');

      CharacterSet set2 = CharacterSet()
        .include_all()
        .exclude('a', 'c')
        .exclude('f', 'm');

      AssertThat(hash<CharacterSet>()(set1), !Equals(hash<CharacterSet>()(set2)));
      AssertThat(hash<CharacterSet>()(set2), !Equals(hash<CharacterSet>()(set1)));
    });

    it("returns different numbers for character sets with different sign", [&]() {
      CharacterSet set1 = CharacterSet().include_all();
      CharacterSet set2 = CharacterSet();

      AssertThat(hash<CharacterSet>()(set1), !Equals(hash<CharacterSet>()(set2)));
      AssertThat(hash<CharacterSet>()(set2), !Equals(hash<CharacterSet>()(set1)));
    });
  });

  describe("::is_empty", [&]() {
    it("returns true for empty character sets", [&]() {
      AssertThat(CharacterSet().is_empty(), Equals(true));
    });

    it("returns false for full character sets", [&]() {
      AssertThat(CharacterSet().include_all().is_empty(), Equals(false));
    });

    it("returns false for character sets that include some characters", [&]() {
      AssertThat(CharacterSet().include('x').is_empty(), Equals(false));
    });
  });

  describe("::include", [&]() {
    describe("when the set has a whitelist of characters", [&]() {
      it("adds included characters", [&]() {
        CharacterSet set1 = CharacterSet().include('a', 'd');
        AssertThat(set1, Equals(CharacterSet()
          .include('a')
          .include('b')
          .include('c')
          .include('d')));
      });
    });

    describe("when the set has a blacklist of characters", [&]() {
      it("removes excluded characters", [&]() {
        CharacterSet set1 = CharacterSet()
          .include_all()
          .exclude('a', 'g')
          .include('c', 'e');

        AssertThat(set1, Equals(CharacterSet()
          .include_all()
          .exclude('a')
          .exclude('b')
          .exclude('f')
          .exclude('g')));
      });

      it("does nothing if the character are already not excluded", [&]() {
        CharacterSet set1 = CharacterSet()
          .include_all()
          .include('a', 'c');

        AssertThat(set1, Equals(CharacterSet().include_all()));
      });
    });
  });

  describe("::exclude", [&]() {
    describe("when the set has a whitelist of characters", [&]() {
      it("removes included characters", [&]() {
        CharacterSet set1 = CharacterSet()
          .include('a', 'g')
          .exclude('c', 'e');

        AssertThat(set1, Equals(CharacterSet()
          .include('a')
          .include('b')
          .include('f')
          .include('g')));
      });

      it("does nothing if the character's are already not included", [&]() {
        CharacterSet set1 = CharacterSet().exclude('a', 'c');
        AssertThat(set1, Equals(CharacterSet()));
      });
    });

    describe("when the set has a blacklist of characters", [&]() {
      it("removes excluded characters", [&]() {
        CharacterSet set1 = CharacterSet()
          .include_all()
          .exclude('a', 'd');

        AssertThat(set1, Equals(CharacterSet()
          .include_all()
          .exclude('a')
          .exclude('b')
          .exclude('c')
          .exclude('d')));
      });
    });
  });

  describe("::remove_set", []() {
    CharacterSet intersection;

    describe("for a set with whitelisted characters", [&]() {
      describe("when the subtractend has whitelisted characters", [&]() {
        it("removes the included characters that the other set also includes", [&]() {
          CharacterSet set1 = CharacterSet().include('a', 'z');
          set1.remove_set(CharacterSet().include('d', 's'));
          AssertThat(set1, Equals(CharacterSet()
            .include('a', 'c')
            .include('t', 'z')));
        });

        it("returns the characters that were removed", [&]() {
          CharacterSet set1 = CharacterSet().include('a', 'z');
          intersection = set1.remove_set(CharacterSet().include('d', 's'));
          AssertThat(intersection, Equals(CharacterSet()
            .include('d', 's')));
        });

        it("returns the empty set when the sets are disjoint", [&]() {
          CharacterSet set1 = CharacterSet().include('a', 'z');
          intersection = set1.remove_set(CharacterSet().include('A', 'Z'));
          AssertThat(set1, Equals(CharacterSet().include('a', 'z')));
          AssertThat(intersection, Equals(CharacterSet()));
        });
      });

      describe("when the subtractend has blacklisted characters", [&]() {
        it("removes the included characters that are not excluded by the other set", [&]() {
          CharacterSet set1 = CharacterSet().include('a', 'f');

          intersection = set1.remove_set(CharacterSet()
            .include_all()
            .exclude('d', 'z'));

          AssertThat(set1, Equals(CharacterSet()
            .include('d', 'f')));
          AssertThat(intersection, Equals(CharacterSet()
            .include('a', 'c')));
        });
      });
    });

    describe("for a set with blacklisted characters", [&]() {
      describe("when the subtractend has whitelisted characters", [&]() {
        it("adds the subtractend's inclusions to the receiver's exclusions", [&]() {
          CharacterSet set1 = CharacterSet()
            .include_all()
            .exclude('a', 'f');

          intersection = set1.remove_set(CharacterSet()
            .include('x', 'z'));

          AssertThat(set1, Equals(CharacterSet()
            .include_all()
            .exclude('a', 'f')
            .exclude('x', 'z')));

          AssertThat(intersection, Equals(CharacterSet().include('x', 'z')));
        });
      });

      describe("when the subtractend has blacklisted characters", [&]() {
        it("includes only the characters excluded by the subtractend but not by the receiver", [&]() {
          CharacterSet set1 = CharacterSet()
            .include_all()
            .exclude('a', 'm');

          set1.remove_set(CharacterSet()
            .include_all()
            .exclude('d', 'z'));

          AssertThat(set1, Equals(CharacterSet()
            .include('n', 'z')));
        });

        it("returns the characters excluded by neither set", [&]() {
          CharacterSet set1 = CharacterSet()
            .include_all()
            .exclude('a', 'm');

          intersection = set1.remove_set(CharacterSet()
            .include_all()
            .exclude('d', 'z'));

          AssertThat(intersection, Equals(CharacterSet()
            .include_all()
            .exclude('a', 'z')));
        });

        it("works when the sets are disjoint", [&]() {
          CharacterSet set1 = CharacterSet()
            .include_all()
            .exclude('a', 'm');

          intersection = set1.remove_set(CharacterSet()
            .include_all()
            .exclude('d', 'z'));

          AssertThat(set1, Equals(CharacterSet()
            .include('n', 'z')));

          AssertThat(intersection, Equals(CharacterSet()
            .include_all()
            .exclude('a', 'z')));
        });
      });
    });
  });

  describe("::included_ranges", [&]() {
    it("consolidates sequences of 3 or more consecutive characters into ranges", [&]() {
      CharacterSet set1 = CharacterSet()
        .include('a', 'c')
        .include('g')
        .include('z');

      AssertThat(set1.included_ranges(), Equals(vector<CharacterRange>({
        CharacterRange{'a', 'c'},
        CharacterRange('g'),
        CharacterRange('z'),
      })));
    });

    it("doesn't consolidate sequences of 2 consecutive characters", [&]() {
      CharacterSet set1 = CharacterSet()
        .include('a', 'b')
        .include('g')
        .include('z');

      AssertThat(set1.included_ranges(), Equals(vector<CharacterRange>({
        CharacterRange('a'),
        CharacterRange('b'),
        CharacterRange('g'),
        CharacterRange('z'),
      })));
    });
  });
});

END_TEST
