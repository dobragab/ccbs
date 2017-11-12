#include "build_package.hpp"

#include "../util/containers.hpp"

namespace ccbs
{

std::vector<ccbs::rule_ptr> build_package::serialize()
{
    std::map<ccsh::fs::path, rule_ptr> rules;
    for (auto& rule : this->rules)
        rules.emplace(rule->output(), rule);

    std::vector<rule_ptr> result;
    auto num = rules.size();
    result.reserve(num);

    while (result.size() != num)
    {
        auto it_end = rules.end();
        for (auto it = rules.begin(); it != it_end; ++it)
        {
            auto& rulePair = *it;
            const auto& ruleInputs = rulePair.second->inputs();
            bool hasUnresolvedInput = std::any_of(
                ruleInputs.begin(),
                ruleInputs.end(),
                [&] (const ccsh::fs::path& input) {
                    return bool(rules.count(input));
                });

            if (!hasUnresolvedInput)
            {
                result.push_back(rulePair.second);
                rules.erase(it);
            }
        }
    }

    return result;
}

void build_package::prepare()
{
    auto dep_copy = dependencies_;
    dep_copy.insert(this);

    for (const auto& dep : dep_copy)
        if (dep != this)
            dep->prepare();

    auto serialized_rules = serialize();

    for (auto& rule : serialized_rules)
    {
        if (rule->needs_rebuild() && rule->make(dep_copy) != 0)
            break;
    }
}

}
