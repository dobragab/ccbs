#include <ccbs/package/repository.hpp>

namespace ccbs
{
std::unordered_map<std::type_index, std::unique_ptr<package>> repository::packages;

package& repository::get_package(std::type_index ti, package* (*factory)())
{
    auto it = packages.find(ti);
    if (it != packages.end())
        return *it->second;

    auto emplace_result = packages.emplace(ti, std::unique_ptr<package>{factory()});
    return *emplace_result.first->second;
}

}
