from unittest.mock import MagicMock

import pyradiolib


class TestPyRadioLibBase:
    def test_mock_hal(self, cpp_hal: pyradiolib.RadioLibHal):
        agg = MagicMock()

        def _test_callback():
            agg.callback_called()

        cpp_hal.attachInterrupt(0, _test_callback, 0)
        cpp_hal.triggerInterrupt(0)

        assert agg.callback_called.called
        agg.callback_called.reset_mock()

        cpp_hal.detachInterrupt(0)

        cpp_hal.triggerInterrupt(0)


        assert not agg.callback_called.called