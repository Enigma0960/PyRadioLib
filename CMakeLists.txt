cmake_minimum_required(VERSION 3.22)

project(PyRadioLib VERSION 0.1.0 LANGUAGES CXX C)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

cmake_policy(SET CMP0156 NEW)
cmake_policy(SET CMP0159 NEW)

include(CollectSources)
include(CopyHeaders)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#set(CMAKE_MESSAGE_CONTEXT_SHOW ON)
#set(CMAKE_FIND_DEBUG_MODE ON)
#set(CMAKE_FIND_USE_PACKAGE_ROOT_PATH ON)

find_package(Python3 3.11 REQUIRED COMPONENTS Interpreter Development Development.Module)

add_subdirectory(src)

if (BUILD_TESTING)
    include(CTest)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF)
    set(RADIOLIB_LIBRARY_TYPE STATIC CACHE STRING "" FORCE)
    add_subdirectory(thirdparty/googletest)
    add_subdirectory(tests)
endif ()