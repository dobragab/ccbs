#ifndef PROJECT_BUILD_TARGET_HPP
#define PROJECT_BUILD_TARGET_HPP

#include <ccbs/package/build_package.hpp>
#include <ccbs/rule/rule.hpp>
#include <ccbs/package/repository.hpp>

namespace ccbs {

class build_target : public build_package
{
    std::set<ccsh::fs::path> files;
    ccsh::fs::path tempdir;
    ccsh::fs::path outfile;
    ccsh::command_builder<ccsh::gcc> cmd;

public:

    explicit build_target(ccsh::fs::path output)
        : build_package({})
        , outfile(std::move(output))
        , cmd{ccsh::gcc()}
    {}

    void build() override;

    void sources(std::set<ccsh::fs::path> const& source_files)
    {
        files.insert(source_files.begin(), source_files.end());
    }

    void sources(ccsh::fs::path const& source_file)
    {
        files.insert(source_file);
    }

    void depends(package& dep) { build_package::add_dependency(dep); }

    template<typename PACKAGE>
    void depends() { depends(repository::get<PACKAGE>()); }

    void temp_dir(ccsh::fs::path dir) { tempdir = std::move(dir); }

    ccsh::command_builder<ccsh::gcc>& command() { return cmd; }
    ccsh::command_builder<ccsh::gcc> command_copy() const { return cmd; }
    ccsh::fs::path const& output() const { return outfile; }

    virtual rule_cmd dependency_command() = 0;
    virtual rule_cmd object_command() = 0;
    virtual rule_cmd target_command() = 0;
};

}

#endif //PROJECT_BUILD_TARGET_HPP
