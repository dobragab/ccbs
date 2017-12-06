cmake_minimum_required (VERSION 2.6)

set(SHARED_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(SHARED_LIB_INCLUDE_DIR ${SHARED_LIB_INCLUDE_DIR} PARENT_SCOPE)

if(NOT TARGET ccbs_lib) # "include guard"

file(GLOB_RECURSE headers ../include/*.hpp)
file(GLOB_RECURSE sources *.cpp)

add_library(ccbs_lib SHARED ${sources} ${headers})
target_link_libraries(ccbs_lib PUBLIC ccsh_lib ${filesystem_lib})

endif()
