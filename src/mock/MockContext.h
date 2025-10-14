#pragma once

#include <memory>

#include <mock/MokGpio.h>

namespace pyradiolib {

class MockContext {
public:
	MockContext();
	virtual ~MockContext();

	std::shared_ptr<MockGpio> gpio() const;

private:
	std::shared_ptr<MockGpio> _gpio;
};

} // namespace pyradiolib
