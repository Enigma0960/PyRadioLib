#include <pybind11/pybind11.h>

#include <py/bind_hal.h>
#include <py/bind_mock.h>
#include <py/bind_module.h>
#include <py/modules/bind_enums.h>
#include <py/modules/bind_sx1262.h>

namespace py = pybind11;

PYBIND11_MODULE(pyradiolib, root_module) {
	root_module.doc() = "PyRadioLib";

	py::register_exception<std::runtime_error>(root_module, "RadioLibError");

	bind_enums(root_module);

	bind_hal(root_module);
	bind_mock(root_module);
	bind_module(root_module);

	auto modules_module = root_module.def_submodule("modules");
	bind_sx1262(modules_module);
}
