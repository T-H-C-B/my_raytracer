cmake_minimum_required(VERSION 3.10)
project(AmbientLightPlugin)

set(CMAKE_CXX_STANDARD 14)

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
        AmbientLight.cpp
        AmbientLight.hpp
        AmbientLightEntryPoint.cpp
        ${SOURCES_DIR}/Plugins/AEntity.cpp)

add_library(AmbientLightPlugin SHARED ${SOURCE_FILES})
target_include_directories(AmbientLightPlugin PRIVATE ${LIBCONFIG++_INCLUDE_DIRS})

target_link_libraries(AmbientLightPlugin PUBLIC PkgConfig::LIBCONFIG++ raytracer_lib)
