#ifndef CCBS_FIND_UTILS_HPP
#define CCBS_FIND_UTILS_HPP

#include <ccsh/ccsh.hpp>

#include <set>

namespace ccbs {

#define CCBS_DOT (ccsh::fs::path{__FILE__}.parent_path())

using path_transformer = std::function<ccsh::fs::path(ccsh::fs::path)>;

std::set<ccsh::fs::path> find_matching(ccsh::fs::path const& dir, std::string const& pattern, int depth = -1);
path_transformer change_extension(ccsh::fs::path const& to);
path_transformer add_extension(ccsh::fs::path const& ext);


}

#endif // CCBS_FIND_UTILS_HPP
