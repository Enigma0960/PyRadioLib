set(MODULE_NAME "pyradiolib")

collect_sources(${CMAKE_CURRENT_SOURCE_DIR}  MODULE_HEADERS MODULE_SOURCES)

pybind11_add_module(${MODULE_NAME} ${MODULE_SOURCES} ${MODULE_HEADERS})

target_link_libraries(${MODULE_NAME} PRIVATE
        radiolib
        PyRadioLib::core
        PyRadioLib::mock
)
target_include_directories(${MODULE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)



#add_library(${MODULE_BINDINGS_NAME} OBJECT SHARED ${MODULE_SOURCES} ${MODULE_HEADERS})
#target_include_directories(${MODULE_BINDINGS_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(${MODULE_BINDINGS_NAME} PRIVATE
#        radiolib
#        PyRadioLib::core
#        PyRadioLib::mock
#)
#target_link_libraries(${MODULE_BINDINGS_NAME} PRIVATE pybind11::module)
#
#target_include_directories(${MODULE_BINDINGS_NAME} PRIVATE ${Python3_INCLUDE_DIRS})
#target_link_libraries(${MODULE_BINDINGS_NAME} PRIVATE ${Python3_LIBRARIES})
#
#pybind11_add_module(${MODULE_NAME} $<TARGET_OBJECTS:${MODULE_BINDINGS_NAME}>)
#
#if (APPLE)
#    target_link_options(${MODULE_NAME} PRIVATE
#            -Wl,-dead_strip
#    )
#endif ()
#
#if (WIN32)
#    set_target_properties(${MODULE_NAME} PROPERTIES SUFFIX ".pyd")
#endif ()
#
#set_target_properties(${MODULE_NAME} PROPERTIES
#        BUILD_RPATH "$ORIGIN"                # искать рядом с модулем
#        INSTALL_RPATH "@loader_path"         # на инсталле — рядом с модулем
#)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${MODULE_NAME}")

set_target_properties(${MODULE_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"
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


add_custom_command(
        TARGET ${MODULE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E env
        "PYTHONPATH=$<TARGET_FILE_DIR:${MODULE_NAME}>"
        ${Python3_EXECUTABLE} -m pybind11_stubgen ${MODULE_NAME}
        -o "$<TARGET_FILE_DIR:${MODULE_NAME}>"
        WORKING_DIRECTORY $<TARGET_FILE_DIR:${MODULE_NAME}>
        COMMENT "Generating pyradiolib with pybind11-stubgen"
        VERBATIM
)
