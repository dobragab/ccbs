#ifndef PROJECT_CONSOLE_PROGRAM_HPP
#define PROJECT_CONSOLE_PROGRAM_HPP

#include <ccbs/target/build_target.hpp>
#include <ccbs/util/visitors.hpp>

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
        auto cmd = command_copy();
        visit_one(*cmd, [this](ccbs::gcc& cc) {
            ccbs::gcc cc_copy{ccsh::gcc{}};
            for (const auto& depPtr : dependencies())
                depPtr->add_arguments(cc_copy);
            for (const auto& arg : cc_copy.native().args())
                if (arg.rfind("-L") != std::string::npos)
                    cc.add_rpath(arg.substr(2));
        });

        return ccbs::make_rule_cmd(cmd);
    }
};

}

#endif //PROJECT_CONSOLE_PROGRAM_HPP
