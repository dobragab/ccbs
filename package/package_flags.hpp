#ifndef CCBS_PACKAGE_FLAGS_HPP
#define CCBS_PACKAGE_FLAGS_HPP

#include "package.hpp"

namespace ccbs {

class package_flags : public package
{
protected:
    std::vector<ccsh::fs::path> I;
    std::vector<ccsh::fs::path> L;
    std::vector<std::string> l;
    std::vector<std::pair<std::string, std::string>> D;

public:

    std::vector<ccsh::fs::path> include_directories() const override
    {
        return I;
    }
    std::vector<ccsh::fs::path> link_directories() const override
    {
        return L;
    }
    std::vector<std::string> link_libraries() const override
    {
        return l;
    }
    std::vector<std::pair<std::string, std::string>> definitions() const override
    {
        return D;
    }
};

}

#endif // CCBS_PACKAGE_FLAGS_HPP
