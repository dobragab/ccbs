#ifndef CCBS_RULE_HPP
#define CCBS_RULE_HPP

#include <ccbs/package/package.hpp>
#include <ccbs/util/find_utils.hpp>

#include <ccbs/compiler/compiler.hpp>
#include <ccbs/util/polymorphic_value.hpp>

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

    virtual bool needs_rebuild() const;

    virtual int make(std::set<package*> const& dependencies)
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

    virtual ~rule() = default;
};

void dump_command(compiler_ptr const& rule, std::ostream& os);
rule_cmd make_rule_cmd(compiler_ptr const& rule);
std::set<ccsh::fs::path> rule_outputs(std::set<rule_ptr> const& rules);

}

#endif // CCBS_RULE_HPP
