#include <gtest/gtest.h>
#include <radiolib/Module.h>

#include <core/macros.h>
#include <mock/MockHal.h>

using namespace pyradiolib;

TEST(RadioLib, SmokeTest) {
	Module module(nullptr, 0, 0, 0);
	UNUSED(module);
}

TEST(RadioLib, MokeHal) {
	auto ctx = std::make_shared<MockContext>();

	MockHal hal(ctx, 0, 0, 0, 0, 0, 0);

	hal.digitalWrite(0, 1);
	ASSERT_EQ(hal.digitalRead(0), 1);
	hal.digitalWrite(0, 0);
	ASSERT_EQ(hal.digitalRead(0), 0);
}
