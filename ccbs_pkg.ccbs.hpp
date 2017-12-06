#pragma ccbs /home/gabesz/git/ccsh/include
#pragma ccbs /home/gabesz/git/ccsh/wrappers

#include <ccbs/rule/ruleset.hpp>
#include <ccbs/package/pkg_config_package.hpp>
#include <ccbs/package/installed_package.hpp>

#include <ccbs/target/shared_library.hpp>
#include <ccbs/target/console_program.hpp>
#include <ccbs/package/cmake_package.hpp>
#include <ccbs/util/visitors.hpp>

using namespace ccsh::literals;

struct pthread_pkg : public ccbs::package_flags
{
    void add_arguments(ccbs::compiler& compiler) const override
    {
        ccbs::visit_one(compiler, [](ccbs::gcc& cc) { cc.native().args().emplace_back("-pthread"); });
    }
};

struct ccsh_pkg : public ccbs::cmake_package
{
    ccsh_pkg() : ccbs::cmake_package{CCBS_DOT / "../ccsh"_p, {"ccsh_lib"}}
    {
        include_directories(basedir() / "wrappers"_p);
    }
};

struct ccbs_pkg : public ccbs::shared_library
{
    ccbs_pkg() : ccbs::shared_library(CCBS_DOT / "../ccbs2"_p)
    {
        sources(ccbs::find_matching(CCBS_DOT / "lib", "*.cpp", 3));
        command()->include_directory(CCBS_DOT / "include"_p);
        temp_dir("/tmp/ccbs"_p);
        command()->std_version(ccbs::compiler::cpp11);
        depends<pthread_pkg>();
        depends<ccsh_pkg>();
    }
};
