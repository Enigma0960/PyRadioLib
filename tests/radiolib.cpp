

#include <gtest/gtest.h>
#include <radiolib/Module.h>
#include <radiolib/modules/SX126x/SX1261.h>

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


TEST(RadioLib, ModuleInit) {
	auto ctx = std::make_shared<MockContext>();
	MockHal hal(ctx, 0, 1, 0, 1, 1, 0);

	Module module(&hal, 0, 1, 2);

	module.init();

	ASSERT_EQ(hal.digitalRead(0), 1);
	ASSERT_EQ(hal.gpio()->getPinMode(0), 1);

}

TEST(RadioLib, Sx1261) {
	auto ctx = std::make_shared<MockContext>();
	MockHal hal(ctx, 0, 1, 0, 1, 1, 0);
	Module module(&hal, 0, 1, 2);

	auto* radio = new SX1261(&module);

	int8_t c = 0;

	radio->checkOutputPower(10, &c);

	ASSERT_EQ(c, 10);
}
