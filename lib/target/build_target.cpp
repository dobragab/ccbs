#include <ccbs/target/build_target.hpp>
#include <ccbs/rule/dependency_rule.hpp>

namespace ccbs
{

void build_target::prepare()
{
    build_package pkg_copy = static_cast<build_package&>(*this);

    auto objects_cmd = object_command();
    auto dependency_cmd = dependency_command();
    auto so_cmd = target_command();

    std::set<rule_ptr> dep_rules;
    for (const auto& file : files)
    {
        dep_rules.emplace(new dependency_rule{
            file,
            ccbs::prefix_dir(tempdir, ccbs::add_extension(".d"))(file),
            dependency_cmd
        });
    }

    std::set<rule_ptr> object_rules;
    for (const auto& file : files)
    {
        object_rules.emplace(new rule{
            {file},
            ccbs::prefix_dir(tempdir, ccbs::add_extension(".o"))(file),
            objects_cmd,
            {ccbs::prefix_dir(tempdir, ccbs::add_extension(".d"))(file)}
        });
    }

    auto so_rule = ccbs::make_rule(so_cmd, object_rules, outfile);

    pkg_copy.add_rule(dep_rules);
    pkg_copy.add_rule(object_rules);
    pkg_copy.add_rule(so_rule);
    pkg_copy.prepare();
}



}