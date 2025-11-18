#include "bind_sx1268.h"

#include <py/bind_types.h>
#include <radiolib/modules/SX126x/SX1268.h>
#include <radiolib/modules/SX126x/SX126x.h>

void bind_sx1268(py::module& module) {
	py::class_<SX1268, SX126x, std::shared_ptr<SX1268>>(module, "SX1268")
	    .def(py::init<>([](std::shared_ptr<Module> const& module) {
		    return std::make_shared<SX1268>(module.get());
	    }),
	        py::arg("module"),
	        py::keep_alive<1, 2>())
	    .def("begin", &SX1268::begin,
	        py::arg("freq") = 434.0,
	        py::arg("bw") = 125.0,
	        py::arg("sf") = 9,
	        py::arg("cr") = 7,
	        py::arg("syncWord") = RADIOLIB_SX126X_SYNC_WORD_PRIVATE,
	        py::arg("power") = 10,
	        py::arg("preambleLength") = 8,
	        py::arg("tcxoVoltage") = 1.6,
	        py::arg("useRegulatorLDO") = false)
	    .def("beginFSK", &SX1268::beginFSK,
	        py::arg("freq") = 434.0,
	        py::arg("br") = 4.8,
	        py::arg("freqDev") = 5.0,
	        py::arg("rxBw") = 156.2,
	        py::arg("power") = 10,
	        py::arg("preambleLength") = 16,
	        py::arg("tcxoVoltage") = 1.6,
	        py::arg("useRegulatorLDO") = false)
	    .def("beginLRFHSS", &SX1268::beginLRFHSS,
	        py::arg("freq") = 434.0,
	        py::arg("bw") = RADIOLIB_SX126X_LR_FHSS_BW_722_66,
	        py::arg("cr") = RADIOLIB_SX126X_LR_FHSS_CR_2_3,
	        py::arg("narrowGrid") = true,
	        py::arg("power") = 10,
	        py::arg("tcxoVoltage") = 1.6,
	        py::arg("useRegulatorLDO") = false)
	    .def("setFrequency", py::overload_cast<float>(&SX1268::setFrequency), py::arg("freq"))
	    .def("setFrequency", py::overload_cast<float, bool>(&SX1268::setFrequency), py::arg("freq"), py::arg("skipCalibration"))
	    .def("setOutputPower", &SX1268::setOutputPower, py::arg("power"))
	    .def("checkOutputPower", [](SX1268& self, std::int8_t power) {
		    std::int8_t clipped = 0;
		    std::int16_t result = 0;
		    {
			    py::gil_scoped_release release;
			    result = self.checkOutputPower(power, &clipped);
		    }
		    return py::make_tuple(result, clipped); //
	    },
	        py::arg("power"))
	    .def("setModem", &SX1268::setModem, py::arg("modem"));
}
