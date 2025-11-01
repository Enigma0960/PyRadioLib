#include "bind_module.h"
#include "mock/MockContext.h"

#include <pybind11/pybind11.h>

#include <py/bind_hal.h>
#include <py/bind_mock.h>

namespace py = pybind11;


PYBIND11_MODULE(pyradiolib, module) {
	module.doc() = "PyRadioLib";

	py::register_exception<std::runtime_error>(module, "RadioLibError");

	bind_hal(module);
	bind_mock(module);
	bind_module(module);
}
