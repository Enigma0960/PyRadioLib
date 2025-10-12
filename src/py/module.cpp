#include <pybind11/pybind11.h>

#include <py/bind_hal.h>

namespace py = pybind11;

PYBIND11_MODULE(pyradiolib, module) {
	module.doc() = "PyRadioLib";

	py::register_exception<std::runtime_error>(module, "RadioLibError");

	bind_hal(module);
}
