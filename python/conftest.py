import pytest

from pyradiolib import Module
from python.MockPyHal.hal import PyMockHal


@pytest.fixture
def hal():
    return PyMockHal(0, 1, 0, 1, 1, 0)


@pytest.fixture
def module(hal):
    hal.set_pin_name(10, 'ch')
    hal.set_pin_name(11, 'irq')
    hal.set_pin_name(12, 'rst')


    return Module(hal, 10, 0xffffffff, 12)
