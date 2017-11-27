#include <ccbs/rule/ruleset.hpp>

#include <ccbs/util/containers.hpp>

namespace ccbs
{

std::vector<ccbs::rule_ptr> ruleset::serialize()
{
    std::map<ccsh::fs::path, rule_ptr> rules;
    for (auto& rule : this->rules)
        rules.emplace(rule->output(), rule);

    std::vector<rule_ptr> result;
    auto num = rules.size();
    result.reserve(num);

    while (result.size() != num)
    {
        size_t rules_size = rules.size();
        for (auto it = rules.begin(); it != rules.end(); ++it)
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
        if (rules_size == rules.size())
            throw "circular dependency";
    }

    return result;
}

void ruleset::build(std::set<package*> const& dependencies)
{
    for (const auto& dep : dependencies)
        dep->prepare();

    auto serialized_rules = serialize();

    for (auto& rule : serialized_rules)
    {
        if (rule->needs_rebuild() && rule->make(dependencies) != 0)
            break;
    }
}

}
