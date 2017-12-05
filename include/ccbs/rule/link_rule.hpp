#ifndef PROJECT_LINK_RULE_HPP
#define PROJECT_LINK_RULE_HPP

#include "rule.hpp"

namespace ccbs {

class link_rule : public rule
{
    std::set<package*> pkg_dependencies_;

public:

    explicit link_rule(
        std::set<ccsh::fs::path> inputs,
        ccsh::fs::path output,
        rule_cmd cmd,
        std::set<ccsh::fs::path> dependency_files,
        std::set<package*> dependencies)
        : rule(std::move(inputs), std::move(output), std::move(cmd), std::move(dependency_files))
        , pkg_dependencies_(std::move(dependencies))
    { }

    bool needs_rebuild() const override;
};


}

#endif //PROJECT_LINK_RULE_HPP
