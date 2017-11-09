#ifndef CCSH_SHARED_LIBRARY_HPP
#define CCSH_SHARED_LIBRARY_HPP

#include "../package/build_package.hpp"
#include "../rule/rule.hpp"
#include "../package/repository.hpp"
#include "build_target.hpp"

namespace ccbs {


class shared_library : public build_target
{
public:
    using build_target::build_target;

    std::vector<ccsh::fs::path> link_directories() const override;
    std::vector<std::string> link_libraries() const override;

    rule_cmd dependency_command() override
    {
        return ccbs::make_rule_cmd(command().MM());
    }
    rule_cmd object_command() override
    {
        return ccbs::make_rule_cmd(command().c().PIC());
    }
    rule_cmd target_command() override
    {
        return ccbs::make_rule_cmd(command().shared());
    }
};


}

#endif //CCSH_SHARED_LIBRARY_HPP
