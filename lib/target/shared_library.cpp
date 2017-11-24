#include <ccbs/target/shared_library.hpp>

using namespace ccsh::literals;

namespace ccbs
{

void shared_library::add_arguments(compiler& cc) const
{
    cc.link_directory(output().parent_path());
    cc.link_library(extract_library_name(output()));
}

}

