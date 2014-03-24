#ifndef TREE_SITTER_COMPILER_H_
#define TREE_SITTER_COMPILER_H_

#include <vector>
#include <string>
#include <memory>

namespace tree_sitter {
    namespace rules {
        class Rule;
        typedef std::shared_ptr<Rule> rule_ptr;

        std::ostream& operator<<(std::ostream& stream, const rule_ptr &rule);

        rule_ptr blank();
        rule_ptr choice(const std::vector<rule_ptr> &rules);
        rule_ptr repeat(const rule_ptr &content);
        rule_ptr seq(const std::vector<rule_ptr> &rules);
        rule_ptr sym(const std::string &name);
        rule_ptr _sym(const std::string &name);
        rule_ptr pattern(const std::string &value);
        rule_ptr str(const std::string &value);
        rule_ptr err(const rule_ptr &rule);
    }

    class Grammar {
    public:
        Grammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &rules);
        bool operator==(const Grammar &other) const;
        std::string start_rule_name() const;
        const rules::rule_ptr rule(const std::string &name) const;
        const std::vector<std::pair<std::string, rules::rule_ptr>> rules;
    };

    std::ostream& operator<<(std::ostream &stream, const Grammar &grammar);

    std::string compile(const Grammar &grammar, std::string name);
}

#endif  // TREE_SITTER_COMPILER_H_
