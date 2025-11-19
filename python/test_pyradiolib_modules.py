import pytest

import pyradiolib
from pyradiolib.modules import (
    SX1261,
    SX1262,
    SX1268,
    SX126x
)
from python.conftest import PyMockHal

RADIO_POWER_PARAMS = {
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

RADIO_BEGIN_PARAMS = {
    # "sx1261": dict(cls=SX1261, ), # Not custom begin
    "sx1262": dict(cls=SX1262, ),
    "sx1268": dict(cls=SX1268, ),
}


@pytest.fixture(
    params=RADIO_BEGIN_PARAMS.values(),
    ids=RADIO_BEGIN_PARAMS.keys(),
)
def radio_begin_case(request, module: pyradiolib.Module):
    param = request.param
    radio = param["cls"](module)
    assert radio is not None
    return radio, param


@pytest.fixture(
    params=RADIO_POWER_PARAMS.values(),
    ids=RADIO_POWER_PARAMS.keys(),
)
def radio_power_case(request, module: pyradiolib.Module):
    param = request.param
    radio = param["cls"](module)
    assert radio is not None
    return radio, param


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


class TestSx126xCustom:
    def test_custom_begin(self, radio_begin_case, hal: PyMockHal):
        radio, param = radio_begin_case

        if param["cls"] == SX1261:
            radio.begin(
                ch=7,
                syncWord=18,
                preambleLength=8,
                tcxoVoltage=1.6,
                useRegulatorLDO=False
            )
        else:
            radio.begin(
                freq=434.0,
                bw=125.0,
                sf=9,
                cr=7,
                syncWord=18,
                power=10,
                preambleLength=8,
                tcxoVoltage=1.6,
                useRegulatorLDO=False
            )

    def test_custom_begin_fsk(self, radio_begin_case, hal: PyMockHal):
        radio, param = radio_begin_case

        radio.beginFSK(
            freq=434.0,
            br=4.0,
            freqDev=5.0,
            rxBw=156.2,
            power=10,
            preambleLength=16,
            tcxoVoltage=1.6,
            useRegulatorLDO=False,
        )

    def test_custom_begin_lrfhss(self, radio_begin_case, hal: PyMockHal):
        radio, param = radio_begin_case

        radio.beginLRFHSS(
            freq=434.0,
            bw=6,
            cr=1,
            narrowGrid=True,
            power=10,
            tcxoVoltage=1.6,
            useRegulatorLDO=False,
        )

    def test_custom_set_output_power(self, radio_power_case, hal: PyMockHal):
        radio, param = radio_power_case
        set_power(
            hal=hal,
            radio=radio,
            min_power=param["min_power"],
            max_power=param["max_power"],
            min_test_power=param["min_test_power"],
            max_test_power=param["max_test_power"],
        )

    def test_custom_check_output_power(self, radio_power_case):
        radio, param = radio_power_case
        check_output_power(
            radio=radio,
            min_power=param["min_power"],
            max_power=param["max_power"],
            min_test_power=param["min_test_power"],
            max_test_power=param["max_test_power"],
        )
