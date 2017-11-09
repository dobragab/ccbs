#include "shared_library.hpp"

using namespace ccsh::literals;

namespace ccbs
{

std::vector<std::string> shared_library::link_libraries() const
{
    auto base = package_flags::link_libraries();
    auto lib = output().filename();
    lib.replace_extension(""_p);
    std::string libname = lib.string();
    if (libname.rfind("lib"))
        libname = libname.substr(3);

    base.push_back(libname);
}

std::vector<ccsh::fs::path> shared_library::link_directories() const
{
    auto base = package_flags::link_directories();
    base.push_back(output().parent_path());
    return base;
}

}

