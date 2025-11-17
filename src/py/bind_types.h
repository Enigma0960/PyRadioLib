#pragma once

#include <pybind11/pybind11.h>
#include <radiolib/protocols/PhysicalLayer/PhysicalLayer.h>

namespace py = pybind11;

using ModemType = ModemType_t;
using RadioModeType = RadioModeType_t;

using LoRaRate = LoRaRate_t;
using FSKRate = FSKRate_t;
using LrFhssRate = LrFhssRate_t;

void bind_types(py::module& module);

