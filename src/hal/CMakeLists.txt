collect_sources(${CMAKE_CURRENT_SOURCE_DIR} HAL_SOURCES HAL_HEADERS)

add_library(hal STATIC ${HAL_SOURCES} ${HAL_HEADERS})
add_library(PyRadioLib::hal ALIAS hal)

set_target_properties(hal PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(hal
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(hal PUBLIC cxx_std_20)

target_link_libraries(hal PUBLIC
        PyRadioLib::radiolib
)