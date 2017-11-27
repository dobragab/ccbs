#ifndef CCSH_SHARED_LIBRARY_HPP
#define CCSH_SHARED_LIBRARY_HPP

#include <ccbs/rule/ruleset.hpp>
#include <ccbs/rule/rule.hpp>
#include <ccbs/package/repository.hpp>
#include <ccbs/target/build_target.hpp>

namespace ccbs {


class shared_library : public build_target, public package
{
    compiler_ptr command_public_ = build_target::command_copy();
public:
    using build_target::build_target;

    compiler_ptr& command_public() { return command_public_; }
    compiler_ptr const& command_public() const { return command_public_; }

    std::set<package*> dependencies() const override
    {
        return build_target::dependencies();
    }
    void prepare() override
    {
        build();
    }
    void add_arguments(compiler& cc) const override;

    rule_cmd dependency_command() override
    {
        auto cmd = command_copy();
        cmd->dependency();
        return ccbs::make_rule_cmd(cmd);
    }
    rule_cmd object_command() override
    {
        auto cmd = command_copy();
        cmd->object_so();
        return ccbs::make_rule_cmd(cmd);
    }
    rule_cmd target_command() override
    {
        auto cmd = command_copy();
        cmd->shared_object();
        return ccbs::make_rule_cmd(cmd);
    }
};

}

#endif //CCSH_SHARED_LIBRARY_HPP
