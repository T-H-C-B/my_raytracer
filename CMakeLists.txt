cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)

find_package(PkgConfig REQUIRED)

if (APPLE)
    pkg_check_modules(LIBCONFIG++ REQUIRED IMPORTED_TARGET libconfig++)
else()
    pkg_check_modules(PKGCONFIG_LIBCONFIG++ REQUIRED IMPORTED_TARGET libconfig++)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Geometry/Ray)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Geometry/Vec2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Geometry/Vec3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Materials)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Utils/Errors)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Core/Image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/Camera)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/GraphModule)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/Decorator)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/SkyBox)

set(SOURCE_FILES
        sources/main.cpp
        sources/Core/Loader/DynamicLibrary.cpp
        sources/Core/Loader/DynamicLibrary.hpp
        sources/Plugins/Camera/ACamera.hpp
        sources/Plugins/Primitives/APrimitive.hpp
        sources/Core/Scene.cpp
        sources/Core/Scene.hpp
        sources/Core/Image/Image.cpp
        sources/Core/Image/Image.hpp
        sources/Core/FactoryTemplate.hpp
        sources/Core/EventManager.cpp
        sources/Core/EventManager.hpp
        sources/Core/Core.cpp
        sources/Core/Core.hpp
        sources/Core/Loader/PluginLoader.cpp
        sources/Core/Loader/PluginLoader.hpp
        sources/Core/LibType.hpp)

add_executable(raytracer ${SOURCE_FILES})

add_subdirectory(sources/Shared)

target_link_libraries(raytracer PRIVATE raytracer_lib) # Use keyword signature here
if (APPLE)
    target_link_libraries(raytracer PRIVATE PkgConfig::LIBCONFIG++ ${CMAKE_DL_LIBS})
else()
    target_link_libraries(raytracer PRIVATE PkgConfig::PKGCONFIG_LIBCONFIG++ ${CMAKE_DL_LIBS})
endif()


link_directories(/opt/homebrew/Cellar/)
include_directories(/usr/local/include)


target_include_directories(raytracer PRIVATE ${LIBCONFIG++_INCLUDE_DIRS})
target_include_directories(raytracer PRIVATE ${PKGCONFIG_LIBCONFIG++_INCLUDE_DIRS})

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
