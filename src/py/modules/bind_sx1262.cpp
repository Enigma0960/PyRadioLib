#include "bind_sx1262.h"

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
	        py::call_guard<py::gil_scoped_release>());
}
