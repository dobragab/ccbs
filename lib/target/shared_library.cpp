#include <ccbs/target/shared_library.hpp>

using namespace ccsh::literals;

namespace ccbs
{

std::vector<std::string> shared_library::link_libraries() const
{
    auto base = package_flags::link_libraries();
    base.push_back(extract_library_name(output()));
    return base;
}

std::vector<ccsh::fs::path> shared_library::link_directories() const
{
    auto base = package_flags::link_directories();
    base.push_back(output().parent_path());
    return base;
}

}

