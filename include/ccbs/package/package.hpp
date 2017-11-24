#ifndef CCBS_PACKAGE_HPP
#define CCBS_PACKAGE_HPP

#include <ccbs/rule/timestamp.hpp>

#include <ccbs/compiler/compiler.hpp>

#include <ccsh/ccsh.hpp>

#include <memory>
#include <set>

namespace ccbs {

class package
{
public:
    virtual void prepare() = 0;

    virtual timestamp last_modified() const = 0;

    virtual std::vector<ccsh::fs::path> include_directories() const = 0;
    virtual std::vector<ccsh::fs::path> link_directories() const = 0;
    virtual std::vector<std::string> link_libraries() const = 0;

    virtual std::vector<std::pair<std::string, std::string>> definitions() const = 0;

    virtual std::set<package*> dependencies() const { return {}; }

    virtual void add_arguments(compiler&) const = 0;

    virtual ~package() = default;
};

}

#endif // CCBS_PACKAGE_HPP
