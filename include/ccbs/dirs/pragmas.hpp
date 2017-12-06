#ifndef PROJECT_PRAGMAS_HPP
#define PROJECT_PRAGMAS_HPP

#include <ccsh/ccsh.hpp>
#include <ccsh/cc.hpp>

namespace ccbs {

std::vector<ccsh::fs::path> get_all_pragmas(ccsh::command_builder<ccsh::gcc>& command, int& result);
ccsh::fs::path get_compiler_path();
ccsh::command_builder<ccsh::gcc> get_gcc_command(int argc, const char** argv);

}

#endif //PROJECT_PRAGMAS_HPP
