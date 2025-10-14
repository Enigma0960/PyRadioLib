#include "MockContext.h"

using namespace pyradiolib;

MockContext::MockContext()
    : _gpio(std::make_shared<MockGpio>()) {
}

MockContext::~MockContext() {
	_gpio.reset();
}

std::shared_ptr<MockGpio> MockContext::gpio() const {
	return _gpio;
}
