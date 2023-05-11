cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(libconfig++ REQUIRED)
include_directories(${LIBCONFIG++_INCLUDE_DIRS})
link_directories(${LIBCONFIG++_LIBRARY_DIRS})

# Set output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)



if (APPLE)
else()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Core/Loader)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/Camera)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/GraphModule)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/Decorator)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/SkyBox)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/Primitives)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Plugins/Lights)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/Shared/Wrapper)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources)

set(SOURCE_FILES
        sources/main.cpp
        sources/Core/Loader/DynamicLibrary.cpp
        sources/Core/Loader/DynamicLibrary.hpp
        sources/Core/SceneManager.cpp
        sources/Core/SceneManager.hpp
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
        sources/Plugins/PluginType.hpp)

add_executable(raytracer ${SOURCE_FILES})

add_subdirectory(sources/Shared)

target_link_libraries(raytracer PRIVATE raytracer_lib)
if (APPLE)
    target_link_libraries(raytracer PRIVATE  ${CMAKE_DL_LIBS})
else()
target_link_libraries(raytracer PRIVATE raytracer_lib Threads::Threads ${LIBCONFIG++_LIBRARIES} ${CMAKE_DL_LIBS})
endif()


link_directories(/opt/homebrew/Cellar/)
include_directories(/usr/local/include)


if (NOT APPLE)
    target_link_libraries(raytracer PRIVATE Threads::Threads)
endif()


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

file(GLOB SKYBOX_DIRS "sources/Plugins/SkyBox/*")
foreach(subdir ${SKYBOX_DIRS})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()

file(GLOB GRAPHMODULE_DIRS "sources/Plugins/GraphModule/*")
foreach(subdir ${GRAPHMODULE_DIRS})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()

file (GLOB DECORATOR_DIRS "sources/Plugins/Decorator/*")
foreach(subdir ${DECORATOR_DIRS})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()