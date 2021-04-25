cmake_minimum_required(VERSION 3.2)

#version settings
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)

set(VERSION_NUMBER "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")

project(SIA VERSION ${VERSION_NUMBER})
message("-- VERSION NUMBER : " ${VERSION_NUMBER})

configure_file(Config.hpp.in ${PROJECT_SOURCE_DIR}/sia/Config.hpp)

add_subdirectory(utils)

add_executable(sia main.cpp)
target_include_directories(sia PRIVATE ${PROJECT_SOURCE_DIR}/sia ${PROJECT_SOURCE_DIR}/utils)
target_link_libraries(sia sia_utils)