cmake_minimum_required(VERSION 3.10)
project(SpherePlugin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG++ REQUIRED IMPORTED_TARGET libconfig++)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include_directories(${SOURCES_DIR}/Shared/Geometry/Vec3)
include_directories(${SOURCES_DIR}/Shared/Geometry/Vec2)
include_directories(${SOURCES_DIR}/Shared/Geometry/Ray)
include_directories(${SOURCES_DIR}/Shared/)
include_directories(${SOURCES_DIR}/Shared/Materials)
include_directories(${SOURCES_DIR}/Entities)
include_directories(${SOURCES_DIR}/Shared/Utils/Errors)
include_directories(${SOURCES_DIR}/Entities/Primitives)
include_directories(${SOURCES_DIR}/Shared/Utils/Errors)
include_directories(${SOURCES_DIR}/Plugins/Primitives)
include_directories(${SOURCES_DIR}/Plugins/Decorator)
include_directories(${SOURCES_DIR}/Plugins/Light)


set(SOURCE_FILES
        Sphere.cpp
        Sphere.hpp
        SpheresEntryPoint.cpp
        ${SOURCES_DIR}/Plugins/AEntity.cpp)

add_library(SpherePlugin SHARED ${SOURCE_FILES})
target_include_directories(SpherePlugin PRIVATE ${LIBCONFIG++_INCLUDE_DIRS})

target_link_libraries(SpherePlugin PUBLIC PkgConfig::LIBCONFIG++ raytracer_lib)

