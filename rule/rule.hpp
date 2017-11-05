#ifndef CCBS_RULE_HPP
#define CCBS_RULE_HPP

#include "../package/package.hpp"
#include "find_utils.hpp"

#include <ccsh/ccsh.hpp>
#include <ccsh/cc.hpp>

#include <memory>
#include <set>
#include <utility>
#include <functional>

namespace ccbs {

using rule_cmd = std::function<int(std::set<ccsh::fs::path> const&, ccsh::fs::path const&, std::set<package*> const&)>;

class rule;
using rule_ptr = std::shared_ptr<rule>;

class rule
{
    std::set<ccsh::fs::path> inputs_;
    ccsh::fs::path output_;
    rule_cmd cmd;
    std::set<ccsh::fs::path> dependencies_;

public:
    rule(std::set<ccsh::fs::path> inputs, ccsh::fs::path output, rule_cmd cmd, std::set<ccsh::fs::path> dependencies = {})
        : inputs_(std::move(inputs))
        , output_(std::move(output))
        , cmd(std::move(cmd))
        , dependencies_(std::move(dependencies))
    { }

    bool needs_rebuild() const;

    int make(std::set<package*> const& dependencies)
    {
        return cmd(inputs_, output_, dependencies);
    }

    std::set<ccsh::fs::path> const& inputs() const
    {
        return inputs_;
    }
    ccsh::fs::path const& output() const
    {
        return output_;
    }
    std::set<ccsh::fs::path> const& dependencies() const
    {
        return dependencies_;
    }

};

void dump_command(ccsh::command_builder<ccsh::gcc> const& rule, std::ostream& os);
rule_cmd make_rule_cmd(ccsh::command_builder<ccsh::gcc> const& rule);
std::set<rule_ptr> make_rules(rule_cmd const& cmd, std::set<ccsh::fs::path> const& inputs, path_transformer path_rule, ccsh::fs::path const& temp_dir = {});
rule_ptr make_rule(rule_cmd const& cmd, std::set<rule_ptr> const& inputs, ccsh::fs::path const& output);

}

#endif // CCBS_RULE_HPP
