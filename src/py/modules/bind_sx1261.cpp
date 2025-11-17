#include "bind_sx1261.h"

#include <py/bind_types.h>
#include <radiolib/modules/SX126x/SX1261.h>

void bind_sx1261(py::module& module) {
	py::class_<SX1261, std::shared_ptr<SX1261>>(module, "SX1261")
	    .def(py::init<>([](std::shared_ptr<Module> const& module) {
		    return std::make_shared<SX1261>(module.get());
	    }))
	    .def("setOutputPower", &SX1261::setOutputPower,
	        py::arg("power"))
	    .def("checkOutputPower", [](SX126x& self, std::uint8_t power, py::buffer const& clipped) {
		    py::buffer_info data = clipped.request();
		    auto* ptr = static_cast<std::int8_t*>(data.ptr);
		    py::gil_scoped_release release;
		    return self.checkOutputPower(power, ptr); //
	    },
	        py::arg("power"), py::arg("clipped"));
}
