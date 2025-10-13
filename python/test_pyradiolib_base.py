import pytest
import datetime

import pyradiolib

from utils import *


class TestPyRadioLibBase:

    def test_mock_hal(self):
        hal = pyradiolib.MockHal(0, 0, 0, 0, 0, 0)
        assert hal is not None

        with assert_duration_lt(seconds=1):
            hal.delay(1000)

        with assert_duration_lt(seconds=1):
            hal.delayMicroseconds(1000 * 1000)
