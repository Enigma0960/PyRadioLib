if(UNIX)
include(GNUInstallDirs)
endif ()

# Add radiolib
set(Radiolib_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/RadioLib")

if (NOT Radiolib_ROOT)
    message(FATAL_ERROR "Radiolib_ROOT not set and not found")
endif()


set(Radiolib_VERSION "")
if (EXISTS "${Radiolib_ROOT}/library.json")
    file(STRINGS "${Radiolib_ROOT}/library.json" _tmp REGEX "\"version\":")
    string(REGEX REPLACE "[ \t]*\"version\":[ \t]*\"" "" Radiolib_VERSION ${_tmp})
    string(REGEX REPLACE "\"," "" Radiolib_VERSION ${Radiolib_VERSION})
endif()
message(STATUS "Radiolib_VERSION = ${Radiolib_VERSION}")

set(COPY_SCRIPT "${CMAKE_BINARY_DIR}/copy_includes.cmake")
file(WRITE "${COPY_SCRIPT}" "file(MAKE_DIRECTORY \"${DEST_DIR}\")\n")
foreach (src ${SRC_FILES})
    get_filename_component(fname "${src}" NAME)
    file(APPEND "${COPY_SCRIPT}" "file(COPY \"${src}\" DESTINATION \"${DEST_DIR}\")\n")
endforeach ()


set(Radiolib_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include/radiolib")
set(Radiolib_SOURCE_DIR "${Radiolib_ROOT}/src")
collect_sources(${Radiolib_SOURCE_DIR} RADIOLIB_HEADERS RADIOLIB_SOURCES)

copy_headers(
        radiolib_include
        ${Radiolib_SOURCE_DIR}
        ${Radiolib_INCLUDE_DIR}
        ${RADIOLIB_HEADERS}
)

add_library(radiolib STATIC SHARED ${RADIOLIB_HEADERS} ${RADIOLIB_SOURCES})
add_dependencies(radiolib radiolib_include)
target_include_directories(radiolib SYSTEM PUBLIC ${Radiolib_INCLUDE_DIR})


# Add pybind11
set(Radiolib_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/pybind11")
add_subdirectory("${Radiolib_ROOT}" "${CMAKE_BINARY_DIR}/_deps/pybind11-subbuild" EXCLUDE_FROM_ALL)

include_directories(SYSTEM "${CMAKE_BINARY_DIR}/include/")

add_subdirectory(core)
add_subdirectory(mock)
add_subdirectory(py)
