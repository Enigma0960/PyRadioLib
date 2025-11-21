import pytest

from pyradiolib import Module, RadioLibHal
from python.mock.hal import PyMockHal


@pytest.fixture
def cpp_hal():
    return RadioLibHal(0, 1, 0, 1, 1, 0)

@pytest.fixture
def hal():
    return PyMockHal(0, 1, 0, 1, 1, 0)


@pytest.fixture
def module(hal):
    hal.set_pin_name(10, 'ch')
    hal.set_pin_name(11, 'irq')
    hal.set_pin_name(12, 'rst')

    hal.set_pin_value(11, 1)


    return Module(hal, 10, 11, 12)
