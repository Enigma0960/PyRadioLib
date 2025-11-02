import pytest

from unittest.mock import MagicMock

from pyradiolib import MockHal, RadioLibHal


class PyMockHal(RadioLibHal):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.mock_init = MagicMock('init')
        self.mock_pinMode = MagicMock('pinMode')
        self.mock_digitalWrite = MagicMock('digitalWrite')
        self.mock_digitalRead = MagicMock('digitalRead')
        self.mock_delay = MagicMock('delay')
        self.mock_delayMicroseconds = MagicMock('delayMicroseconds')
        self.mock_analogWrite = MagicMock('analogWrite')
        self.mock_analogRead = MagicMock('analogRead')
        self.mock_setPinMode = MagicMock('setPinMode')
        self.mock_setPinValue = MagicMock('setPinValue')
        self.mock_setPinModeArray = MagicMock('setPinModeArray')

        self._agg = MagicMock(name='hal')
        self._agg.attach_mock(self.mock_init, 'init')
        self._agg.attach_mock(self.mock_pinMode, 'pinMode')
        self._agg.attach_mock(self.mock_digitalWrite, 'digitalWrite')
        self._agg.attach_mock(self.mock_digitalRead, 'digitalRead')
        self._agg.attach_mock(self.mock_delay, 'delay')
        self._agg.attach_mock(self.mock_delayMicroseconds, 'delayMicroseconds')
        self._agg.attach_mock(self.mock_analogWrite, 'analogWrite')
        self._agg.attach_mock(self.mock_analogRead, 'analogRead')
        self._agg.attach_mock(self.mock_setPinMode, 'setPinMode')
        self._agg.attach_mock(self.mock_setPinValue, 'setPinValue')


    @property
    def agg(self) -> MagicMock:
        return self._agg

    def init(self):
        self.mock_init()

    def pinMode(self, pin, mode):
        self.mock_pinMode(pin, mode)

    def digitalWrite(self, pin, value):
        self.mock_digitalWrite(pin, value)

    def digitalRead(self, pin):
        return self.mock_digitalRead(pin)



@pytest.fixture
def hal():
    return PyMockHal(0, 1, 0, 1, 1, 0)
