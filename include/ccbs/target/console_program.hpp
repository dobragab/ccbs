#ifndef PROJECT_CONSOLE_PROGRAM_HPP
#define PROJECT_CONSOLE_PROGRAM_HPP

#include <ccbs/target/build_target.hpp>

namespace ccbs
{

class console_program : public build_target
{
public:
    using build_target::build_target;

    rule_cmd dependency_command() override
    {
        auto cmd = command_copy();
        cmd->dependency();
        return ccbs::make_rule_cmd(cmd);
    }
    rule_cmd object_command() override
    {
        auto cmd = command_copy();
        cmd->object();
        return ccbs::make_rule_cmd(cmd);
    }
    rule_cmd target_command() override
    {
        return ccbs::make_rule_cmd(command_copy());
    }
};

}

#endif //PROJECT_CONSOLE_PROGRAM_HPP
