cmake_minimum_required (VERSION 2.6)

add_subdirectory(./../ccsh ccsh EXCLUDE_FROM_ALL)

include_directories(../ccsh/include)
include_directories(../ccsh/wrappers)

file(GLOB_RECURSE headers *.hpp)
file(GLOB sources *.cpp target/*.cpp package/*.cpp rule/*.cpp)

add_executable(ccbs ${sources} ${headers})
target_link_libraries(ccbs PUBLIC ccsh_lib ${filesystem_lib})
