project(PyRadioLib_test LANGUAGES CXX)

set(TEST_APP PyRadioLib_test)

include(FetchContent)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/googletest")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
set(INSTALL_GMOCK OFF)
FetchContent_MakeAvailable(googletest)

set_target_properties(gtest gtest_main gmock gmock_main PROPERTIES FOLDER extern)


add_executable(${TEST_APP} main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(${TEST_APP} PUBLIC GTest::gt est GTest::gmock)


include(GoogleTest)
gtest_discover_tests(${TEST_APP})