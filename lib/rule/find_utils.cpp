#include <ccbs/rule/find_utils.hpp>

namespace ccbs
{

std::set<ccsh::fs::path> find_matching(ccsh::fs::path const& dir, std::string const& pattern, int depth)
{
    std::vector<std::string> str_result;
    if (depth < 0)
        ccsh::shell("find", {dir.string(), "-name", pattern}) > str_result;
    else
        ccsh::shell("find", {dir.string(), "-maxdepth", std::to_string(depth), "-name", pattern}) > str_result;
    std::set<ccsh::fs::path> result;
    std::copy(str_result.begin(), str_result.end(), std::inserter(result, result.end()));
    return result;
}

path_transformer change_extension(ccsh::fs::path const& to)
{
    return [to](ccsh::fs::path input) {
        return input.replace_extension(to);
    };
}

path_transformer add_extension(ccsh::fs::path const& ext)
{
    return [ext](ccsh::fs::path input) {
        return input.replace_extension(input.extension().string() + ext.string());
    };
}

path_transformer prefix_dir(ccsh::fs::path const& prefix, path_transformer transformer)
{
    return [prefix, transformer](ccsh::fs::path input) {
        input = transformer(input);
        if (!input.empty())
        {
            input = ccsh::fs::weakly_canonical(prefix / input);
        }
        return input;
    };
}

}
