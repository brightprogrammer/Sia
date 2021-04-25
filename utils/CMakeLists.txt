file(GLOB_RECURSE sia_utils_sources ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(sia_utils ${sia_utils_sources})