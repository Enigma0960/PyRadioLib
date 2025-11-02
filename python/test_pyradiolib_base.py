import pytest

from unittest.mock import call

import pyradiolib
from python.conftest import PyMockHal

from python.utils import assert_duration_lt


class TestPyRadioLibBase:
    def test_mock_hal(self):
        hal = pyradiolib.MockHal(0, 0, 0, 0, 0, 0)
        assert hal is not None

        with assert_duration_lt(seconds=1):
            hal.delay(1000)

        with assert_duration_lt(seconds=1):
            hal.delayMicroseconds(1000 * 1000)

        hal.digitalWrite(0, 1)
        assert hal.digitalRead(0) == 1
        hal.digitalWrite(0, 0)
        assert hal.digitalRead(0) == 0

    def test_mock_gpio(self):
        hal = pyradiolib.MockHal(0, 1, 0, 1, 1, 0)
        assert hal is not None

        gpio = hal.gpio()
        assert gpio is not None

    def test_module_init(self, hal: PyMockHal):
        cs = 1

        module = pyradiolib.Module(hal, cs, 255, 255)

        assert module is not None

        module.init()

        hal.mock_pinMode.assert_called_once_with(cs, 1)
        hal.mock_digitalWrite.assert_called_once_with(cs, 1)
        assert hal._agg.mock_calls == [
            call.pinMode(cs, 1),
            call.digitalWrite(cs, 1),
        ]
