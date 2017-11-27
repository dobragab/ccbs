#ifndef PROJECT_VISITORS_HPP
#define PROJECT_VISITORS_HPP

#include <utility>

namespace ccbs
{

namespace detail
{

template<typename Func>
class call_arg
{
    template<typename Arg>
    static Arg f(void (Func::*)(Arg&) const);

public:
    using type = decltype(f(&Func::operator()));
};

} // namespace detail

template<typename Base, typename Func>
bool visit_one(Base& base, Func&& func)
{
    using Derived = typename detail::call_arg<Func>::type;
    auto * ptr = dynamic_cast<Derived*>(&base);
    if (ptr)
    {
        func(*ptr);
        return true;
    }
    return false;
}

namespace detail
{

template<typename Base>
bool visit_all_impl(Base& base)
{
    return false;
}

template<typename Base, typename FuncHead, typename... FuncTail>
bool visit_all_impl(Base& base, FuncHead&& funcHead, FuncTail&&... funcTail)
{
    return visit_one(base, std::forward<FuncHead>(funcHead)) || visit_all_impl(base, std::forward<FuncTail>(funcTail)...);
}

} // namespace detail

template<typename Base, typename... Func>
bool visit_all(Base& base, Func&&... func)
{
    return detail::visit_all_impl(base, std::forward<Func>(func)...);
}


}


#endif //PROJECT_VISITORS_HPP
