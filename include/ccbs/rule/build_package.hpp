#ifndef CCBS_BUILD_PACKAGE_HPP
#define CCBS_BUILD_PACKAGE_HPP

#include <ccbs/package/package_flags.hpp>
#include <ccbs/rule/rule.hpp>

namespace ccbs {

class build_package
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

    std::set<package*> dependencies() const { return dependencies_; }

    virtual void build();
    virtual ~build_package() = default;
};

}

#endif // CCBS_BUILD_PACKAGE_HPP
