#include "package/build_package.hpp"
#include "package/pkg_config_package.hpp"
#include "package/installed_package.hpp"

#include "target/shared_library.hpp"
#include "target/console_program.hpp"

using namespace ccsh::literals;

struct ccsh_pkg : public ccbs::installed_package
{
    ccsh_pkg() : ccbs::installed_package{CCBS_DOT / "../ccsh"_p, {"ccsh_lib"}}
    {
        include_directories(basedir() / "wrappers"_p);
    }
};

struct ccbs_pkg : public ccbs::console_program
{
    ccbs_pkg() : ccbs::console_program(CCBS_DOT / "ccbs2"_p)
    {
        sources(ccbs::find_matching("."_p, "*.cpp", 2));
        temp_dir("/tmp/ccbs"_p);
        depends<ccsh_pkg>();
    }
};


int main()
{
    ccbs::repository::get<ccbs_pkg>().prepare();
}
