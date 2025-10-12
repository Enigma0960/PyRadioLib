import pytest
import pyradiolib


class TestPyRadioLibBase:

    def test_hal(self):
        hal = pyradiolib.RadioLibHal(0, 0, 0, 0, 0, 0)
        assert hal is not None

    # def test_module(self):
    #     assert False
    #     module = pyradiolib.Module(
    #         nss=10,
    #         irq=2,
    #         nrst=3,
    #         busy=9,
    #     )
