#pragma once

#include <pybind11/pybind11.h>
#include <radiolib/protocols/PhysicalLayer/PhysicalLayer.h>

namespace py = pybind11;

using ModemType = ModemType_t;
using RadioModeType = RadioModeType_t;

using LoRaRate = LoRaRate_t;
using FSKRate = FSKRate_t;
using LrFhssRate = LrFhssRate_t;

using LoRaPacketConfig = LoRaPacketConfig_t;
using FSKPacketConfig = FSKPacketConfig_t;
using LrFhssPacketConfig = LrFhssPacketConfig_t;

using CADScanConfig = CADScanConfig_t;
using RSSIScanConfig = RSSIScanConfig_t;

using StandbyConfig = StandbyConfig_t;
using ReceiveConfig = ReceiveConfig_t;
using TransmitConfig = TransmitConfig_t;
using ChannelScanConfig = ChannelScanConfig_t;
using SleepConfig = SleepConfig_t;

void bind_types(py::module& module);

