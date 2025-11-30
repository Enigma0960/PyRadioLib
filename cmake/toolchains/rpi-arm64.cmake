# cmake/toolchains/rpi-arm64.cmake

# Целевая система
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Кросс-компиляторы
set(CMAKE_C_COMPILER   aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# Sysroot внутри контейнера
set(RPI_SYSROOT "/opt/rpi-sysroot")
set(CMAKE_SYSROOT "${RPI_SYSROOT}")

# CMake должен всё искать внутри sysroot
set(CMAKE_FIND_ROOT_PATH "${RPI_SYSROOT}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Настройки для pkg-config
set(ENV{PKG_CONFIG_SYSROOT_DIR} "${RPI_SYSROOT}")
set(ENV{PKG_CONFIG_LIBDIR} "${RPI_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig:${RPI_SYSROOT}/usr/share/pkgconfig")

set(Python3_ROOT_DIR "${CMAKE_SYSROOT}/usr" CACHE PATH "Python3 root in sysroot")
set(Python3_INCLUDE_DIR "${CMAKE_SYSROOT}/usr/include/python3.13" CACHE PATH "")
set(Python3_LIBRARY     "${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/libpython3.13.so" CACHE FILEPATH "")

set(IS_CROSSCOMPILING ON)