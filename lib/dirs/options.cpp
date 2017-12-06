#include <ccbs/dirs/options.hpp>

namespace ccbs {

options parse_options(int argc, const char** argv)
{
    options result;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        auto equals = arg.find('=');
        if (equals == std::string::npos)
            result.emplace(arg, "");
        else
            result.emplace(arg.substr(0, equals), arg.substr(equals + 1));
    }

    return result;
}

}

