cmake_minimum_required(VERSION 3.10)
project(POCPlugin)

set(CMAKE_CXX_STANDARD 20)

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
include_directories(${SOURCES_DIR}/Plugins/GraphModule)


set(SOURCE_FILES
        PocEntryPoint.cpp
        PocGraphModule.cpp
        )

add_library(POCPlugin SHARED ${SOURCE_FILES})
target_include_directories(POCPlugin PRIVATE ${LIBCONFIG++_INCLUDE_DIRS})

target_link_libraries(POCPlugin PUBLIC PkgConfig::LIBCONFIG++ raytracer_lib)

