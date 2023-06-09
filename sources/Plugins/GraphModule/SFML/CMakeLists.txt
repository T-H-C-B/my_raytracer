cmake_minimum_required(VERSION 3.10)
project(SFMLPlugin)

set(CMAKE_CXX_STANDARD 20)



find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include_directories(${SOURCES_DIR}/Shared/Geometry/Vec3)
include_directories(${SOURCES_DIR}/Shared/Geometry/Vec2)
include_directories(${SOURCES_DIR}/Shared/Geometry/Ray)
include_directories(${SOURCES_DIR}/Shared/)
include_directories(${SOURCES_DIR}/Shared/Materials)
include_directories(${SOURCES_DIR}/Entities)
include_directories(${SOURCES_DIR}/Shared/Utils/Errors)
include_directories(${SOURCES_DIR}/Plugins/GraphModule)
include_directories(${SOURCES_DIR}/Shared/Wrapper)


set(SOURCE_FILES
        SFMLGraphModule.cpp
        SFMLGraphModule.hpp
        SFMLKeyEventMap.hpp
        SFMLEntryPoint.cpp
        ${SOURCES_DIR}/Core/EventManager.cpp
        )

add_library(SFMLPlugin SHARED ${SOURCE_FILES})

target_link_libraries(SFMLPlugin PUBLIC raytracer_lib sfml-graphics sfml-audio)

