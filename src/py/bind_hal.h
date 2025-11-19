#pragma once

#include <memory>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <radiolib/Hal.h>

namespace py = pybind11;

struct PyHal : public RadioLibHal {
	using RadioLibHal::RadioLibHal;
	virtual ~PyHal() = default;

	void pinMode(uint32_t pin, uint32_t mode) override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, pinMode, pin, mode);
	}

	void digitalWrite(uint32_t pin, uint32_t value) override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, digitalWrite, pin, value);
	}

	uint32_t digitalRead(uint32_t pin) override {
		PYBIND11_OVERRIDE_PURE(uint32_t, RadioLibHal, digitalRead, pin);
	}

	void attachInterrupt(uint32_t interruptNum, void (*interruptCb)(void), uint32_t mode) override {
		// PYBIND11_OVERRIDE_PURE(void, RadioLibHal, attachInterrupt, interruptNum, interruptCb, mode);
	}

	void detachInterrupt(uint32_t interruptNum) override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, detachInterrupt, interruptNum);
	}

	void delay(RadioLibTime_t ms) override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, delay, ms);
	}

	void delayMicroseconds(RadioLibTime_t us) override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, delayMicroseconds, us);
	}

	RadioLibTime_t millis() override {
		PYBIND11_OVERRIDE_PURE(RadioLibTime_t, RadioLibHal, millis, );
	}

	RadioLibTime_t micros() override {
		PYBIND11_OVERRIDE_PURE(RadioLibTime_t, RadioLibHal, micros, );
	}

	long pulseIn(uint32_t pin, uint32_t state, RadioLibTime_t timeout) override {
		PYBIND11_OVERRIDE_PURE(long, RadioLibHal, pulseIn, pin, state, timeout);
	}

	void spiBegin() override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, spiBegin, );
	}

	void spiBeginTransaction() override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, spiBeginTransaction, );
	}

	void spiTransfer(uint8_t* out, size_t len, uint8_t* in) override {
		py::gil_scoped_acquire const gil;

		py::function const override = pybind11::get_override(static_cast<RadioLibHal const*>(this), "spiTransfer");
		if (!override) {
			PyErr_SetString(PyExc_TypeError, "Pure virtual function 'RadioLibHal.spiTransfer' not overridden in Python");
			throw py::error_already_set();
		}

		py::bytes out_bytes(reinterpret_cast<char const*>(out), len);

		py::object result = override(out_bytes);

		if (!result.is_none()) {
			py::bytes in_bytes = result.cast<py::bytes>();
			std::string in_str = in_bytes;

			std::size_t const copy_len = std::min(len, in_str.size());
			std::memcpy(in, in_str.data(), copy_len);
		}
	}

	void spiEndTransaction() override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, spiEndTransaction, );
	}

	void spiEnd() override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, spiEnd, );
	}

	uint32_t pinToInterrupt(uint32_t pin) override {
		PYBIND11_OVERRIDE_PURE(uint32_t, RadioLibHal, pinToInterrupt, pin);
	}
};

void bind_hal(py::module_& module);
