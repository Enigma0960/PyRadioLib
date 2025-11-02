if (APPLE)
    find_path(Radiolib_DIR
            NAMES library.json
            HINTS ${RADIOLIB_DIR}
            PATHS ${RADIOLIB_DIR}
    )
    find_path(Radiolib_SOURCE_DIR
            NAMES RadioLib.h
            HINTS ${RADIOLIB_SOURCE_DIR}
            PATHS ${RADIOLIB_SOURCE_DIR}
    )
endif ()

mark_as_advanced(Radiolib_SOURCE_DIR)

collect_sources(${Radiolib_SOURCE_DIR} RADIOLIB_HEADERS RADIOLIB_SOURCES)

if (NOT Radiolib_VERSION AND EXISTS "${Radiolib_DIR}/library.json")
    file(STRINGS "${Radiolib_DIR}/library.json" RADIOLIV_VERSION_LINE REGEX "\"version\":")
    string(REGEX REPLACE "[ \t]*\"version\":[ \t]*\"" "" Radiolib_VERSION ${RADIOLIV_VERSION_LINE})
    string(REGEX REPLACE "\"," "" Radiolib_VERSION ${Radiolib_VERSION})
endif ()


set(COPY_SCRIPT "${CMAKE_BINARY_DIR}/copy_includes.cmake")
file(WRITE "${COPY_SCRIPT}" "file(MAKE_DIRECTORY \"${DEST_DIR}\")\n")
foreach (src ${SRC_FILES})
    get_filename_component(fname "${src}" NAME)
    file(APPEND "${COPY_SCRIPT}" "file(COPY \"${src}\" DESTINATION \"${DEST_DIR}\")\n")
endforeach ()

set(Radiolib_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include/radiolib")

copy_headers(
        radiolib_include
        ${Radiolib_SOURCE_DIR}
        ${Radiolib_INCLUDE_DIR}
        ${RADIOLIB_HEADERS}
)

add_library(radiolib STATIC SHARED ${RADIOLIB_HEADERS} ${RADIOLIB_SOURCES})
add_dependencies(radiolib radiolib_include)
target_include_directories(radiolib SYSTEM PRIVATE
        ${Radiolib_INCLUDE_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
        Radiolib
        REQUIRED_VARS Radiolib_INCLUDE_DIR
        VERSION_VAR Radiolib_VERSION
)
