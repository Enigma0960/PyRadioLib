#include "bind_hal.h"

#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <mock/MockHal.h>
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
	        R"()")
	    .def("pinMode", &RadioLibHal::pinMode, py::arg("pin"), py::arg("mode"))
	    .def("digitalWrite", &RadioLibHal::digitalWrite, py::arg("pin"), py::arg("value"))
	    .def("digitalRead", &RadioLibHal::digitalRead, py::arg("pin"))
	    .def("attachInterrupt", [](RadioLibHal& self, uint32_t num, std::function<void()> const& cb, uint32_t mode) {
		    // если это чисто виртуальный метод, тут обычно бросают исключение:
		    //throw std::runtime_error("attachInterrupt is only meaningful in concrete HAL implementations");
	    }, //
	        py::arg("interruptNum"), py::arg("callback"), py::arg("mode"), //
	        R"(Для Python-наследников реализуйте attachInterrupt в своём классе.)")
	    .def("detachInterrupt", &RadioLibHal::detachInterrupt, py::arg("interruptNum"))
	    .def("delay", &RadioLibHal::delay, py::arg("ms"))
	    .def("delayMicroseconds", &RadioLibHal::delayMicroseconds, py::arg("us"))
	    .def("millis", &RadioLibHal::millis)
	    .def("micros", &RadioLibHal::micros)
	    .def("pulseIn", &RadioLibHal::pulseIn, py::arg("pin"), py::arg("state"), py::arg("timeout"))
	    .def("spiBegin", &RadioLibHal::spiBegin)
	    .def("spiBeginTransaction", &RadioLibHal::spiBeginTransaction)
	    .def("spiTransfer", &RadioLibHal::spiTransfer)
	    .def("spiEndTransaction", &RadioLibHal::spiEndTransaction)
	    .def("spiEnd", &RadioLibHal::spiEnd);

#if defined(__unix__) || defined(linux)
	py::class_<PiHal, RadioLibHal, std::shared_ptr<PiHal>>(module, "PiHal")
	    .def(py::init<std::uint32_t, std::uint32_t, std::uint32_t,
	             std::uint32_t, std::uint32_t, std::uint32_t>(),
	        py::arg("input"),
	        py::arg("output"),
	        py::arg("low"),
	        py::arg("high"),
	        py::arg("rising"),
	        py::arg("falling"),
	        R"()");
#endif
}
