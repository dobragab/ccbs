#ifndef CCBS_BUILD_PACKAGE_HPP
#define CCBS_BUILD_PACKAGE_HPP

#include <ccbs/package/package_flags.hpp>
#include <ccbs/rule/rule.hpp>

namespace ccbs {

class build_package
{
    package_flags flags_;
    std::set<package*> dependencies_;
    std::set<rule_ptr> rules;

    std::vector<rule_ptr> serialize();

protected:
    package_flags& flags() { return flags_; }
    package_flags const& flags() const { return flags_; }

    void include_directories(ccsh::fs::path dir)
    {
        flags_.include_directories(std::move(dir));
    }
    void link_directories(ccsh::fs::path dir)
    {
        flags_.link_directories(std::move(dir));
    }
    void link_libraries(std::string lib)
    {
        flags_.link_libraries(std::move(lib));
    }
    void definitions(std::string name, std::string value)
    {
        flags_.definitions(std::move(name), std::move(value));
    }

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
};

}

#endif // CCBS_BUILD_PACKAGE_HPP
