cmake_minimum_required(VERSION 3.10)
project(MultipleDirectionalLightPlugin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)




set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include_directories(${SOURCES_DIR}/Shared/Geometry/Vec3)
include_directories(${SOURCES_DIR}/Shared/Geometry/Vec2)
include_directories(${SOURCES_DIR}/Shared/Geometry/Ray)
include_directories(${SOURCES_DIR}/Shared/)
include_directories(${SOURCES_DIR}/Shared/Materials)
include_directories(${SOURCES_DIR}/Shared/Utils/Errors)
include_directories(${SOURCES_DIR}/Plugins/Lights)
include_directories(${SOURCES_DIR}/Plugins)
include_directories(${SOURCES_DIR}/Shared/Wrapper)
include_directories(${SOURCES_DIR}/Plugins/Lights/Directional)

set(SOURCE_FILES
        MultipleDirectionalLight.cpp
        MultipleDirectionalLight.hpp
        MultipleLightEntryPoint.cpp
        ${SOURCES_DIR}/Plugins/Lights/Directional/DirectionalLight.cpp
        ${SOURCES_DIR}/Plugins/Lights/Directional/DirectionalLight.hpp
        ${SOURCES_DIR}/Plugins/AEntity.cpp)

add_library(MultipleDirectionalLightPlugin SHARED ${SOURCE_FILES})

target_link_libraries(MultipleDirectionalLightPlugin PUBLIC raytracer_lib)
