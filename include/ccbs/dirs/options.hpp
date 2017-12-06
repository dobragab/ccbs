#ifndef PROJECT_OPTIONS_HPP
#define PROJECT_OPTIONS_HPP

#include <unordered_map>
#include <string>

namespace ccbs {

using options = std::unordered_map<std::string, std::string>;

options parse_options(int argc, const char** argv);

namespace config {

static constexpr const char* key = "CONFIG";

static constexpr const char* debug = "debug";
static constexpr const char* release = "release";

}

}

#endif //PROJECT_OPTIONS_HPP
