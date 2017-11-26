#ifndef PROJECT_COMPILER_HPP
#define PROJECT_COMPILER_HPP

#include <ccsh/ccsh.hpp>
#include <ccbs/util/polymorphic_value.hpp>

namespace ccbs
{

class compiler
{
public:
    virtual ~compiler() = default;

    virtual ccsh::internal::command_native& native() = 0;
    virtual ccsh::internal::command_native const& native() const = 0;

    int run() { return native().run(); }

    enum std_
    {
        cpp98,
        cpp03,
        cpp11,
        cpp14,
        cpp17,
    };

    virtual void input(ccsh::fs::path const&) = 0;
    virtual void output(ccsh::fs::path const&) = 0;

    virtual void std_version(std_ std1) = 0;

    virtual void include_directory(ccsh::fs::path const&) = 0;
    virtual void link_directory(ccsh::fs::path const&) = 0;
    virtual void link_library(std::string const&) = 0;

    virtual void definition(std::string const&, std::string const&) = 0;

    virtual void object_so() = 0;
    virtual void object() = 0;
    virtual void dependency() = 0;
    virtual void shared_object() = 0;
};

template<typename Impl>
class compiler_t : public compiler
{
    ccsh::command_builder<Impl> impl_;

public:
    explicit compiler_t(ccsh::command_builder<Impl> impl)
        : impl_(std::move(impl))
    { }

    ccsh::internal::command_native& native() override { return impl_; }
    ccsh::internal::command_native const& native() const override { return impl_; }

    ccsh::command_builder<Impl>& impl() { return impl_; }
    ccsh::command_builder<Impl> const& impl() const { return impl_; }
};

using compiler_ptr = jbcoe::polymorphic_value<compiler>;

}

#endif //PROJECT_COMPILER_HPP
