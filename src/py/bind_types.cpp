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
}
