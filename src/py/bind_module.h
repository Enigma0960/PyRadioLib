#pragma once

#include <pybind11/pybind11.h>
#include <radiolib/Module.h>

namespace py = pybind11;

void bind_module(py::module& module);
