if (APPLE)
    find_path(Pybind11_DIR
            NAMES CMakeLists.txt
            HINTS ${PYBIND11_DIR}
            PATHS ${PYBIND11_DIR}
    )
endif ()


mark_as_advanced(Pybind11_DIR)

add_subdirectory("${Pybind11_DIR}" "${CMAKE_BINARY_DIR}/_deps/pybind11-subbuild" EXCLUDE_FROM_ALL)

set(pybind11_FOUND TRUE)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pybind11 REQUIRED_VARS pybind11_FOUND)