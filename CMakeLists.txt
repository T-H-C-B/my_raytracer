cmake_minimum_required(VERSION 3.10)
project(raytracing)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PKGCONFIG_LIBCONFIG++ REQUIRED IMPORTED_TARGET libconfig++)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Geometry/Ray)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Geometry/Vec2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Geometry/Vec3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Materials)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Utils/Errors)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Core/Image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/Camera)

set(SOURCE_FILES
        sources/Core/Loader/DynamicLibrary.cpp
        sources/Core/Loader/DynamicLibrary.hpp
        sources/Core/Loader/SceneLoader.cpp
        sources/Core/Loader/SceneLoader.hpp
        sources/Plugins/Camera/ACamera.hpp
        sources/Plugins/Primitives/APrimitive.hpp
        sources/Core/Scene.cpp
        sources/Core/Scene.hpp
        sources/Core/Image/Image.cpp
        sources/Core/Image/Image.hpp)

add_executable(raytracing ${SOURCE_FILES})

add_subdirectory(sources/Shared)

target_link_libraries(raytracing raytracer_lib)
target_link_libraries(raytracing ${PKGCONFIG_LIBCONFIG++_LIBRARIES})
target_link_libraries(raytracing ${CMAKE_DL_LIBS})

target_include_directories(raytracing PRIVATE ${LIBCONFIG++_INCLUDE_DIRS})
target_include_directories(raytracing PRIVATE ${PKGCONFIG_LIBCONFIG++_INCLUDE_DIRS})

file(GLOB PRIMITIVE_DIRS "sources/Plugins/Primitives/*")
foreach(subdir ${PRIMITIVE_DIRS})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()

file(GLOB CAMERA_DIRS "sources/Plugins/Camera/*")
foreach(subdir ${CAMERA_DIRS})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()

file(GLOB LIGHT_DIRS "sources/Plugins/Lights/*")
foreach(subdir ${LIGHT_DIRS})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()
