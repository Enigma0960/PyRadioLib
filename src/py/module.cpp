#include "protocols/bind_physical_layer.h"

#include <pybind11/pybind11.h>

#include <modules/sx126x/bind_sx1261.h>
#include <modules/sx126x/bind_sx1262.h>
#include <modules/sx126x/bind_sx1268.h>
#include <modules/sx126x/bind_sx126x.h>
#include <modules/sx126x/bind_types.h>
#include <py/bind_hal.h>
#include <py/bind_mock.h>
#include <py/bind_module.h>
#include <py/bind_types.h>
#include <py/protocols/bind_physical_layer.h>

namespace py = pybind11;

PYBIND11_MODULE(pyradiolib, root_module) {
	root_module.doc() = "PyRadioLib";

	py::register_exception<std::runtime_error>(root_module, "RadioLibError");

	bind_types(root_module);

	bind_hal(root_module);
	bind_mock(root_module);
	bind_module(root_module);

	auto protocols_module = root_module.def_submodule("protocols");
	bind_physical_layer(protocols_module);

	auto modules_module = root_module.def_submodule("modules");
	bind_sx126x_types(modules_module);
	bind_sx126x(modules_module);
	bind_sx1261(modules_module);
	bind_sx1262(modules_module);
	bind_sx1268(modules_module);
}
