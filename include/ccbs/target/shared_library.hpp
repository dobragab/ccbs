#ifndef CCSH_SHARED_LIBRARY_HPP
#define CCSH_SHARED_LIBRARY_HPP

#include <ccbs/package/build_package.hpp>
#include <ccbs/rule/rule.hpp>
#include <ccbs/package/repository.hpp>
#include <ccbs/target/build_target.hpp>

namespace ccbs {


class shared_library : public build_target
{
public:
    using build_target::build_target;

    std::vector<ccsh::fs::path> link_directories() const override;
    std::vector<std::string> link_libraries() const override;

    rule_cmd dependency_command() override
    {
        return ccbs::make_rule_cmd(command_copy().MM());
    }
    rule_cmd object_command() override
    {
        return ccbs::make_rule_cmd(command_copy().c().PIC());
    }
    rule_cmd target_command() override
    {
        return ccbs::make_rule_cmd(command_copy().shared());
    }
};


}

#endif //CCSH_SHARED_LIBRARY_HPP
