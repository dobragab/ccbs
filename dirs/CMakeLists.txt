cmake_minimum_required (VERSION 2.6)

add_executable(ccbs-dirs main.cpp)
target_link_libraries(ccbs-dirs PUBLIC ccsh_lib ${filesystem_lib})
