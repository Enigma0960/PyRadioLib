
set(RADIOLIB_HOME_DIR "${CMAKE_SOURCE_DIR}/thirdparty/RadioLib")
set(RADIOLIB_SOURCE_DIR "${RADIOLIB_HOME_DIR}/src/" CACHE PATH "RadioLib source path")


find_package(radiolib REQUIRED)

if (Radiolib_FOUND)

    message("Radiolib version: ${Radiolib_VERSION}")

endif ()