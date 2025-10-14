#pragma once

#include <memory>
#include <pybind11/pybind11.h>
#include <radiolib/Hal.h>

#include <mock/MockContext.h>

namespace py = pybind11;

void bind_mock(py::module_& module);
