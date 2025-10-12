collect_sources(${CMAKE_CURRENT_SOURCE_DIR} CORE_SOURCES CORE_HEADERS)

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
add_library(PyRadioLib::core ALIAS core)

set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(core
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(core PUBLIC cxx_std_20)