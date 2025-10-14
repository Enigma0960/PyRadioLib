project(PyRadioLibTest LANGUAGES CXX C)

set(TEST_APP radiolib_test)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
set(INSTALL_GMOCK OFF)

set_target_properties(gtest gtest_main PROPERTIES FOLDER extern)

collect_sources("." TEST_SOURCES TEST_HEADERS)

add_executable(${TEST_APP} main.cpp ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(${TEST_APP} PUBLIC gtest)
target_link_libraries(${TEST_APP} PUBLIC
        PyRadioLib::radiolib
        PyRadioLib::core
        PyRadioLib::mock
)

include(GoogleTest)
gtest_discover_tests(${TEST_APP})
