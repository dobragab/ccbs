#ifndef CCBS_REPOSITORY_HPP
#define CCBS_REPOSITORY_HPP

#include "package.hpp"

#include <typeindex>
#include <unordered_map>

namespace ccbs
{

class repository
{
    static std::unordered_map<std::type_index, std::unique_ptr<package>> packages;

    static package& get_package(std::type_index, package*(*)());

public:

    template<typename PACKAGE>
    static PACKAGE& get()
    {
        static_assert(std::is_base_of<package, PACKAGE>::value, "repository can store packages only!");
        return static_cast<PACKAGE&>(get_package(typeid(PACKAGE), []()-> package* {return new PACKAGE{};}));
    }
};

}

#endif // CCBS_REPOSITORY_HPP
