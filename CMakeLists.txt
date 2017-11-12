cmake_minimum_required (VERSION 2.6)

add_subdirectory(./../ccsh ccsh EXCLUDE_FROM_ALL)

include_directories(../ccsh/include)
include_directories(../ccsh/wrappers)

include_directories("include")

file(GLOB_RECURSE headers include/*.hpp)
file(GLOB_RECURSE sources lib/*.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # ensure C++11

add_executable(ccbs ${sources} ${headers})
target_link_libraries(ccbs PUBLIC ccsh_lib ${filesystem_lib})
