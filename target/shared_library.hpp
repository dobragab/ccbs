#ifndef CCSH_SHARED_LIBRARY_HPP
#define CCSH_SHARED_LIBRARY_HPP

#include "../package/build_package.hpp"
#include "../rule/rule.hpp"
#include "../package/repository.hpp"

namespace ccbs {


class shared_library : public package
{
    std::shared_ptr<ccbs::build_package> pkg{new ccbs::build_package{{}}};
    std::set<ccsh::fs::path> files;
    ccsh::fs::path tempdir;
    ccsh::fs::path outfile;
    ccsh::command_builder<ccsh::gcc> cmd = ccsh::gcc();

public:

    void prepare() override;

    timestamp last_modified() const override
    {
        return {0};
    }
    std::vector<ccsh::fs::path> include_directories() const override
    {
        return pkg->include_directories();
    }
    std::vector<ccsh::fs::path> link_directories() const override
    {
        return pkg->link_directories();
    }
    std::vector<std::string> link_libraries() const override
    {
        return pkg->link_libraries();
    }
    std::vector<std::pair<std::string, std::string>> definitions() const override
    {
        return pkg->definitions();
    }

public:

    shared_library& sources(std::set<ccsh::fs::path> const& source_files)
    {
        files.insert(source_files.begin(), source_files.end());
        return *this;
    }

    shared_library& sources(ccsh::fs::path const& source_file)
    {
        files.insert(source_file);
        return *this;
    }

    shared_library& depends(package& dep)
    {
        pkg->add_dependency(dep);
        return *this;
    }

    template<typename PACKAGE>
    shared_library& depends()
    {
        pkg->add_dependency(repository::get<PACKAGE>());
        return *this;
    }

    shared_library& include_directories(ccsh::fs::path dir)
    {
        pkg->include_directories(std::move(dir));
        return *this;
    }
    shared_library& link_directories(ccsh::fs::path dir)
    {
        pkg->link_directories(std::move(dir));
        return *this;
    }
    shared_library& link_libraries(std::string lib)
    {
        pkg->link_libraries(std::move(lib));
        return *this;
    }
    shared_library& definitions(std::string name, std::string value)
    {
        pkg->definitions(std::move(name), std::move(value));
        return *this;
    }

    shared_library& temp_dir(ccsh::fs::path dir)
    {
        tempdir = std::move(dir);
        return *this;
    }

    shared_library& output(ccsh::fs::path dir)
    {
        outfile = std::move(dir);
        return *this;
    }

    ccsh::command_builder<ccsh::gcc>& command()
    {
        return cmd;
    }
};


}

#endif //CCSH_SHARED_LIBRARY_HPP
