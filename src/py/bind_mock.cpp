#include "bind_mock.h"

#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <mock/MockHal.h>

namespace py = pybind11;

using namespace pyradiolib;

void bind_mock(py::module_& module) {
	py::class_<MockContext, std::shared_ptr<MockContext>>(module, "MockContext")
	    .def(py::init<>());

	py::class_<MockGpio, std::shared_ptr<MockGpio>>(module, "MockGpio")
	    .def(py::init<std::uint32_t>(),
	        py::arg("ios"))
	    .def("contains", &MockGpio::contains, py::arg("pin"));

	py::class_<MockHal, RadioLibHal, std::shared_ptr<MockHal>>(module, "MockHal")
	    .def(py::init([](uint32_t input, uint32_t output, uint32_t low,
	                      uint32_t high, uint32_t rising, uint32_t falling) {
		    auto ctx = std::make_shared<MockContext>();
		    return std::make_shared<MockHal>(ctx, input, output, low, high, rising, falling);
	    }),
	        py::arg("input"),
	        py::arg("output"),
	        py::arg("low"),
	        py::arg("high"),
	        py::arg("rising"),
	        py::arg("falling"),
	        R"()")
	    .def("gpio", &MockHal::gpio);
}
