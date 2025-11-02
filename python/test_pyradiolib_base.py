import pytest
import datetime

import pyradiolib


class TestPyRadioLibBase:
    def test_mock_hal(self):
        hal = pyradiolib.MockHal(0, 0, 0, 0, 0, 0)
        assert hal is not None

        # with assert_duration_lt(seconds=1):
        #     hal.delay(1000)
        #
        # with assert_duration_lt(seconds=1):
        #     hal.delayMicroseconds(1000 * 1000)

        hal.digitalWrite(0, 1)
        assert hal.digitalRead(0) == 1
        hal.digitalWrite(0, 0)
        assert hal.digitalRead(0) == 0

    def test_mock_gpio(self):
        hal = pyradiolib.MockHal(0, 0, 0, 0, 0, 0)
        assert hal is not None

        gpio = hal.gpio()
        assert gpio is not None

    def test_module_init(self):
        module = pyradiolib.Module(None, 0,0,0)

        assert module is not None

        try:
            module.init()
        except Exception as e:
            pytest.fail(f"Unexpected exception: {e}")
