#include "bind_module.h"

#include <radiolib/Module.h>

void bind_module(py::module& module) {
	py::class_<Module, std::shared_ptr<Module>>(module, "Module")
	    .def(py::init([](std::shared_ptr<RadioLibHal> const& hal,
	                      std::uint32_t cs,
	                      std::uint32_t irq,
	                      std::uint32_t rst,
	                      std::uint32_t gpio) {
		    return std::make_shared<Module>(hal.get(), cs, irq, rst, gpio);
	    }),
	        py::arg("hal"),
	        py::arg("cs"),
	        py::arg("irq"),
	        py::arg("rst"),
	        py::arg("gpio") = RADIOLIB_NC,
	        py::keep_alive<1, 2>()
	        )
	    .def("init", &Module::init, py::call_guard<py::gil_scoped_release>());
}
