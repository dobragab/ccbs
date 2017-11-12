#include <ccbs/package/build_package.hpp>
#include <ccbs/package/pkg_config_package.hpp>
#include <ccbs/package/installed_package.hpp>

#include <ccbs/target/shared_library.hpp>
#include <ccbs/target/console_program.hpp>
#include <ccbs/package/cmake_package.hpp>

using namespace ccsh::literals;

struct ccsh_pkg : public ccbs::cmake_package
{
    ccsh_pkg() : ccbs::cmake_package{CCBS_DOT / "../../ccsh"_p, {"ccsh_lib"}}
    {
        include_directories(basedir() / "wrappers"_p);
        link_libraries("pthread");
    }
};

struct ccbs_pkg : public ccbs::console_program
{
    ccbs_pkg() : ccbs::console_program(CCBS_DOT / "ccbs2"_p)
    {
        sources(ccbs::find_matching(CCBS_DOT, "*.cpp", 3));
        include_directories(CCBS_DOT / "../include"_p);
        temp_dir("/tmp/ccbs"_p);
        depends<ccsh_pkg>();
    }
};


int main()
{
    ccbs::repository::get<ccbs_pkg>().prepare();
}
