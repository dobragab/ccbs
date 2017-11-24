#ifndef PROJECT_GCC_HPP
#define PROJECT_GCC_HPP

#include "compiler.hpp"

#include <ccsh/cc/gcc.hpp>

namespace ccbs
{

class gcc : public compiler_t<ccsh::gcc_t>
{
    static constexpr std::array<const char*, 5> std_mapping()
    {
        return {
            "c++98",
            "c++98",
            "c++11",
            "c++14",
            "c++17",
        };
    };

public:
    using compiler_t<ccsh::gcc_t>::compiler_t;

    void input(ccsh::fs::path const& path) override
    {
        impl().args().push_back(path.string());
    }
    void output(ccsh::fs::path const& path) override
    {
        impl().o(path);
    }

    void std_version(std_ std1) override
    {
        impl().std(ccsh::enum_to_string(std1, std_mapping()));
    }
    void include_directory(ccsh::fs::path const& path) override
    {
        impl().I(path);
    }
    void link_directory(ccsh::fs::path const& path) override
    {
        impl().L(path);
    }
    void link_library(std::string const& lib) override
    {
        impl().l(lib);
    }
    void definition(std::string const& string, std::string const& string1) override
    {
        impl().D(string, string1);
    }

    void object_so() override
    {
        impl().c().PIC();
    }
    void object() override
    {
        impl().c();
    }
    void dependency() override
    {
        impl().MM();
    }
    void shared_object() override
    {
        impl().shared();
    }
};

}

#endif //PROJECT_GCC_HPP
