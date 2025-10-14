#include "MokGpio.h"

#include <memory>

#include <core/macros.h>

using namespace pyradiolib;

MockGpio::MockGpio(uint32_t ios)
    : _ioCount(ios) {
	_states.reserve(_ioCount);
	for (uint32_t i = 0; i < _ioCount; i++) {
		_states.emplace_back();
	}
}

bool MockGpio::contains(uint32_t pin) const {
	return pin < _states.size();
}

std::optional<uint32_t> MockGpio::getPinMode(uint32_t pin) const {
	if (!contains(pin)) {
		return std::nullopt;
	}
	return _states.at(pin).mode;
}

void MockGpio::setPinMode(uint32_t pin, uint32_t mode) {
	if (!contains(pin)) {
		return;
	}
	if (_states[pin].mode != mode) {
		_states[pin].mode = static_cast<PinMode>(mode);
	}
}

std::optional<uint32_t> MockGpio::getPinOutput(uint32_t pin) const {
	if (!contains(pin)) {
		return std::nullopt;
	}
	return _states.at(pin).value;
}

void MockGpio::setPinOutput(uint32_t pin, uint32_t value) {
	if (!contains(pin)) {
		return;
	}
	if (_states[pin].value != value) {
		_states[pin].value = value;
	}
}

void MockGpio::emitPinOutput(uint32_t pin, uint32_t value) {
	if (!contains(pin)) {
		return;
	}
	if (_states[pin].value != value) {
		_states[pin].value = value;
		// IRQ
	}
}
