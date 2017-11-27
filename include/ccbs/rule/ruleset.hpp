#ifndef CCBS_BUILD_PACKAGE_HPP
#define CCBS_BUILD_PACKAGE_HPP

#include <ccbs/package/package_flags.hpp>
#include <ccbs/rule/rule.hpp>

namespace ccbs {

class ruleset
{
    std::set<rule_ptr> rules;
    std::vector<rule_ptr> serialize();

public:

    void add_rule(std::set<rule_ptr> const& inputs)
    {
        rules.insert(inputs.begin(), inputs.end());
    }
    void add_rule(rule_ptr const& input)
    {
        rules.insert(input);
    }

    void build(std::set<package*> const& dependencies);
};

}

#endif // CCBS_BUILD_PACKAGE_HPP
