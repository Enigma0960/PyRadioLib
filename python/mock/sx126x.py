import logging
from dataclasses import dataclass, field
from typing import Optional, Dict, Any, Callable

from pyradiolib.modules import Sx126xCommands
from python.mock.module import MockModule, StandbyMode

_LOGGER = logging.getLogger(__name__)

NOP_BYTE = b"\xa2"

REGISTER_0_DEFAULT_MAP = {
    0x0320: b"SX1261 V2D 2D02\x00"
}


@dataclass
class ModuleParameters:
    standby_mode: StandbyMode = StandbyMode.Default


@dataclass
class ModuleRegisters:
    register_0: Dict[int, bytes] = field(default_factory=dict)
    register_1: Dict[int, bytes] = field(default_factory=dict)


class MockSX126x(MockModule):
    def __init__(self, type: str):
        self._type: str = type

        self._output: bytes = b""
        self._current_len: int = 0

        self._parameters: ModuleParameters = ModuleParameters()

        self._register: ModuleRegisters = ModuleRegisters()
        self._register.register_0 = REGISTER_0_DEFAULT_MAP

    def _normalize(self, data: bytes) -> bytes:
        if len(data) < self._current_len:
            data = NOP_BYTE * (self._current_len - len(data)) + data
        elif len(data) > self._current_len:
            data = data[:self._current_len]
            _LOGGER.warning(f"SX126x._normalize: data too long: {len(data)} > {self._current_len}")
        return data

    def _pop(self) -> Optional[bytes]:
        if len(self._output) > 0:
            out = self._normalize(self._output)
            self._output = b''
            return out
        else:
            return None

    def _push(self, data: int | bytes) -> None:
        if isinstance(data, int):
            data = bytes([data])
        self._output += self._normalize(data)

    def transfer(self, data: bytes) -> Optional[bytes]:
        self._current_len = len(data)

        command_handlers: Dict[Sx126xCommands, Callable[[bytes], Any]] = {
            # operational modes commands
            Sx126xCommands.Nop: self._cmd_nop,
            Sx126xCommands.SetSleep: self._cmd_set_sleep,
            Sx126xCommands.SetStandby: self._cmd_set_standby,
            Sx126xCommands.SetFs: self._cmd_set_fs,
            Sx126xCommands.SetTx: self._cmd_set_tx,
            Sx126xCommands.SetRx: self._cmd_set_rx,
            Sx126xCommands.StopTimerOnPreamble: self._cmd_set_timer_on_preamble,
            Sx126xCommands.SetRxDutyCycle: self._cmd_set_rx_duty_cycle,
            Sx126xCommands.SetCad: self._cmd_set_cad,
            Sx126xCommands.SetTxContinuousWave: self._cmd_set_tx_continuous_wave,
            Sx126xCommands.SetTxInfinitePreamble: self._cmd_set_tx_infinite_preamble,
            Sx126xCommands.SetRegulatorMode: self._cmd_set_regulator_mode,
            Sx126xCommands.Calibrate: self._cmd_calibrate,
            Sx126xCommands.CalibrateImage: self._cmd_calibrate_image,
            Sx126xCommands.SetPaConfig: self._cmd_set_pa_config,
            Sx126xCommands.SetRxTxFallbackMode: self._cmd_set_rx_tx_fallback_mode,

            # operational modes commands
            Sx126xCommands.WriteRegister: self._cmd_write_register,
            Sx126xCommands.ReadRegister: self._cmd_read_registor,
            Sx126xCommands.WriteBuffer: self._cmd_write_buffer,
            Sx126xCommands.ReadBuffer: self._cmd_read_buffer,

            # DIO and IRQ control
            Sx126xCommands.SetDioIrqParams: self._cmd_set_dio_irq_params,
            Sx126xCommands.GetIrqStatus: self._cmd_get_irq_status,
            Sx126xCommands.ClearIrqStatus: self._cmd_clear_irq_status,
            Sx126xCommands.SetDio2AsRfSwitchCtrl: self._cmd_set_dio2_as_rf_switch_ctrl,
            Sx126xCommands.SetDio3AsTcxoCtrl: self._cmd_set_dio3_as_tcxo_ctrl,

            # RF, modulation and packet commands
            Sx126xCommands.SetRfFrequency: self._cmd_set_rf_frequency,
            Sx126xCommands.SetPacketType: self._cmd_set_packet_type,
            Sx126xCommands.GetPacketType: self._cmd_get_packet_type,
            Sx126xCommands.SetTxParams: self._cmd_set_tx_params,
            Sx126xCommands.SetModulationParams: self._cmd_set_modulation_params,
            Sx126xCommands.SetPacketParams: self._cmd_set_packet_params,
            Sx126xCommands.SetCadParams: self._cmd_set_cad_params,
            Sx126xCommands.SetBufferBaseAddress: self._cmd_set_buffer_base_address,
            Sx126xCommands.SetLoraSymbNumTimeout: self._cmd_set_lora_symb_num_timeout,

            # status commands
            Sx126xCommands.GetStatus: self._cmd_get_status,
            Sx126xCommands.GetRssiInst: self._cmd_get_rssi_inst,
            Sx126xCommands.GetRxBufferStatus: self._cmd_get_rx_buffer_status,
            Sx126xCommands.GetPacketStatus: self._cmd_get_packet_status,
            Sx126xCommands.GetDeviceErrors: self._cmd_get_device_error,
            Sx126xCommands.ClearDeviceErrors: self._cmd_clear_device_error,
            Sx126xCommands.GetStats: self._cmd_get_stats,
            # Sx126xCommands.ResetStats:self._cmd_reset_stats,
            Sx126xCommands.PramUpdate: self._cmd_pram_update,
            Sx126xCommands.SetLbtScanParams: self._cmd_set_lbt_scan_params,
            Sx126xCommands.SetSpectrScanParams: self._cmd_set_spectr_scan_params,
        }

        try:
            command: Sx126xCommands = Sx126xCommands(data[0])
        except ValueError:
            _LOGGER.warning(f"SX126x.transfer: unknown command: {data[0]}")
            return None
        data = data[1:]

        if command not in command_handlers.keys():
            return None

        try:
            command_handlers[command](data)
        except Exception as e:
            _LOGGER.warning(f"SX126x.transfer: command handler error: {e}")
            return None

        return self._pop()

    def _read_register(self, addr: int) -> Optional[bytes]:
        if addr in self._register.register_0.keys():
            return self._register.register_0[addr]
        elif addr in self._register.register_1.keys():
            return self._register.register_1[addr]
        else:
            return None

    def _write_register(self, addr: int, value: int):
        pass

    def _cmd_nop(self, data: bytes):
        self._push(NOP_BYTE)

    def _cmd_set_sleep(self, data: bytes):
        pass

    def _cmd_set_standby(self, data: bytes):
        try:
            self._parameters.standby_mode = StandbyMode(data[0])
        except ValueError:
            _LOGGER.warning(f"SX126x.SetStandby: unknown standby mode: {data[0]}")
            return

    def _cmd_set_fs(self, data: bytes):
        pass

    def _cmd_set_tx(self, data: bytes):
        pass

    def _cmd_set_rx(self, data: bytes):
        pass

    def _cmd_set_timer_on_preamble(self, data: bytes):
        pass

    def _cmd_set_rx_duty_cycle(self, data: bytes):
        pass

    def _cmd_set_cad(self, data: bytes):
        pass

    def _cmd_set_tx_continuous_wave(self, data: bytes):
        pass

    def _cmd_set_tx_infinite_preamble(self, data: bytes):
        pass

    def _cmd_set_regulator_mode(self, data: bytes):
        pass

    def _cmd_calibrate(self, data: bytes):
        pass

    def _cmd_calibrate_image(self, data: bytes):
        pass

    def _cmd_set_pa_config(self, data: bytes):
        pass

    def _cmd_set_rx_tx_fallback_mode(self, data: bytes):
        pass

    def _cmd_write_register(self, data: bytes):
        register_addr = int.from_bytes(data[0:2])
        register_value = int.from_bytes(data[2:])

        self._write_register(
            register_addr,
            register_value
        )

    def _cmd_read_registor(self, data: bytes):
        register_addr = int.from_bytes(data[0:2])
        value = self._read_register(register_addr)
        if value is None:
            _LOGGER.warning(f"SX126x.ReadRegister: register {register_addr} not found")
            return

        self._push(value)

    def _cmd_write_buffer(self, data: bytes):
        pass

    def _cmd_read_buffer(self, data: bytes):
        pass

    def _cmd_set_dio_irq_params(self, data: bytes):
        pass

    def _cmd_get_irq_status(self, data: bytes):
        pass

    def _cmd_clear_irq_status(self, data: bytes):
        pass

    def _cmd_set_dio2_as_rf_switch_ctrl(self, data: bytes):
        pass

    def _cmd_set_dio3_as_tcxo_ctrl(self, data: bytes):
        pass

    def _cmd_set_rf_frequency(self, data: bytes):
        pass

    def _cmd_set_packet_type(self, data: bytes):
        pass

    def _cmd_get_packet_type(self, data: bytes):
        pass

    def _cmd_set_tx_params(self, data: bytes):
        pass

    def _cmd_set_modulation_params(self, data: bytes):
        pass

    def _cmd_set_packet_params(self, data: bytes):
        pass

    def _cmd_set_cad_params(self, data: bytes):
        pass

    def _cmd_set_buffer_base_address(self, data: bytes):
        pass

    def _cmd_set_lora_symb_num_timeout(self, data: bytes):
        pass

    def _cmd_get_device_error(self, data: bytes):
        self._push(b"\x00\x20")

    def _cmd_get_status(self, data: bytes):
        pass

    def _cmd_get_rssi_inst(self, data: bytes):
        pass

    def _cmd_get_rx_buffer_status(self, data: bytes):
        pass

    def _cmd_get_packet_status(self, data: bytes):
        pass

    def _cmd_clear_device_error(self, data: bytes):
        pass

    def _cmd_get_stats(self, data: bytes):
        pass

    # def _cmd_reset_stats(self, data: bytes):
    #     pass

    def _cmd_pram_update(self, data: bytes):
        pass

    def _cmd_set_lbt_scan_params(self, data: bytes):
        pass

    def _cmd_set_spectr_scan_params(self, data: bytes):
        pass

    # def nop(self, payload: bytes, len_: int):
    #     self._push(NOP_BYTE, len_)
    #     return self._pop()
    #
    # def write_register(self, payload: bytes, len_: int):
    #
    #     return self._pop()
    #
    # def read_register(self, payload: bytes, len_: int):
    #     addr = int.from_bytes(payload[0:2])
    #
    #     if addr in self.registers.keys():
    #         self._push(self.registers[addr], len_)
    #
    #     return self._pop()
    #
    # def set_standby(self, payload: int, len_: int):
    #     self._standby_mode = StandbyMode(payload)
    #     _LOGGER.debug(f"SX126x.SetStandby({self._standby_mode.name})")
    #     self._push(b"\xa2\xa2", len_)
    #     return self._pop()
    #
    # def clear_irq_status(self, payload: bytes, len_: int):
    #     self._push(b"", len_)
    #     return self._pop()
    #
    # def set_dio_irq_param(self, payload: bytes, len_: int):
    #     self._push(b"", len_)
    #     return self._pop()
    #
    # def get_packet_type(self, payload: bytes, len_: int):
    #     self._push(b"\x11", len_)
    #     return self._pop()
    #
    # def set_packet_type(self, payload: bytes, len_: int):
    #     self._push(b"", len_)
    #     return self._pop()
    #
    # def set_buffer_base_address(self, payload: bytes, len_: int):
    #     self._push(b"", len_)
    #     return self._pop()
    #
    # def set_rx_tx_fallback_mode(self, payload: bytes, len_: int):
    #     self._push(b"", len_)
    #     return self._pop()
    #
    # def set_regulator_mode(self, payload: bytes, len_: int):
    #     self._push(b"", len_)
    #     return self._pop()
    #
    # def set_dio3_as_tcx0_ctrl(self, payload: bytes, len_: int):
    #     data = b"\x00\x20"
    #     self._push(data, len_)
    #     return self._pop()
    #
    # def get_status(self, payload: bytes, len_: int):
    #     self._push(b"\x22\x22", len_)
    #     return self._pop()
    #
    # def calibrate(self, payload: bytes, len_: int):
    #     self._push(b"", len_)
    #     return self._pop()
    #
    # def set_cmd_param(self, payload: bytes, len_: int):
    #     self._push(b"", len_)
    #     return self._pop()
    #
    # def get_device_errors(self, payload: bytes, len_: int):
    #     self._push(b"\x00\x20", len_)
    #     return self._pop()
