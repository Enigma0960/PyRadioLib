#pragma once

#include <radiolib/Hal.h>

namespace PyRadioLib {
class MockHal : public RadioLibHal {
	using Self = MockHal;
	using Super = RadioLibHal;

public:
	virtual ~MockHal() = default;

	MockHal(uint32_t const input, uint32_t const output, uint32_t const low, uint32_t const high, uint32_t const rising, uint32_t const falling);

	void pinMode(uint32_t pin, uint32_t mode) override;
	void digitalWrite(uint32_t pin, uint32_t value) override;
	uint32_t digitalRead(uint32_t pin) override;
	void attachInterrupt(uint32_t interruptNum, void (*interruptCb)(void), uint32_t mode) override;
	void detachInterrupt(uint32_t interruptNum) override;
	void delay(RadioLibTime_t ms) override;
	void delayMicroseconds(RadioLibTime_t us) override;
	RadioLibTime_t millis() override;
	RadioLibTime_t micros() override;
	long pulseIn(uint32_t pin, uint32_t state, RadioLibTime_t timeout) override;
	void spiBegin() override;
	void spiBeginTransaction() override;
	void spiTransfer(uint8_t* out, size_t len, uint8_t* in) override;
	void spiEndTransaction() override;
	void spiEnd() override;
	void yield() override;
};

} // namespace PyRadioLib
