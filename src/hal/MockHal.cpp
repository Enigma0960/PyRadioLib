#include "MockHal.h"

using namespace PyRadioLib;

MockHal::MockHal(uint32_t const input, uint32_t const output, uint32_t const low, uint32_t const high, uint32_t const rising, uint32_t const falling)
    : Super(input, output, low, high, rising, falling) {
}

void MockHal::pinMode(uint32_t pin, uint32_t mode) {
}

void MockHal::digitalWrite(uint32_t pin, uint32_t value) {
}

uint32_t MockHal::digitalRead(uint32_t pin) {
	return {};
}

void MockHal::attachInterrupt(uint32_t interruptNum, void (*interruptCb)(void), uint32_t mode) {
}

void MockHal::detachInterrupt(uint32_t interruptNum) {
}

void MockHal::delay(RadioLibTime_t ms) {
}

void MockHal::delayMicroseconds(RadioLibTime_t us) {
}

RadioLibTime_t MockHal::millis() {
	return {};
}

RadioLibTime_t MockHal::micros() {
	return {};
}

long MockHal::pulseIn(uint32_t pin, uint32_t state, RadioLibTime_t timeout) {
	return {};
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
