#include <iostream>

#define CCSH_NON_STANDARD_DOLLAR

#include <ccsh/ccsh.hpp>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

#include <unistd.h>

using namespace ccsh;


template<typename FUNC>
void tokenize_string(std::string line, std::string const& delimiters, FUNC&& func)
{
    char* saveptr = nullptr;
    char* token = strtok_r(&line[0], delimiters.c_str(), &saveptr);

    while (token != nullptr)
    {
        func(token);
        token = strtok_r(nullptr, delimiters.c_str(), &saveptr);
    }
}

void print_usage()
{
    std::cout << "Usage: ccbs-dirs [gcc-options] file" << std::endl;
    std::cout << "Note: it can process only ONE file!" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    bool compile_only = false;
    std::string compile_only_str = "-c";

    std::vector<std::string> gcc_args;
    gcc_args.reserve(std::size_t(argc));
    for (int i = 1; i < argc; ++i)
    {
        gcc_args.emplace_back(argv[i]);
    }

    gcc_args.emplace_back("-E");

    std::string cxx = ccsh::$("CXX");
    if (cxx.empty())
        cxx = "/usr/bin/c++";

    std::vector<ccsh::fs::path> includes;

    auto pragma_processor = [&](std::string line) {
        std::vector<std::string> parts;
        tokenize_string(line, " ", [&](char * part){
            parts.emplace_back(part);
        });

        if (parts.size() == 4 &&
            parts[0] == "#pragma" &&
            parts[1] == "ccbs")
        {
            if (parts[2] == "I")
            {
                if (std::find(includes.begin(), includes.end(), parts[3]) == includes.end())
                    includes.emplace_back(parts[3]);
            }
            else
            {
                std::cerr << "Unsupported pragma " << parts[2] << std::endl;
            }
        }
    };

    size_t includes_count;
    int last_result;
    do
    {
        includes_count = includes.size();
        last_result = (ccsh::shell(cxx, gcc_args) >= "/dev/null" > pragma_processor).run();
    } while(includes_count != includes.size());

    if (last_result != 0)
        return (ccsh::shell(cxx, gcc_args) > "/dev/null").run();

    for (const auto& include : includes)
        std::cout << include.string() << std::endl;
    return 0;
}



