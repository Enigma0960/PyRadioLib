collect_sources(${CMAKE_CURRENT_SOURCE_DIR} MOCK_SOURCES MOCK_HEADERS)

add_library(mock STATIC ${MOCK_SOURCES} ${MOCK_HEADERS})
add_library(PyRadioLib::mock ALIAS mock)

set_target_properties(mock PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(mock SYSTEM PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(mock PUBLIC cxx_std_20)
target_link_libraries(mock PUBLIC PyRadioLib::core radiolib)