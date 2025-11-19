import logging
from collections.abc import Callable
from enum import IntEnum
from typing import Optional, Dict, Any, Callable

_LOGGER = logging.getLogger(__name__)


class StandbyMode(IntEnum):
    Rc = 0
    Xosc = 1


NOP_BYTE = b"\xa2"


class MockSX126x:
    def __init__(self, type: str):
        self._type: str = type
        self._standby_mode: StandbyMode = StandbyMode.Rc

        self._output: bytes = b''

    @property
    def commands(self) -> Dict[int, Callable[..., Any]]:
        return {
            0x00: self.nop,  # RADIOLIB_SX126X_CMD_NOP
            0x02: self.clear_irq_status,  # RADIOLIB_SX126X_CMD_CLEAR_IRQ_STATUS
            0x08: self.set_dio_irq_param,  # RADIOLIB_SX126X_CMD_SET_DIO_IRQ_PARAMS
            0x11: self.get_packet_type,  # RADIOLIB_SX126X_CMD_GET_PACKET_TYPE
            0x0d: self.write_register,  # RADIOLIB_SX126X_CMD_WRITE_REGISTER
            0x17: self.get_device_errors,  # RADIOLIB_SX126X_CMD_GET_DEVICE_ERRORS
            0x1d: self.read_register,  # RADIOLIB_SX126X_CMD_READ_REGISTER
            0x80: self.set_standby,  # RADIOLIB_SX126X_CMD_SET_STANDBY
            0x88: self.set_cmd_param,  # RADIOLIB_SX126X_CMD_SET_CAD_PARAMS
            0x89: self.calibrate,  # RADIOLIB_SX126X_CMD_CALIBRATE
            0x8a: self.set_packet_type,  # RADIOLIB_SX126X_CMD_SET_PACKET_TYPE
            0x8f: self.set_buffer_base_address,  # RADIOLIB_SX126X_CMD_SET_BUFFER_BASE_ADDRESS
            0x93: self.set_rx_tx_fallback_mode,  # RADIOLIB_SX126X_CMD_SET_RX_TX_FALLBACK_MODE
            0x96: self.set_regulator_mode,  # RADIOLIB_SX126X_CMD_SET_REGULATOR_MODE
            0x97: self.set_dio3_as_tcx0_ctrl,  # RADIOLIB_SX126X_CMD_SET_DIO3_AS_TCXO_CTRL
            0xc0: self.get_status,  # RADIOLIB_SX126X_CMD_GET_STATUS
        }

    @property
    def registers(self) -> Dict[int, bytes]:
        return {
            0x0320: b"\xa2\xa2\xa2\xa2\x53\x58\x31\x32\x36\x31\20\x56\x32\x44\x20\x32\x44\x30\x32\x00",

        }


    def _normalize(self, data: bytes, len_: int) -> bytes:
        if len(data) < len_:
            data = NOP_BYTE * (len_ - len(data)) + data
        elif len(data) > len_:
            data = data[:len_]
            _LOGGER.warning(f"SX126x._normalize: data too long: {len(data)} > {len_}")
        return data

    def _pop(self) -> Optional[bytes]:
        if len(self._output) > 0:
            out = self._output
            self._output = b''
            return out
        else:
            return None

    def _push(self, data: int | bytes, len_: int) -> None:
        if isinstance(data, int):
             data = bytes([data])

        self._output += self._normalize(data, len_)



    def nop(self, payload: bytes, len_: int):
        self._push(NOP_BYTE, len_)
        return self._pop()

    def write_register(self, payload: bytes, len_: int):

        return self._pop()

    def read_register(self, payload: bytes, len_: int):
        addr = int.from_bytes(payload[0:2])

        if addr in self.registers.keys():
            self._push(self.registers[addr], len_)

        return self._pop()

    def set_standby(self, payload: int, len_: int):
        self._standby_mode = StandbyMode(payload)
        _LOGGER.debug(f"SX126x.SetStandby({self._standby_mode.name})")
        self._push(b"\xa2\xa2", len_)
        return self._pop()

    def clear_irq_status(self, payload: bytes, len_: int):
        pass

    def set_dio_irq_param(self, payload: bytes, len_: int):
        pass

    def get_packet_type(self, payload: bytes, len_: int):
        pass

    def set_packet_type(self, payload: bytes, len_: int):
        pass

    def set_buffer_base_address(self, payload: bytes, len_: int):
        pass

    def set_rx_tx_fallback_mode(self, payload: bytes, len_: int):
        pass

    def set_regulator_mode(self, payload: bytes, len_: int):
        pass

    def set_dio3_as_tcx0_ctrl(self, payload: bytes, len_: int):
        data = b"\x00\x20"
        self._push(data, len_)
        return self._pop()

    def get_status(self,  payload: bytes, len_: int):
        pass

    def calibrate(self,  payload: bytes, len_: int):
        pass

    def set_cmd_param(self,  payload: bytes, len_: int):
        pass

    def get_device_errors(self,  payload: bytes, len_: int):
        self._push(b"\x00\x20", len_)
        return self._pop()
