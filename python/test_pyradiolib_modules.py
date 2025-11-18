import pprint

import pytest

import pyradiolib
from pyradiolib.modules import (
    SX1261,
    SX1262,
    SX1268,
    SX126x
)
from python.conftest import PyMockHal

RADIO_PARAMS = {
    "sx1261": dict(cls=SX1261,
                   min_power=-17, max_power=15,
                   min_clipped_power=-17, max_clipped_power=15,
                   min_test_power=-18, max_test_power=16),
    "sx1262": dict(cls=SX1262,
                   min_power=-9, max_power=22,
                   min_clipped_power=-9, max_clipped_power=22,
                   min_test_power=-10, max_test_power=23),
    "sx1268": dict(cls=SX1268,
                   min_power=-9, max_power=22,
                   min_clipped_power=-9, max_clipped_power=22,
                   min_test_power=-10, max_test_power=23),
}


def set_power(
        hal: PyMockHal,
        radio: SX1261 | SX1262 | SX1268 | SX126x,
        min_power: int, max_power: int,
        min_test_power: int, max_test_power: int,
):
    for power in range(min_test_power, max_test_power):
        res = radio.setOutputPower(power)

        if min_power <= power <= max_power:
            assert res == 0
        else:
            assert res == -13  # RADIOLIB_ERR_INVALID_OUTPUT_POWER
            return

        if power < min_power:
            _power = min_power
        elif power > max_power:
            _power = max_power
        else:
            _power = power

        if _power < 0:
            _power = 256 + _power

        assert len(hal.agg.mock_calls) >= 22
        assert hal.agg.mock_calls[22][0] == "spiTransfer"
        assert hal.agg.mock_calls[22][1] == (_power, 2, 0)

        hal.agg.mock_calls.clear()


def check_output_power(
        radio: SX1261 | SX1262 | SX1268 | SX126x,
        min_power: int, max_power: int,
        min_test_power: int, max_test_power: int,
):
    for power in range(min_test_power, max_test_power):
        res, clipped = radio.checkOutputPower(power)

        if min_power <= power <= max_power:
            assert res == 0
        else:
            assert res == -13  # RADIOLIB_ERR_INVALID_OUTPUT_POWER
            return

        if power < min_power:
            _power = min_power
        elif power > max_power:
            _power = max_power
        else:
            _power = power

        assert _power == clipped


@pytest.fixture(params=RADIO_PARAMS.values(), ids=RADIO_PARAMS.keys())
def radio_case(request, module: pyradiolib.Module):
    p = request.param
    radio = p["cls"](module)
    assert radio is not None
    return radio, p


class TestSx1261:
    # def test_begin(self, radio_case):
    #     radio, param = radio_case

    def test_set_output_power(self, radio_case, hal: PyMockHal):
        radio, param = radio_case
        set_power(
            hal=hal,
            radio=radio,
            min_power=param["min_power"],
            max_power=param["max_power"],
            min_test_power=param["min_test_power"],
            max_test_power=param["max_test_power"],
        )

    def test_check_output_power(self, radio_case):
        radio, param = radio_case
        check_output_power(
            radio=radio,
            min_power=param["min_power"],
            max_power=param["max_power"],
            min_test_power=param["min_test_power"],
            max_test_power=param["max_test_power"],
        )

# def set_power(radio: SX1261 | SX1262 | SX1268 | SX126x, hal: PyMockHal, min_power: int, max_power: int):
#     for power in range(min_power, max_power):
#         res = radio.setOutputPower(power)
#
#         assert res == 0
#
#         assert len(hal.agg.mock_calls) >= 22
#
#         assert hal.agg.mock_calls[22][0] == "spiTransfer"
#         assert hal.agg.mock_calls[22][1] == (power if power >= 0 else 256 + power, 2, 0)
#
#         hal.agg.mock_calls.clear()

# class TestPyRadioLibModules:
#     def test_sx1262_begin(self, hal: PyMockHal, module: PyMockHal):
#         radio = SX1262(module)
#         assert radio is not None
#
#         try:
#             radio.begin()
#         except Exception as e:
#             pytest.fail(f"SX1262.begin() raised {e}")
#
#         # pytest.exit(f'Call results: \n{pprint.pformat(hal.agg.mock_calls)}')
#
#
# class TestSx1261:
#     def test_begin(self, module):
#         radio = SX1261(module)
#         assert radio is not None
#
#     def test_set_output_power(self, hal: PyMockHal, module: pyradiolib.Module):
#         radio = SX1261(module)
#
#         set_power(radio, hal, -17, 15)
#
#     def test_check_output_power(self, hal: PyMockHal, module: pyradiolib.Module):
#         radio = SX1261(module)
#
#         for power in range(-17, 15):
#             res, clipped = radio.checkOutputPower(power)
#             assert res == 0
#             assert power == clipped
#
#         res, clipped = radio.checkOutputPower(-20)
#         assert clipped == -17
#
#         res, clipped = radio.checkOutputPower(20)
#         assert clipped == 15
#
#
# class TestSx1262:
#     pass
#
#
# class TestSx1268:
#     def test_begin(self, module):
#         radio = SX1268(module)
#         assert radio is not None
#
#     def test_set_output_power(self, hal: PyMockHal, module: pyradiolib.Module):
#         radio = SX1268(module)
#
#         set_power(radio, hal, -9, 22)
#
#     def test_check_output_power(self, hal: PyMockHal, module: pyradiolib.Module):
#         radio = SX1268(module)
#
#         for power in range(-9, 22):
#             res, clipped = radio.checkOutputPower(power)
#             assert res == 0
#             assert power == clipped
#
#         res, clipped = radio.checkOutputPower(-20)
#         assert clipped == -9
#
#         res, clipped = radio.checkOutputPower(20)
#         assert clipped == 20
