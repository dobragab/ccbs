#include <ccbs/rule/ruleset.hpp>

#include <ccbs/util/containers.hpp>

namespace ccbs
{

int ruleset::build_dependencies(std::set<package*> const& dependencies)
{
    auto serialized_deps = serialize_set(
        dependencies,
        [](package* dep) { return dep; },
        [](package* dep) { return dep->dependencies(); }
    );

    for (const auto& dep : serialized_deps)
    {
        int result = dep->prepare();
        if (result != 0)
            return result;
    }
    return 0;
}

int ruleset::build(std::set<package*> const& dependencies)
{
    auto serialized_rules = serialize_set(
        this->rules,
        [](rule_ptr const& rule) { return rule->output(); },
        [](rule_ptr const& rule) { return rule->inputs(); }
    );

    int last_result = 0;
    for (auto& rule : serialized_rules)
    {
        if (rule->needs_rebuild() && (last_result = rule->make(dependencies)) != 0)
            break;
    }
    return last_result;
}

}
