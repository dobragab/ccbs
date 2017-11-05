#include "package/build_package.hpp"
#include "package/pkg_config_package.hpp"
#include "rule/find_utils.hpp"
#include "target/shared_library.hpp"
#include "package/repository.hpp"

#include "asd b/asd.hpp"

using namespace ccsh::literals;

struct ccbs_pkg : public ccbs::shared_library
{
    ccbs_pkg()
    {
        output("ccbs.so"_p);
        sources(ccbs::find_matching("."_p, "*.cpp", 2));
        temp_dir("/tmp/ccbs"_p);
        include_directories(CCBS_DOT / "../ccsh/wrappers"_p);
        include_directories(CCBS_DOT / "../ccsh/include"_p);
        link_directories(CCBS_DOT / "../ccsh/lib"_p);
        link_libraries("ccsh_lib");
    }
};


int main()
{
    ccbs::repository::get<ccbs_pkg>().prepare();
}
