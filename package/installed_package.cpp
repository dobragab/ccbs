#include "installed_package.hpp"

using namespace ccsh::literals;

namespace ccbs
{


installed_package::installed_package(ccsh::fs::path basedir_, std::vector<std::string> libraries)
    : basedir_(std::move(basedir_))
{
    include_directories(this->basedir_ / "include"_p);
    link_directories(this->basedir_ / "lib"_p);
    for (const auto& library : libraries)
        link_libraries(library);
}


}
