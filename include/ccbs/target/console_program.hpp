#ifndef PROJECT_CONSOLE_PROGRAM_HPP
#define PROJECT_CONSOLE_PROGRAM_HPP

#include <ccbs/target/build_target.hpp>

namespace ccbs
{

class console_program : public build_target
{
public:
    using build_target::build_target;

    virtual rule_cmd dependency_command() override
    {
        return ccbs::make_rule_cmd(command_copy().MM());
    }
    virtual rule_cmd object_command() override
    {
        return ccbs::make_rule_cmd(command_copy().c());
    }
    virtual rule_cmd target_command() override
    {
        auto command = command_copy();
        for (auto ptr : dependencies())
            for (const auto& dir : ptr->link_directories())
            command.args().push_back("-Wl,-rpath," + dir.string());

        return ccbs::make_rule_cmd(command);
    }
};

}

#endif //PROJECT_CONSOLE_PROGRAM_HPP
