#include "cmake_package.hpp"

using namespace ccsh::literals;

namespace ccbs
{

void cmake_package::prepare()
{
    ccsh::command generate_command = ccsh::shell("cmake"_p, {basedir().string()});
    ccsh::command build_command = ccsh::shell("cmake"_p, {"--build", basedir().string()});

    if ((build_command || (generate_command && build_command)).run() != 0)
        throw "up";
}

}
