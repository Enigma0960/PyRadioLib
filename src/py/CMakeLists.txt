collect_sources(${CMAKE_CURRENT_SOURCE_DIR} MODULE_SOURCES MODULE_HEADERS)

set(MODULE_NAME "pyradiolib")

pybind11_add_module(${MODULE_NAME} ${MODULE_SOURCES} ${MODULE_HEADERS})
target_link_libraries(${MODULE_NAME} PRIVATE
        PyRadioLib::core
        PyRadioLib::mock
        PyRadioLib::radiolib
)
target_include_directories(${MODULE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${RADIOLIB_INCLUDE_DIR}
)

if (WIN32)
    set_target_properties(${MODULE_NAME} PROPERTIES SUFFIX ".pyd")
endif ()

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${MODULE_NAME}")

set_target_properties(${MODULE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
)

foreach (_cfg IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER "${_cfg}" _CFG)
    set_target_properties(${MODULE_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${_CFG} "${OUTPUT_DIR}"
            LIBRARY_OUTPUT_DIRECTORY_${_CFG} "${OUTPUT_DIR}"
            ARCHIVE_OUTPUT_DIRECTORY_${_CFG} "${OUTPUT_DIR}"
    )
endforeach ()

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/pkg/__init__.py.in"
        "${CMAKE_BINARY_DIR}/generated/__init__.py"
        @ONLY
)

add_custom_command(
        TARGET ${MODULE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/generated/__init__.py"
        "${OUTPUT_DIR}/__init__.py"
        COMMENT "Placing Python package 'pyradiolib' next to compiled module"
        VERBATIM
)

find_package(Python3 COMPONENTS Interpreter QUIET)

if (Python3_Interpreter_FOUND)
    add_custom_command(
            TARGET ${MODULE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env
            "PYTHONPATH=$<TARGET_FILE_DIR:${MODULE_NAME}>"
            ${Python3_EXECUTABLE} -m pybind11_stubgen pyradiolib
            -o "$<TARGET_FILE_DIR:${MODULE_NAME}>"
            COMMENT "Generating pyradiolib.pyi with pybind11-stubgen"
            VERBATIM
    )
endif ()