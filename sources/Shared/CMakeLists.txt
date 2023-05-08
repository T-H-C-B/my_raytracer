cmake_minimum_required(VERSION 3.10)
project(raytracer_lib)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIGPP REQUIRED IMPORTED_TARGET libconfig++)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Ray)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Vec2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Vec3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Materials)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils/Errors)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Shared)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Wrapper)

set(SOURCE_FILES
        Geometry/Ray/Ray.cpp
        Geometry/Ray/Ray.hpp
        Geometry/Vec2/Vec2.cpp
        Geometry/Vec2/Vec2.hpp
        Geometry/Vec3/Vec3.cpp
        Geometry/Vec3/Vec3.hpp
        Materials/Material.cpp
        Materials/Material.hpp
        Intersection.hpp
        Utils/Errors/ConfigError.hpp
        Utils/Errors/CustomError.hpp
        Wrapper/ConfigWrapper.hpp
        Wrapper/ConfigWrapper.cpp
        Wrapper/SettingWrapper.hpp
        Wrapper/SettingWrapper.cpp)

add_library(raytracer_lib STATIC ${SOURCE_FILES})
target_link_libraries(raytracer_lib PRIVATE PkgConfig::LIBCONFIGPP)
