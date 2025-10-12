#include "bind_hal.h"

#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hal/MockHal.h>
#if defined(__unix__) || defined(linux)
	#include <radiolib/hal/RPi/PiHal.h>
#endif

namespace py = pybind11;

void bind_hal(py::module_& module) {
	py::class_<RadioLibHal, PyHal, std::shared_ptr<RadioLibHal>>(module, "RadioLibHal")
	    .def(py::init<std::uint32_t, std::uint32_t, std::uint32_t,
	             std::uint32_t, std::uint32_t, std::uint32_t>(),
	        py::arg("input"),
	        py::arg("output"),
	        py::arg("low"),
	        py::arg("high"),
	        py::arg("rising"),
	        py::arg("falling"),
	        R"(HAL реализация.
				Аргументы соответствуют пинам/линиям:
				- input
				- output
				- low
				- high
				- rising
				- falling)");

	py::class_<PyRadioLib::MockHal, RadioLibHal, std::shared_ptr<PyRadioLib::MockHal>>(module, "MockHal");

#if defined(__unix__) || defined(linux)
	py::class_<PiHal, RadioLibHal, std::shared_ptr<PiHal>>(module, "MockHal");
#endif
}
