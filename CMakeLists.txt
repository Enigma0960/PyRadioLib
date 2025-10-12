cmake_minimum_required(VERSION 3.22)

project(PyRadioLib VERSION 0.1.0 LANGUAGES CXX C)

include(cmake/FindSources.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


set(RADIOLIB_LIBRARY_TYPE "SHARED" CACHE STRING "Library type for RadioLib (STATIC or SHARED)")
set_property(CACHE RADIOLIB_LIBRARY_TYPE PROPERTY STRINGS STATIC SHARED)


set(SRC_ROOT "${CMAKE_SOURCE_DIR}/src")
set(RADIOLIB_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/RadioLib")

if (EXISTS "${RADIOLIB_ROOT}")
    collect_sources("${RADIOLIB_ROOT}/src" RADIOLIB_SOURCES RADIOLIB_HEADERS)

    add_custom_target(radiolib_include ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${RADIOLIB_ROOT}/src"
            "${CMAKE_BINARY_DIR}/include/radiolib"
    )

    add_library(radiolib ${RADIOLIB_LIBRARY_TYPE} ${RADIOLIB_SOURCES} ${RADIOLIB_HEADERS})
    add_dependencies(radiolib radiolib_include)

    target_include_directories(radiolib PUBLIC "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>")
    target_compile_features(radiolib PUBLIC cxx_std_20)
endif ()

if (TARGET radiolib)
    add_library(PyRadioLib::radiolib ALIAS radiolib)
endif ()

set(PYBIND11_FINDPYTHON ON)
add_subdirectory(thirdparty/pybind11)

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