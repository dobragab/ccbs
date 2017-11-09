#include "package/build_package.hpp"
#include "package/pkg_config_package.hpp"
#include "rule/find_utils.hpp"
#include "target/shared_library.hpp"
#include "package/repository.hpp"

#include "asd b/asd.hpp"
#include "package/installed_package.hpp"

using namespace ccsh::literals;

struct ccsh_pkg : public ccbs::installed_package
{
    ccsh_pkg() : ccbs::installed_package{CCBS_DOT / "../ccsh"_p, {"ccsh_lib"}}
    {
        include_directories(basedir() / "wrappers"_p);
    }
};

struct ccbs_pkg : public ccbs::shared_library
{
    ccbs_pkg()
    {
        output("ccbs.so"_p);
        sources(ccbs::find_matching("."_p, "*.cpp", 2));
        temp_dir("/tmp/ccbs"_p);
        depends<ccsh_pkg>();
    }
};


int main()
{
    ccbs::repository::get<ccbs_pkg>().prepare();
}
