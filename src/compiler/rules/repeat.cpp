#include "blank.h"
#include "seq.h"
#include "choice.h"
#include "repeat.h"
#include "transition_map.h"

namespace tree_sitter {
    namespace rules {
        Repeat::Repeat(const rule_ptr content) : content(content) {}
        
        rule_ptr repeat(const rule_ptr content) {
            return std::make_shared<Repeat>(content);
        }
        
        TransitionMap<Rule> Repeat::transitions() const {
            return content->transitions().map<Rule>([&](const rule_ptr &value) -> rule_ptr {
                return seq({ value, choice({ repeat(content), blank() }) });
            });
        }
        
        bool Repeat::operator==(const Rule &rule) const {
            const Repeat *other = dynamic_cast<const Repeat *>(&rule);
            return other && (*other->content == *content);
        }
        
        std::string Repeat::to_string() const {
            return std::string("(repeat ") + content->to_string() + ")";
        }
    }
}
