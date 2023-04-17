cmake_minimum_required(VERSION 3.10)
project(raytracer_lib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Ray)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Vec2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Vec3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Materials)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils/Errors)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils/Image)

set(SOURCE_FILES
        Geometry/Ray/Ray.cpp
        Geometry/Ray/Ray.hpp
        Geometry/Vec2/Vec2.cpp
        Geometry/Vec2/Vec2.hpp
        Geometry/Vec3/Vec3.cpp
        Geometry/Vec3/Vec3.hpp
        Intersection.hpp
        Materials/IMaterial.hpp
        Utils/Errors/ConfigError.hpp
        Utils/Errors/CustomError.hpp
        Utils/Image/Image.cpp
        Utils/Image/Image.hpp)

add_library(raytracer_lib STATIC ${SOURCE_FILES})
