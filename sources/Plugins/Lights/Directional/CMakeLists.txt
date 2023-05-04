cmake_minimum_required(VERSION 3.10)
project(DirectionalLightPlugin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG++ REQUIRED IMPORTED_TARGET libconfig++)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include_directories(${SOURCES_DIR}/Shared/Geometry/Vec3)
include_directories(${SOURCES_DIR}/Shared/Geometry/Vec2)
include_directories(${SOURCES_DIR}/Shared/Geometry/Ray)
include_directories(${SOURCES_DIR}/Shared/)
include_directories(${SOURCES_DIR}/Shared/Materials)
include_directories(${SOURCES_DIR}/Shared/Utils/Errors)
include_directories(${SOURCES_DIR}/Plugins/Lights)
include_directories(${SOURCES_DIR}/Plugins)


set(SOURCE_FILES
        DirectionalLight.cpp
        DirectionalLight.hpp
        DirectionalLightEntryPoint.cpp
        ${SOURCES_DIR}/Plugins/AEntity.cpp)

add_library(DirectionalLightPlugin SHARED ${SOURCE_FILES})
target_include_directories(DirectionalLightPlugin PRIVATE ${LIBCONFIG++_INCLUDE_DIRS})

target_link_libraries(DirectionalLightPlugin PUBLIC PkgConfig::LIBCONFIG++ raytracer_lib)
