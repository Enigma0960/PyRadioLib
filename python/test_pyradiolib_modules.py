import pprint

import pytest

import pyradiolib
from pyradiolib.modules import SX1262


class TestPyRadioLibModules:
    def test_sx1262_begin(self, hal):
        module = pyradiolib.Module(hal, 1, 255, 255)
        assert module is not None

        radio = SX1262(module)
        assert radio is not None

        try:
            radio.begin()
        except Exception as e:
            pytest.fail(f"SX1262.begin() raised {e}")

        # pytest.(f'Call results: \n{pprint.pformat(hal.agg.mock_calls)}')
