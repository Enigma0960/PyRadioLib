import logging
import time
from enum import IntEnum
from typing import Callable, Dict, Tuple, Optional, Union, Any, List
from pyradiolib import RadioLibHal
from unittest.mock import MagicMock, _Call

from python.mock.sx126x import MockSX126x
from python.mock.module import MockModule

_LOGGER = logging.getLogger(__name__)


class PinMode(IntEnum):
    Input = 0
    Output = 1
    Disable = 255


class PinType(IntEnum):
    Digital = 0
    Analog = 1
    Pwm = 2


class PinInfo:
    name: str = ""
    mode: PinMode = PinMode.Input
    type: PinType = PinType.Digital
    value: Tuple[int, float] = 0


class PyMockHal(RadioLibHal):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self._agg: MagicMock = MagicMock(name='hal')
        self._millis: int = 0
        self._modem_type: Optional[str] = None
        self._modem: Optional[MockModule] = None

        self._pins_map: Dict[int, PinInfo] = {}

    @property
    def agg(self) -> MagicMock:
        return self._agg

    def set_pin_name(self, pin: int, name: str) -> None:
        if pin == 0xffffffff:
            return
        if pin not in self._pins_map:
            self._pins_map[pin] = PinInfo()
        self._pins_map[pin].name = name

    def set_modem_type(self, modem_type: str) -> None:
        self._modem_type = modem_type

        modems = {
            "sx1261": MockSX126x,
        }

        if modem_type in modems.keys():
            self._modem = modems[modem_type](type=modem_type)

    def pinMode(self, pin: int, mode: int) -> None:
        if pin == 0xffffffff:
            return

        if pin not in self._pins_map:
            self._pins_map[pin] = PinInfo()

        self._pins_map[pin].mode = PinMode(mode)

        self._agg.pinMode(pin, mode)

    def digitalWrite(self, pin: int, value: int) -> None:
        if pin == 0xffffffff:
            return

        if pin not in self._pins_map:
            self._pins_map[pin] = PinInfo()
        self._pins_map[pin].value = value

        self._agg.digitalWrite(pin, value)


    def digitalRead(self, pin: int) -> int:
        if pin == 0xffffffff:
            return 0

        if pin not in self._pins_map:
            self._pins_map[pin] = PinInfo()
        self._agg.digitalRead.return_value = self._pins_map[pin].value

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
        self.agg.millis.return_value = self._millis
        return self._agg.millis()

    def micros(self) -> int:
        self.agg.micros.return_value = self._millis * 1000
        return self._agg.micros()

    def pulseIn(self, pin: int, state: int, timeout: int) -> int:
        return self._agg.pulseIn(pin, state, timeout)

    def spiBegin(self):
        self._agg.spiBegin()

    def spiBeginTransaction(self):
        self._agg.spiBeginTransaction()

    def spiTransfer(self, out: bytes):
        if self._modem_type is not None:
            data = self._transfer(out)
            if data is not None:
                self._agg.spiTransfer.return_value = data

        result = self._agg.spiTransfer(out)

        if type(result) is bytes:
            return result
        else:
            return b''

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

    def _transfer(self, data: bytes) -> Optional[bytes]:
        if self._modem_type is None or self._modem is None:
            return None
        return self._modem.transfer(data)
