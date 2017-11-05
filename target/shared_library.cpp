#include "shared_library.hpp"

#include <ccsh/core.hpp>

namespace
{

void dependency_parser(std::string line, std::set<ccsh::fs::path>& headers)
{
    auto npos = std::string::npos;

    auto colon = line.find(':');
    if (colon != npos)
        line = line.substr(colon + 1);

    if (line[line.size()-1] == '\\' && line[line.size()-2] == ' ')
        line = line.substr(0, line.length() - 2);

    while (!line.empty())
    {
        size_t last_space = 0;
        while (true)
        {
            last_space = line.find(' ', last_space);
            if (last_space != 0 && line[last_space - 1] == '\\')
            {
                line.erase(last_space - 1, 1);
            }
            else
            {
                break;
            }
        }

        if (last_space == npos)
        {
            headers.emplace(std::move(line));
            line.clear(); // std::move leaves line in an unspecified state, need to make sure it's clear
        }
        else if (last_space == 0)
        {
            line = line.substr(1);
        }
        else
        {
            headers.emplace(std::string{&line[0], &line[last_space]});
            line = line.substr(last_space + 1);
        }
    }
}

}

namespace ccbs
{

void shared_library::prepare()
{
    std::shared_ptr<ccbs::build_package> pkg_copy{new ccbs::build_package{*pkg}};

    auto objects_gcc = cmd;
    objects_gcc.c().PIC();
    auto objects_cmd = ccbs::make_rule_cmd(objects_gcc);

    auto dependency_gcc = cmd;
    dependency_gcc.MM();

    auto dependency_cmd = ccbs::make_rule_cmd(dependency_gcc);

    std::set<rule_ptr> object_rules;

    for (const auto& file : files)
    {
        auto d_file = ccbs::add_extension(".d")(file);
        if (!tempdir.empty())
            d_file = tempdir/d_file;

        rule_ptr dep_rule{new rule{{file}, d_file, dependency_cmd}};
        pkg_copy->make_rule(dep_rule);

        std::set<ccsh::fs::path> headers;
        auto parser = std::bind(&dependency_parser, std::placeholders::_1, std::ref(headers));

        ccsh::cat{dep_rule->output()} > parser;

        auto o_file = ccbs::add_extension(".o")(file);
        if (!tempdir.empty())
            o_file = tempdir/o_file;

        object_rules.emplace(new rule{{file}, o_file, objects_cmd, {dep_rule->output()}});
        pkg_copy->add_rule(rule_ptr{new rule{{file}, dep_rule->output(), dependency_cmd, headers}});
    }

    auto so_gcc = cmd;
    so_gcc.shared();
    auto so_cmd = ccbs::make_rule_cmd(so_gcc);
    auto so_rule = ccbs::make_rule(so_cmd, object_rules, outfile);

    pkg_copy->add_rule(object_rules);
    pkg_copy->add_rule(so_rule);
    pkg_copy->prepare();
}
}