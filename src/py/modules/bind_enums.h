#pragma once

#include <pybind11/pybind11.h>
#include <radiolib/protocols/PhysicalLayer/PhysicalLayer.h>

namespace py = pybind11;

using ModemType = ModemType_t;

void bind_enums(py::module& module);

