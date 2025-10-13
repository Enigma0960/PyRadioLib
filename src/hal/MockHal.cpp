#include "MockHal.h"

#include <chrono>
#include <thread>

using namespace PyRadioLib;
using namespace std::chrono;

MockHal::MockHal(uint32_t const input, uint32_t const output, uint32_t const low, uint32_t const high, uint32_t const rising, uint32_t const falling)
    : Super(input, output, low, high, rising, falling) {
}

void MockHal::pinMode(uint32_t pin, uint32_t mode) {
}

void MockHal::digitalWrite(uint32_t pin, uint32_t value) {
}

uint32_t MockHal::digitalRead(uint32_t pin) {
	return 42;
}

void MockHal::attachInterrupt(uint32_t interruptNum, void (*interruptCb)(void), uint32_t mode) {
}

void MockHal::detachInterrupt(uint32_t interruptNum) {
}

void MockHal::delay(RadioLibTime_t ms) {
	if (ms == 0) {
		std::this_thread::yield();
		return;
	}

	std::this_thread::sleep_for(milliseconds(ms));
}

void MockHal::delayMicroseconds(RadioLibTime_t us) {
	if (us == 0) {
		std::this_thread::yield();
		return;
	}

	std::this_thread::sleep_for(microseconds(us));
}

RadioLibTime_t MockHal::millis() {
	auto const ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	return ms.count();
}

RadioLibTime_t MockHal::micros() {
	auto const us = duration_cast<microseconds>(system_clock::now().time_since_epoch());
	return us.count();
}

long MockHal::pulseIn(uint32_t pin, uint32_t state, RadioLibTime_t timeout) {
	return 45;
}

void MockHal::spiBegin() {
}

void MockHal::spiBeginTransaction() {
}

void MockHal::spiTransfer(uint8_t* out, size_t len, uint8_t* in) {
}

void MockHal::spiEndTransaction() {
}

void MockHal::spiEnd() {
}

void MockHal::yield() {
	std::this_thread::yield();
}
