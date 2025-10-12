cmake_minimum_required(VERSION 3.22)

# ---- Проект ---------------------------------------------------------------
project(PyRadioLib VERSION 0.1.0 LANGUAGES CXX C)

# ---- Политики -------------------------------------------------------------
if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif ()

# ---- Опции проекта --------------------------------------------------------
option(BUILD_PY_MODULE         "Build Python extension module (pybind11)" ON)
option(BUILD_TESTING           "Build C++ tests"                           ON)
option(HAL_BACKEND_MOCK        "Use MOCK HAL backend"                      ON)
option(HAL_BACKEND_RPI         "Use RPI  HAL backend"                      OFF)
option(USE_SYSTEM_PYBIND11     "Find pybind11 via find_package"            OFF)

# HAL взаимоисключения
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
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# MSVC рантайм DLL (/MDd|/MD)
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif ()

# НЕ используем глобальные add_compile_options!
# Вместо этого сделаем функцию, применяемую ПО ТАРГЕТАМ
function(set_common_warnings tgt)
    target_compile_options(${tgt} PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
            $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wpedantic>
    )
endfunction()

# ---- Зависимости ----------------------------------------------------------
# RadioLib: не добавляем как подпроект, подключаем как header-only
# Ожидаем, что заголовки в thirdparty/RadioLib/src
set(RADIOLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/RadioLib/src CACHE PATH "RadioLib include dir")

# pybind11
if (BUILD_PY_MODULE)
    if (USE_SYSTEM_PYBIND11)
        find_package(pybind11 CONFIG REQUIRED)
    else ()
        add_subdirectory(thirdparty/pybind11)
    endif ()
endif ()

# ---- Глобальные дефайны для HAL -------------------------------------------
if (HAL_BACKEND_MOCK)
    add_compile_definitions(RLRPI_HAL_BACKEND_MOCK=1)
elseif (HAL_BACKEND_RPI)
    add_compile_definitions(RLRPI_HAL_BACKEND_RPI=1)
endif ()

# ---- Подпроект с исходниками ----------------------------------------------
# ВАЖНО: весь ваш код/цели в src/
add_subdirectory(src)

# ---- Тестирование ---------------------------------------------------------
include(CTest)
if (BUILD_TESTING)
    enable_testing()
endif ()

# ---- Диагностика ----------------------------------------------------------
message(STATUS "========== PyRadioLib build config ==========")
message(STATUS "CMAKE_BUILD_TYPE     : ${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_PY_MODULE      : ${BUILD_PY_MODULE}")
message(STATUS "BUILD_TESTING        : ${BUILD_TESTING}")
message(STATUS "HAL_BACKEND_MOCK     : ${HAL_BACKEND_MOCK}")
message(STATUS "HAL_BACKEND_RPI      : ${HAL_BACKEND_RPI}")
message(STATUS "RADIOLIB_INCLUDE_DIR : ${RADIOLIB_INCLUDE_DIR}")
message(STATUS "USE_SYSTEM_PYBIND11  : ${USE_SYSTEM_PYBIND11}")
message(STATUS "================================================")
