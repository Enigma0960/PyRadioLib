#include "bind_types.h"

void bind_types(py::module& module) {
	py::enum_<ModemType>(module, "ModemType", py::arithmetic())
	    .value("RADIOLIB_MODEM_FSK", RADIOLIB_MODEM_FSK)
	    .value("RADIOLIB_MODEM_LORA", RADIOLIB_MODEM_LORA)
	    .value("RADIOLIB_MODEM_LRFHSS", RADIOLIB_MODEM_LRFHSS)
	    .value("RADIOLIB_MODEM_NONE", RADIOLIB_MODEM_NONE);

	py::enum_<RadioModeType>(module, "RadioMode", py::arithmetic())
	    .value("RADIOLIB_RADIO_MODE_NONE", RADIOLIB_RADIO_MODE_NONE)
	    .value("RADIOLIB_RADIO_MODE_STANDBY", RADIOLIB_RADIO_MODE_STANDBY)
	    .value("RADIOLIB_RADIO_MODE_RX", RADIOLIB_RADIO_MODE_RX)
	    .value("RADIOLIB_RADIO_MODE_TX", RADIOLIB_RADIO_MODE_TX)
	    .value("RADIOLIB_RADIO_MODE_SCAN", RADIOLIB_RADIO_MODE_SCAN)
	    .value("RADIOLIB_RADIO_MODE_SLEEP", RADIOLIB_RADIO_MODE_SLEEP);

	py::class_<LoRaRate>(module, "LoRaRate")
	    .def_readwrite("spreadingFactor", &LoRaRate::spreadingFactor)
	    .def_readwrite("bandwidth", &LoRaRate::bandwidth)
	    .def_readwrite("codingRate", &LoRaRate::codingRate);

	py::class_<FSKRate>(module, "FSKRate")
	    .def_readwrite("bitRate", &FSKRate::bitRate)
	    .def_readwrite("freqDev", &FSKRate::freqDev);

	py::class_<LrFhssRate>(module, "LrFhssRate")
	    .def_readwrite("bw", &LrFhssRate::bw)
	    .def_readwrite("cr", &LrFhssRate::cr)
	    .def_readwrite("narrowGrid", &LrFhssRate::narrowGrid);

	py::class_<LoRaPacketConfig>(module, "LoRaPacketConfig")
	    .def_readwrite("crcEnabled", &LoRaPacketConfig::crcEnabled)
	    .def_readwrite("implicitHeader", &LoRaPacketConfig::implicitHeader)
	    .def_readwrite("ldrOptimize", &LoRaPacketConfig::ldrOptimize)
	    .def_readwrite("preambleLength", &LoRaPacketConfig::preambleLength);

	py::class_<FSKPacketConfig>(module, "FSKPacketConfig")
	    .def_readwrite("syncWordLength", &FSKPacketConfig::syncWordLength)
	    .def_readwrite("crcLength", &FSKPacketConfig::crcLength)
	    .def_readwrite("preambleLength", &FSKPacketConfig::preambleLength);

	py::class_<LrFhssPacketConfig>(module, "LrFhssPacketConfig")
	    .def_readwrite("hdrCount", &LrFhssPacketConfig::hdrCount);

	py::class_<CADScanConfig>(module, "CADScanConfig")
	    .def_readwrite("symNum", &CADScanConfig::symNum)
	    .def_readwrite("detPeak", &CADScanConfig::detPeak)
	    .def_readwrite("detMin", &CADScanConfig::detMin)
	    .def_readwrite("exitMode", &CADScanConfig::exitMode)
	    .def_readwrite("timeout", &CADScanConfig::timeout)
	    .def_readwrite("irqFlags", &CADScanConfig::irqFlags)
	    .def_readwrite("irqMask", &CADScanConfig::irqMask);

	py::class_<RSSIScanConfig>(module, "RSSIScanConfig")
	    .def_readwrite("limit", &RSSIScanConfig::limit);

	py::class_<StandbyConfig>(module, "StandbyConfig")
	    .def_readwrite("mode", &StandbyConfig::mode);

	py::class_<ReceiveConfig>(module, "ReceiveConfig")
	    .def_readwrite("irqFlags", &ReceiveConfig::irqFlags)
	    .def_readwrite("irqMask", &ReceiveConfig::irqMask)
	    .def_readwrite("len", &ReceiveConfig::len)
	    .def_readwrite("timeout", &ReceiveConfig::timeout);

	py::class_<TransmitConfig>(module, "TransmitConfig")
	    .def_readwrite("len", &TransmitConfig::len)
	    .def_readwrite("addr", &TransmitConfig::addr)
	    .def_readwrite("data", &TransmitConfig::data);

	py::class_<ChannelScanConfig>(module, "ChannelScanConfig")
	    .def_readwrite("cad", &ChannelScanConfig::cad)
	    .def_readwrite("rssi", &ChannelScanConfig::rssi);

	py::class_<SleepConfig>(module, "SleepConfig")
	    .def_readwrite("mode", &SleepConfig::mode);
}
