#include "rules.h"

using std::make_shared;
using std::string;
using std::set;
using std::vector;

namespace tree_sitter {
    namespace rules {
        rule_ptr blank() {
            return make_shared<Blank>();
        }
  
        char_ptr character(char value) {
            set<CharacterRange> ranges = { value };
            return make_shared<CharacterSet>(ranges);
        }

        char_ptr character(const set<CharacterRange> &ranges) {
            return make_shared<CharacterSet>(ranges);
        }

        char_ptr character(const set<CharacterRange> &ranges, bool sign) {
            return make_shared<CharacterSet>(ranges, sign);
        }

        rule_ptr choice(const vector<rule_ptr> &rules) {
            rule_ptr result;
            for (auto rule : rules)
                result = result.get() ? make_shared<Choice>(result, rule) : rule;
            return result;
        }
        
        rule_ptr pattern(const string &value) {
            return make_shared<Pattern>(value);
        }
        
        rule_ptr repeat(const rule_ptr content) {
            return std::make_shared<Repeat>(content);
        }
        
        rule_ptr seq(const vector<rule_ptr> &rules) {
            rule_ptr result = blank();
            for (auto rule : rules)
                result = (typeid(*result) != typeid(Blank)) ?
                    make_shared<Seq>(result, rule) :
                    rule;
            return result;
        }

        rule_ptr str(const string &value) {
            return make_shared<String>(value);
        }

        sym_ptr sym(const string &name) {
            return make_shared<Symbol>(name, false);
        }

        rule_ptr aux_sym(const string &name) {
            return make_shared<Symbol>(name, true);
        }
    }
}
