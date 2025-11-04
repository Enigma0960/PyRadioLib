#include "bind_sx1262.h"

#include <py/modules/bind_enums.h>
#include <radiolib/modules/SX126x/SX1262.h>

void bind_sx1262(py::module& module) {
	py::class_<SX1262, std::shared_ptr<SX1262>>(module, "SX1262")
	    .def(py::init([](std::shared_ptr<Module> module) {
		    return std::make_shared<SX1262>(module.get());
	    }),
	        py::arg("module"),
	        py::keep_alive<1, 2>())
	    .def("begin", &SX1262::begin,
	        py::arg("freq") = 434.0,
	        py::arg("bw") = 125.0,
	        py::arg("sf") = 9,
	        py::arg("cr") = 7,
	        py::arg("syncWord") = RADIOLIB_SX126X_SYNC_WORD_PRIVATE,
	        py::arg("power") = 10,
	        py::arg("preambleLength") = 8,
	        py::arg("tcxoVoltage") = 1.6,
	        py::arg("useRegulatorLDO") = false,
	        py::call_guard<py::gil_scoped_release>())
	    .def("beginFSK", &SX1262::beginFSK,
	        py::arg("freq") = 434.0,
	        py::arg("br") = 4.0,
	        py::arg("freqDev") = 5.0,
	        py::arg("rxBw") = 156.2,
	        py::arg("power") = 10,
	        py::arg("preambleLength") = 16,
	        py::arg("tcxoVoltage") = 1.6,
	        py::arg("useRegulatorLDO") = false)
	    .def("beginLRFHSS", &SX1262::beginLRFHSS,
	        py::arg("freq") = 434.0,
	        py::arg("bw") = RADIOLIB_SX126X_LR_FHSS_BW_722_66,
	        py::arg("cr") = RADIOLIB_SX126X_LR_FHSS_CR_2_3,
	        py::arg("narrowGrid") = true,
	        py::arg("power") = 10,
	        py::arg("tcxoVoltage") = 1.6,
	        py::arg("useRegulatorLDO") = false)
	    .def("setFrequency", py::overload_cast<float>(&SX1262::setFrequency),
	        py::arg("freq"))
	    .def("setFrequency", py::overload_cast<float, bool>(&SX1262::setFrequency),
	        py::arg("freq"),
	        py::arg("skipCalibration"))
	    .def("setOutputPower", &SX1262::setOutputPower,
	        py::arg("power"))
	    .def("checkOutputPower", &SX1262::checkOutputPower,
	        py::arg("power"),
	        py::arg("clipped"))
	    .def("setModem", py::overload_cast<ModemType>(&SX1262::setModem),
	        py::arg("modem"));
}
