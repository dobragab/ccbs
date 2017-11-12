#ifndef CCBS_BUILD_PACKAGE_HPP
#define CCBS_BUILD_PACKAGE_HPP

#include <ccbs/package/package_flags.hpp>
#include <ccbs/rule/rule.hpp>

namespace ccbs {

class build_package : public package_flags
{
    std::set<package*> dependencies_;
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

    void add_dependency(package& package)
    {
        dependencies_.insert(&package);
        for (auto depPtr : package.dependencies())
            dependencies_.insert(depPtr);
    }

    std::set<package*> dependencies() const override { return dependencies_; }

    template<typename... ARGS>
    explicit build_package(std::set<package*> dependencies, ARGS const&... rules)
        : dependencies_(std::move(dependencies))
    {
        using swallow = int[];
        (void)swallow{0, ((void)(add_rule(rules)), 0)...};
    }

    void prepare() override;

    timestamp last_modified() const override
    {
        return time(nullptr);
    }
};

}

#endif // CCBS_BUILD_PACKAGE_HPP
