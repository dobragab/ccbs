#include <iostream>

#define CCSH_NON_STANDARD_DOLLAR

#include <ccsh/ccsh.hpp>

#include <fstream>
#include <random>
#include <unordered_set>

#include <ccbs/dirs/pragmas.hpp>

using namespace ccsh;
using namespace ccsh::literals;


void print_usage()
{
    std::cout << "Usage: ccbs-dirs [gcc-options] file" << std::endl;
    std::cout << "Note: it can process only ONE file!" << std::endl;
}

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    ccsh::command_builder<ccsh::gcc> gcc = ccbs::get_gcc_command(argc, argv);

    int last_result;
    auto includes = ccbs::get_all_pragmas(gcc, last_result);

    if (last_result != 0)
        return (gcc > "/dev/null"_p).run();

    for (const auto& include : includes)
        std::cout << include.string() << std::endl;
}



