import time

import pytest

import pyradiolib
from python.conftest import PyMockHal
from pyradiolib.modules import (
    SX1261,
    SX1262,
    SX1268,
    SX126x,
)
from pyradiolib import ModuleStatus

RADIO_PARAMETERS = {
    "sx1261": dict(cls=SX1261, ),
    "sx1262": dict(cls=SX1262, ),
    "sx1268": dict(cls=SX1268, ),
}


@pytest.fixture(
    params=RADIO_PARAMETERS.values(),
    ids=RADIO_PARAMETERS.keys(),
)
def make_radio(request: pytest.FixtureRequest, module: pyradiolib.Module, hal: PyMockHal):
    hal.set_modem_type(request.node.callspec.id)
    radio = request.param["cls"](module)
    assert radio is not None

    if request.param["cls"] == SX1261:
        status = radio.begin(
            ch=7,
            syncWord=18,
            preambleLength=8,
            tcxoVoltage=1.6,
            useRegulatorLDO=False
        )
    else:
        status = radio.begin(
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

    assert ModuleStatus(status) == ModuleStatus.Normal

    return radio, request.param


class TestSx126xBase:
    def test_scan_channel(self, make_radio, hal: PyMockHal):
        radio, param = make_radio
        radio: SX126x

        try:
            status = radio.scanChannel()
        except Exception as e:
            pytest.fail(f"scanChannel() raised {e.__class__.__name__}: {e}")

        assert ModuleStatus(status) in (ModuleStatus.LoraDetected, ModuleStatus.ChannelFree)