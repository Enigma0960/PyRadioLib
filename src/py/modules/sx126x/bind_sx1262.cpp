#include "bind_sx1262.h"

#include <py/bind_types.h>
#include <radiolib/modules/SX126x/SX1262.h>
#include <radiolib/modules/SX126x/SX126x.h>

void bind_sx1262(py::module& module) {
	py::class_<SX1262, SX126x, std::shared_ptr<SX1262>>(module, "SX1262")
	    .def(py::init([](std::shared_ptr<Module> const& module) {
		    return std::make_shared<SX1262>(module.get());
	    }),
	        py::arg("module"),
	        py::keep_alive<1, 2>())
	    .def("begin", [](SX1262& self, float freq, float bw, std::uint8_t sf, std::uint8_t cr, std::uint8_t syncWord, std::int8_t power, std::uint16_t preambleLength, float tcxoVoltage, bool useRegulatorLDO) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.begin(freq, bw, sf, cr, syncWord, power, preambleLength, tcxoVoltage, useRegulatorLDO));
		    }
		    return status; //
	    },
	        py::arg("freq") = 434.0, py::arg("bw") = 125.0, py::arg("sf") = 9, py::arg("cr") = 7, py::arg("syncWord") = RADIOLIB_SX126X_SYNC_WORD_PRIVATE, py::arg("power") = 10, py::arg("preambleLength") = 8, py::arg("tcxoVoltage") = 1.6, py::arg("useRegulatorLDO") = false, py::call_guard<py::gil_scoped_release>())
	    .def("beginFSK", [](SX1262& self, float freq, float br, float freqDev, float rxBw, std::int8_t power, std::uint16_t preambleLength, float tcxoVoltage, bool useRegulatorLDO) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.beginFSK(freq, br, freqDev, rxBw, power, preambleLength, tcxoVoltage, useRegulatorLDO));
		    }
		    return status; //
	    },
	        py::arg("freq") = 434.0, py::arg("br") = 4.0, py::arg("freqDev") = 5.0, py::arg("rxBw") = 156.2, py::arg("power") = 10, py::arg("preambleLength") = 16, py::arg("tcxoVoltage") = 1.6, py::arg("useRegulatorLDO") = false)
	    .def("beginLRFHSS", [](SX1262& self, float freq, std::uint8_t bw, std::uint8_t cr, bool narrowGrid, std::int8_t power, float tcxoVoltage, bool useRegulatorLDO) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.beginLRFHSS(freq, bw, cr, narrowGrid, power, tcxoVoltage, useRegulatorLDO));
		    }
		    return status; //
	    },
	        py::arg("freq") = 434.0, py::arg("bw") = RADIOLIB_SX126X_LR_FHSS_BW_722_66, py::arg("cr") = RADIOLIB_SX126X_LR_FHSS_CR_2_3, py::arg("narrowGrid") = true, py::arg("power") = 10, py::arg("tcxoVoltage") = 1.6, py::arg("useRegulatorLDO") = false)
	    .def("setFrequency", [](SX1262& self, float freq, bool skipCalibration) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setFrequency(freq, skipCalibration));
		    }
		    return status; //
	    },
	        py::arg("freq"), py::arg("skipCalibration") = false)
	    .def("setOutputPower", [](SX1262& self, std::int8_t power) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setOutputPower(power));
		    }
		    return status; //
	    },
	        py::arg("power"))
	    .def("checkOutputPower", [](SX1262& self, std::int8_t power) {
		    std::int8_t clipped = 0;
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release release;
			    status = static_cast<ModuleStatus>(self.checkOutputPower(power, &clipped));
		    }
		    return py::make_tuple(status, clipped); //
	    },
	        py::arg("power"))
	.def("setModem", [](SX1262& self, ModemType modem) {
		ModuleStatus status{};
		{
			py::gil_scoped_release const release;
			status = static_cast<ModuleStatus>(self.setModem(modem));
		}
		return status; //
	}, py::arg("modem"));
}
