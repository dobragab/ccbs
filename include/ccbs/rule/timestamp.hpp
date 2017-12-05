#ifndef CCBS_TIMESTAMP_HPP
#define CCBS_TIMESTAMP_HPP

#include <ctime>

#include <ccsh/ccsh_filesystem.hpp>

namespace ccbs {

#ifdef CCSH_FILESYSTEM_BOOST

using timestamp = std::time_t;

inline timestamp to_timestamp(std::time_t t)
{
    return t;
}
inline std::time_t to_time_t(timestamp t)
{
    return t;
}

#else

using timestamp = ccsh::fs::file_time_type;

inline timestamp to_timestamp(std::time_t t)
{
    return timestamp::clock::from_time_t(t);
}
inline std::time_t to_time_t(timestamp t)
{
    return timestamp::clock::to_time_t(t);
}

#endif

}

#endif // CCBS_TIMESTAMP_HPP
