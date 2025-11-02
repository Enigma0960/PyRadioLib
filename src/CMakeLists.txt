
set(RADIOLIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/RadioLib")
set(RADIOLIB_SOURCE_DIR "${RADIOLIB_DIR}/src/" CACHE PATH "RadioLib source path")
find_package(Radiolib REQUIRED)

find_package(pybind11 QUIET CONFIG)
if (NOT pybind11_FOUND)
    set(PYBIND11_DIR "${CMAKE_SOURCE_DIR}/thirdparty/pybind11")
    find_package(pybind11 REQUIRED)
endif ()

include_directories(SYSTEM ${CMAKE_BINARY_DIR}/include/ )

add_subdirectory(core)
add_subdirectory(mock)
add_subdirectory(py)
