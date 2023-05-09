cmake_minimum_required(VERSION 3.10)
project(BasicCameraPlugin)

set(CMAKE_BUILD_TYPE Debug)




set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include_directories(${SOURCES_DIR}/Shared/Geometry/Vec3)
include_directories(${SOURCES_DIR}/Shared/Geometry/Vec2)
include_directories(${SOURCES_DIR}/Shared/Geometry/Ray)
include_directories(${SOURCES_DIR}/Shared/)
include_directories(${SOURCES_DIR}/Shared/Materials)
include_directories(${SOURCES_DIR}/Entities)
include_directories(${SOURCES_DIR}/Entities/Camera)
include_directories(${SOURCES_DIR}/Entities/Primitives)
include_directories(${SOURCES_DIR}/Shared/Utils/Errors)
include_directories(${SOURCES_DIR}/Shared/Wrapper)


set(SOURCE_FILES
        BasicCamera.cpp
        BasicCamera.hpp
        BasicCameraEntryPoint.cpp
        BasicCameraEntryPoint.cpp
        ${SOURCES_DIR}/Plugins/AEntity.cpp
        ${SOURCES_DIR}/Plugins/Camera/ACamera.cpp)

add_library(BasicCameraPlugin SHARED ${SOURCE_FILES})

target_link_libraries(BasicCameraPlugin PUBLIC raytracer_lib)
