cmake_minimum_required(VERSION 3.22)

# ---- Проект ---------------------------------------------------------------
project(PyRadioLib VERSION 0.1.0 LANGUAGES CXX C)

# ---- Политики для современного поведения ---------------------------------
# (Опционально, но полезно для новых возможностей)
if (POLICY CMP0135) # FetchContent - более предсказуемое поведение
    cmake_policy(SET CMP0135 NEW)
endif ()

# ---- Опции проекта --------------------------------------------------------
option(BUILD_PY_MODULE "Build Python extension module (pybind11)" ON)
option(BUILD_TESTING "Build C++ tests" ON)
option(HAL_BACKEND_MOCK "Use MOCK HAL backend" ON)
option(HAL_BACKEND_RPI "Use RPI  HAL backend" OFF)
option(USE_SYSTEM_PYBIND11 "Find pybind11 via find_package" OFF)
option(USE_SYSTEM_RADIOLIB "Use system-installed RadioLib" OFF)

# Взаимоисключающие опции HAL
if (HAL_BACKEND_MOCK AND HAL_BACKEND_RPI)
    message(FATAL_ERROR "Choose only one HAL backend: MOCK or RPI.")
endif ()
if (NOT HAL_BACKEND_MOCK AND NOT HAL_BACKEND_RPI)
    message(STATUS "No HAL backend chosen explicitly, defaulting to MOCK")
    set(HAL_BACKEND_MOCK ON)
endif ()

# ---- Язык и компилятор ----------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # полезно и для shared, и для python-модулей

if (MSVC)
    add_compile_options(/W4 /permissive-)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# ---- Зависимости: RadioLib и pybind11 ------------------------------------
# Ожидаем, что исходники лежат в thirdparty/, но даём возможность использовать системные
include(FetchContent)

# RadioLib
if (USE_SYSTEM_RADIOLIB)
    # если есть find_package(RadioLib CONFIG) — можно добавить; у RadioLib обычно нет такого конфига.
    message(FATAL_ERROR "System RadioLib is not supported in this template. Use thirdparty submodule.")
else ()
    # Подразумевается, что у вас добавлен git submodule thirdparty/RadioLib
    add_subdirectory(thirdparty/RadioLib)
endif ()

# pybind11
if (BUILD_PY_MODULE)
    if (USE_SYSTEM_PYBIND11)
        find_package(pybind11 CONFIG REQUIRED)  # например, v2.11+
    else ()
        # Подразумевается submodule thirdparty/pybind11
        add_subdirectory(thirdparty/pybind11)
    endif ()
endif ()

# ---- Глобальные дефайны для выбора HAL ------------------------------------
if (HAL_BACKEND_MOCK)
    add_compile_definitions(RLRPI_HAL_BACKEND_MOCK=1)
elseif (HAL_BACKEND_RPI)
    add_compile_definitions(RLRPI_HAL_BACKEND_RPI=1)
endif ()

# ---- Подпроект с исходниками ----------------------------------------------
# ВАЖНО: Весь C++-код, включая библиотеки, биндинги и тесты — в папке src
add_subdirectory(src)

# ---- Тестирование (ctest) -------------------------------------------------
include(CTest) # выставит BUILD_TESTING при необходимости
if (BUILD_TESTING)
    enable_testing()
    # Таргеты тестов объявляйте в src/CMakeLists.txt через add_test(...)
endif ()

# ---- Вывод конфигурации ---------------------------------------------------
message(STATUS "========== radiolib_rpi build config ==========")
message(STATUS "CMAKE_BUILD_TYPE     : ${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_PY_MODULE      : ${BUILD_PY_MODULE}")
message(STATUS "BUILD_TESTING        : ${BUILD_TESTING}")
message(STATUS "HAL_BACKEND_MOCK     : ${HAL_BACKEND_MOCK}")
message(STATUS "HAL_BACKEND_RPI      : ${HAL_BACKEND_RPI}")
message(STATUS "USE_SYSTEM_PYBIND11  : ${USE_SYSTEM_PYBIND11}")
message(STATUS "USE_SYSTEM_RADIOLIB  : ${USE_SYSTEM_RADIOLIB}")
message(STATUS "================================================")
