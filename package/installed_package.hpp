#ifndef PROJECT_INSTALLED_PACKAGE_HPP
#define PROJECT_INSTALLED_PACKAGE_HPP

#include "package_flags.hpp"

namespace ccbs
{

class installed_package : public package_flags
{
    ccsh::fs::path basedir_;
public:
    explicit installed_package(ccsh::fs::path basedir_ = ccsh::fs::path("/usr"), std::vector<std::string> libraries = {});

    ccsh::fs::path& basedir() { return basedir_; }
    ccsh::fs::path const& basedir() const { return basedir_; }

    void prepare() override {}
    timestamp last_modified() const override
    {
        // TODO: find latest library
        return timestamp(0);
    }
};

}

#endif //PROJECT_INSTALLED_PACKAGE_HPP
