#pragma once

#include <memory>
#include <pybind11/pybind11.h>
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
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, spiTransfer, out, len, in);
	}

	void spiEndTransaction() override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, spiEndTransaction, );
	}

	void spiEnd() override {
		PYBIND11_OVERRIDE_PURE(void, RadioLibHal, spiEnd, );
	}
};

void bind_hal(py::module_& module);
