#ifndef TREE_SITTER_COMPILER_H_
#define TREE_SITTER_COMPILER_H_

#include <vector>
#include <set>
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
        rule_ptr pattern(const std::string &value);
        rule_ptr str(const std::string &value);
        rule_ptr keyword(const std::string &value);
        rule_ptr keypattern(const std::string &value);
        rule_ptr err(const rule_ptr &rule);
        rule_ptr prec(int precedence, rule_ptr rule);
        rule_ptr token(rule_ptr rule);
    }

    class Grammar {
    protected:
        const std::vector<std::pair<std::string, rules::rule_ptr>> rules_;
        std::set<std::string> ubiquitous_tokens_;
        std::set<char> separators_;

    public:
        Grammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &rules);
        bool operator==(const Grammar &other) const;
        std::string start_rule_name() const;
        const rules::rule_ptr rule(const std::string &name) const;

        const std::vector<std::pair<std::string, rules::rule_ptr>> & rules() const;
        const std::set<std::string> & ubiquitous_tokens() const;
        Grammar & ubiquitous_tokens(const std::set<std::string> &ubiquitous_tokens);
        const std::set<char> & separators() const;
        Grammar & separators(const std::set<char> &separators);
    };

    struct Conflict {
        Conflict(std::string description);
        std::string description;
        bool operator==(const Conflict &other) const;
        bool operator<(const Conflict &other) const;
    };

    enum GrammarErrorType {
        GrammarErrorTypeRegex,
        GrammarErrorTypeUndefinedSymbol
    };

    class GrammarError {
    public:
        GrammarError(GrammarErrorType type, std::string message);
        bool operator==(const GrammarError &other) const;
        GrammarErrorType type;
        std::string message;
    };

    std::ostream& operator<<(std::ostream &stream, const Grammar &grammar);
    std::ostream& operator<<(std::ostream &stream, const Conflict &conflict);
    std::ostream& operator<<(std::ostream &stream, const GrammarError *error);

    std::tuple<std::string, std::vector<Conflict>, const GrammarError *>
    compile(const Grammar &grammar, std::string name);
}

#endif  // TREE_SITTER_COMPILER_H_
