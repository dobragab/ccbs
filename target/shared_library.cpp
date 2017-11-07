#include "shared_library.hpp"

#include "../rule/dependency_rule.hpp"

namespace ccbs
{

void shared_library::prepare()
{
    std::shared_ptr<ccbs::build_package> pkg_copy{new ccbs::build_package{*pkg}};

    pkg_copy->add_dependency(*pkg_copy); // sorry.

    auto objects_gcc = cmd;
    objects_gcc.c().PIC();
    auto objects_cmd = ccbs::make_rule_cmd(objects_gcc);

    auto dependency_gcc = cmd;
    dependency_gcc.MM();

    auto dependency_cmd = ccbs::make_rule_cmd(dependency_gcc);

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

    auto so_gcc = cmd;
    so_gcc.shared();
    auto so_cmd = ccbs::make_rule_cmd(so_gcc);
    auto so_rule = ccbs::make_rule(so_cmd, object_rules, outfile);

    pkg_copy->add_rule(dep_rules);
    pkg_copy->add_rule(object_rules);
    pkg_copy->add_rule(so_rule);
    pkg_copy->prepare();
}
}