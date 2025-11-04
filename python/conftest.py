from typing import Callable

import pytest

from unittest.mock import MagicMock

from pyradiolib import RadioLibHal


class PyMockHal(RadioLibHal):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self._agg = MagicMock(name='hal')

        self._millis = 0

    @property
    def agg(self) -> MagicMock:
        return self._agg

    def pinMode(self, pin: int, mode: int) -> None:
        self._agg.pinMode(pin, mode)

    def digitalWrite(self, pin: int, value: int) -> None:
        self._agg.digitalWrite(pin, value)

    def digitalRead(self, pin: int) -> int:
        return self._agg.digitalRead(pin)

    def attachInterrupt(self, interruptNum: int, interruptCb: Callable, mode: int) -> None:
        self._agg.attachInterrupt(interruptNum, interruptCb, mode)

    def detachInterrupt(self, interruptNum: int) -> None:
        self._agg.detachInterrupt(interruptNum)

    def delay(self, ms: int) -> None:
        self._agg.delay(ms)
        self._millis += int(ms)

    def delayMicroseconds(self, us: int) -> None:
        self._agg.delayMicroseconds(us)
        self._millis += int(us // 1000)

    def millis(self) -> int:
        self._agg.millis()
        return self._millis

    def micros(self) -> int:
        return self._agg.micros()

    def pulseIn(self, pin: int, state: int, timeout: int) -> int:
        return self._agg.pulseIn(pin, state, timeout)

    def spiBegin(self):
        self._agg.spiBegin()

    def spiBeginTransaction(self):
        self._agg.spiBeginTransaction()

    def spiTransfer(self, out, len, in_):
        self._agg.spiTransfer(out, len, in_)

    def spiEndTransaction(self):
        self._agg.spiEndTransaction()

    def spiEnd(self):
        self._agg.spiEnd()

    def init(self):
        self._agg.init()

    def term(self):
        self._agg.term()

    def tone(self, pin, frequency, duration):
        self._agg.tone(pin, frequency, duration)

    def noTone(self, pin):
        self._agg.noTone(pin)

    def yield_(self):
        self._agg.yield_()

    def pinToInterrupt(self, pin) -> int:
        return self._agg.pinToInterrupt(pin)


@pytest.fixture
def hal():
    return PyMockHal(0, 1, 0, 1, 1, 0)
