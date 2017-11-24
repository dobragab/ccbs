#include <ccbs/rule/rule.hpp>

namespace ccbs
{

void dump_command(jbcoe::polymorphic_value<compiler> const& rule, std::ostream& os)
{
    auto& args = rule->native().args();
    os << rule->native().binary().string() << " ";
    for (const auto& arg : args)
    {
        os << arg << " ";
    }
    os << std::endl;
}

rule_cmd make_rule_cmd(jbcoe::polymorphic_value<compiler> const& rule)
{
    return [rule](std::set<ccsh::fs::path> const& inputs,
                  ccsh::fs::path const& output,
                  std::set<package*> const& pkgs) -> int {

        auto rule_copy = rule;

        for (const auto& p : inputs)
            rule_copy->input(p);

        rule_copy->output(output);

        for (const auto& pkg : pkgs)
        {
            pkg->add_arguments(*rule_copy);

            for (const auto& def : pkg->definitions())
                rule_copy->definition(def.first, def.second);

            for (const auto& include_dir : pkg->include_directories())
                rule_copy->include_directory(include_dir);

            for (const auto& link_dir : pkg->link_directories())
                rule_copy->link_directory(link_dir);

            for (const auto& link_lib : pkg->link_libraries())
                rule_copy->link_library(link_lib);
        }

        ccsh::fs::path output_dir = output.parent_path();

        if (!output_dir.empty())
        {
            int mkdir_result = ccsh::shell("mkdir", {"-p", output.parent_path().string()}).run();
            if (mkdir_result != 0)
                return mkdir_result;
        }

        dump_command(rule_copy, std::cout);

        return rule_copy->run();
    };
}

std::set<rule_ptr> make_rules(rule_cmd const& cmd, std::set<ccsh::fs::path> const& inputs, path_transformer path_rule)
{
    std::set<rule_ptr> result;
    for (const auto& input : inputs)
    {
        result.emplace(new rule{{input}, path_rule(input), cmd});
    }
    return result;
}

rule_ptr make_rule(rule_cmd const& cmd, std::set<rule_ptr> const& inputs, ccsh::fs::path const& output)
{
    std::set<ccsh::fs::path> input_files;
    for (const auto& input : inputs)
    {
        input_files.insert(input->output());
    }
    return std::make_shared<rule>(std::move(input_files), output, cmd);
}

bool rule::needs_rebuild() const
{
    if (!ccsh::fs::exists(output_))
        return true;

    auto outstamp = ccsh::fs::last_write_time(output_);

    auto is_fresher = [outstamp](ccsh::fs::path const& p) {
        return !ccsh::fs::exists(p) || outstamp < ccsh::fs::last_write_time(p);
    };

    return std::any_of(inputs_.begin(), inputs_.end(), is_fresher) ||
        std::any_of(dependencies_.begin(), dependencies_.end(), is_fresher);
}

}
