#pragma once

#include <optional>
#include <vector>

namespace pyradiolib {

enum PinMode : uint32_t {
	INPUT = 0,
	INPUT_PULLUP = 1,
	INPUT_PULLDOWN = 2,
	OUTPUT = 3,
	OUTPUT_OPEN_DRAIN = 4,
};

struct MockGpioState {
	PinMode mode = INPUT;
	uint32_t value = 0;
};

class MockGpio {
	using Self = MockGpio;

public:
	explicit MockGpio(uint32_t ios = 26);

	bool contains(uint32_t pin) const;

	std::optional<uint32_t> getPinMode(uint32_t pin) const;
	void setPinMode(uint32_t pin, uint32_t mode);

	std::optional<uint32_t> getPinOutput(uint32_t pin) const;
	void setPinOutput(uint32_t pin, uint32_t value);

	void emitPinOutput(uint32_t pin, uint32_t value);

private:
	uint32_t _ioCount = 0;

	std::vector<MockGpioState> _states;
};

} // namespace pyradiolib
