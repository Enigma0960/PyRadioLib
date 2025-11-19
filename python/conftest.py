import pytest

from pyradiolib import Module
from python.MockPyHal.hal import PyMockHal


@pytest.fixture
def hal():
    return PyMockHal(0, 1, 0, 1, 1, 0)


@pytest.fixture
def module(hal):
    return Module(hal, 10, 11, 12)
