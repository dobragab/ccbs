#ifndef CCSH_SHARED_LIBRARY_HPP
#define CCSH_SHARED_LIBRARY_HPP

#include "../package/build_package.hpp"
#include "../rule/rule.hpp"
#include "../package/repository.hpp"

namespace ccbs {


class shared_library : public build_package
{
    std::set<ccsh::fs::path> files;
    ccsh::fs::path tempdir;
    ccsh::fs::path outfile;
    ccsh::command_builder<ccsh::gcc> cmd;

public:

    shared_library()
        : build_package({})
        , cmd{ccsh::gcc()}
    {}

    void prepare() override;

    void sources(std::set<ccsh::fs::path> const& source_files)
    {
        files.insert(source_files.begin(), source_files.end());
    }

    void sources(ccsh::fs::path const& source_file)
    {
        files.insert(source_file);
    }

    void depends(package& dep)
    {
        build_package::add_dependency(dep);
    }

    template<typename PACKAGE>
    void depends()
    {
        build_package::add_dependency(repository::get<PACKAGE>());
    }

    void temp_dir(ccsh::fs::path dir)
    {
        tempdir = std::move(dir);
    }

    void output(ccsh::fs::path dir)
    {
        outfile = std::move(dir);
    }

    ccsh::command_builder<ccsh::gcc>& command()
    {
        return cmd;
    }
};


}

#endif //CCSH_SHARED_LIBRARY_HPP
