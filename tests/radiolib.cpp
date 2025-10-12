#include <gtest/gtest.h>
#include <radiolib/Module.h>

#include <core/macros.h>
#include <hal/MockHal.h>

using namespace PyRadioLib;

TEST(RadioLib, SmokeTest) {
	Module module();
	UNUSED(module);
}

TEST(RadioLib, MokeHal) {
	MockHal mock(0, 0, 0, 0, 0, 0);
	UNUSED(mock);
}
