#pragma once

#include <pybind11/pybind11.h>
#include <radiolib/protocols/PhysicalLayer/PhysicalLayer.h>

namespace py = pybind11;

struct PyPhysicalLayer : public PhysicalLayer {
	using PhysicalLayer::PhysicalLayer;
	virtual ~PyPhysicalLayer() = default;

	Module* getMod() override {
		PYBIND11_OVERRIDE_PURE(Module*, PyPhysicalLayer, );
	}
};

void bind_physical_layer(py::module& module);
