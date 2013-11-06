#ifndef __TreeSitter__Rule__
#define __TreeSitter__Rule__

#include <string>

namespace tree_sitter {
    namespace rules {
        template<class value> class TransitionMap;
        
        class Rule {
        public:
            virtual TransitionMap<Rule> transitions() const = 0;
            virtual Rule * copy() const = 0;
            virtual bool operator==(const Rule& other) const = 0;
            virtual std::string to_string() const = 0;
        };
        
        class Blank : public Rule {
        public:
            Blank();
            TransitionMap<Rule> transitions() const;
            Blank * copy() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        };
        
        class Symbol : public Rule {
        public:
            Symbol(int id);
            TransitionMap<Rule> transitions() const;
            Symbol * copy() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            int id;
        };
        
        class Choice : public Rule {
        public:
            Choice(const Rule &left, const Rule &right);
            Choice(const Rule *left, const Rule *right);
            Choice(std::shared_ptr<const Rule> left, std::shared_ptr<const Rule> right);
            TransitionMap<Rule> transitions() const;
            Choice * copy() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            std::shared_ptr<const Rule> left;
            std::shared_ptr<const Rule> right;
        };
        
        class Seq : public Rule {
        public:
            Seq(const Rule &left, const Rule &right);
            Seq(const Rule *left, const Rule *right);
            Seq(std::shared_ptr<const Rule> left, std::shared_ptr<const Rule> right);
            TransitionMap<Rule> transitions() const;
            Seq * copy() const;
            bool operator==(const Rule& other) const;
            std::string to_string() const;
        private:
            std::shared_ptr<const Rule> left;
            std::shared_ptr<const Rule> right;
        };
    }
}

#endif
