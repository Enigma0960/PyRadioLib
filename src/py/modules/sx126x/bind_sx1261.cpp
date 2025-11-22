#include "bind_sx1261.h"

#include <py/bind_types.h>
#include <radiolib/modules/SX126x/SX1261.h>
#include <radiolib/modules/SX126x/SX126x.h>

void bind_sx1261(py::module& module) {
	py::class_<SX1261, SX126x, std::shared_ptr<SX1261>>(module, "SX1261")
	    .def(py::init<>([](std::shared_ptr<Module> const& module) {
		    return std::make_shared<SX1261>(module.get());
	    }),
	        py::arg("module"),
	        py::keep_alive<1, 2>())
	    .def("setOutputPower", [](SX1261& self, std::int8_t power) {
	    	ModuleStatus status{};
			{
				py::gil_scoped_release const release;
				status = static_cast<ModuleStatus>(self.setOutputPower(power));
			}
	    	return status;
	    },
	        py::arg("power"))
	    .def("checkOutputPower", [](SX1261& self, std::int8_t power) {
		    std::int8_t clipped = 0;
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.checkOutputPower(power, &clipped));
		    }
		    return py::make_tuple(status, clipped); //
	    },
	        py::arg("power"));
}
