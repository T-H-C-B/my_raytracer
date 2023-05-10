cmake_minimum_required(VERSION 3.10)
project(PNGDecorator)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include_directories(${SOURCES_DIR}/Shared/Geometry/Vec3)
include_directories(${SOURCES_DIR}/Shared/Geometry/Vec2)
include_directories(${SOURCES_DIR}/Shared/Geometry/Ray)
include_directories(${SOURCES_DIR}/Shared/)
include_directories(${SOURCES_DIR}/Shared/Materials)
include_directories(${SOURCES_DIR}/Entities)
include_directories(${SOURCES_DIR}/Shared/Utils/Errors)
include_directories(${SOURCES_DIR}/Plugins/GraphModule)
include_directories(${SOURCES_DIR}/Plugins/Primitives/Plane)
include_directories(${SOURCES_DIR}/Plugins/)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

set(SOURCE_FILES
        PNGDecorator.cpp
        PNGDecoratorEntryPoint.cpp
        PNGDecorator.hpp

        )

add_library(PNGDecorator SHARED ${SOURCE_FILES})

target_link_libraries(PNGDecorator PUBLIC raytracer_lib ${PNG_LIBRARY})

