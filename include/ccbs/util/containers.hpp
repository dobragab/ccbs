#ifndef PROJECT_CONTAINERS_HPP
#define PROJECT_CONTAINERS_HPP

#include <vector>

namespace ccbs
{

template<typename T>
std::vector<T>& merge_vectors(std::vector<T>& target_, std::vector<T> items_)
{
    target_.reserve(target_.size() + items_.size());
    while (!items_.empty())
    {
        target_.push_back(std::move(items_.back()));
        items_.pop_back();
    }
    return target_;
}

}

#endif //PROJECT_CONTAINERS_HPP
