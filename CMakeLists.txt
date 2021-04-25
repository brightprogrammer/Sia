cmake_minimum_required(VERSION 3.2)

#version settings
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)

set(VERSION_NUMBER "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")

project(SIA VERSION ${VERSION_NUMBER})
message("-- VERSION NUMBER : " ${VERSION_NUMBER})

set(SIA_UTILS_DIR ${PROJECT_SOURCE_DIR}/utils)
set(SIA_COMPILER_DIR ${PROJECT_SOURCE_DIR}/compiler)

configure_file(Config.hpp.in ${PROJECT_SOURCE_DIR}/Config.hpp)

add_subdirectory(utils)
add_subdirectory(compiler)

add_executable(siac main.cpp)
target_include_directories(siac PRIVATE ${SIA_UTILS_DIR} ${SIA_COMPILER_DIR})
target_link_libraries(siac sia_utils)