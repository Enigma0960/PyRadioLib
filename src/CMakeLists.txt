# src/CMakeLists.txt — минимальный каркас проекта

# Интерфейсная билиотека с include-директориями (RadioLib + ваш src)
add_library(hal_iface INTERFACE)
target_include_directories(hal_iface INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${RADIOLIB_INCLUDE_DIR}         # заголовки RadioLib
)


add_subdirectory(tests)