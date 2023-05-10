cmake_minimum_required(VERSION 3.10)
project(TorusPlugin)

set(CMAKE_CXX_STANDARD 20)

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
include_directories(${SOURCES_DIR}/Shared/Wrapper)

set(SOURCE_FILES
        Torus.cpp
        Torus.hpp
        TorusEntryPoint.cpp
        ${SOURCES_DIR}/Plugins/AEntity.cpp)

add_library(TorusPlugin SHARED ${SOURCE_FILES})
target_link_libraries(TorusPlugin PUBLIC  raytracer_lib)

