#include <ccbs/rule/link_rule.hpp>

namespace ccbs {

bool link_rule::needs_rebuild() const
{
    if (rule::needs_rebuild())
        return true;

    auto outstamp = ccsh::fs::last_write_time(output());

    auto is_fresher = [outstamp](package * p) {
        return outstamp < p->last_modified();
    };

    return std::any_of(pkg_dependencies_.begin(), pkg_dependencies_.end(), is_fresher);
}

}
