#include "bind_types.h"

#include <pybind11/native_enum.h>

#include <radiolib/modules/SX126x/SX126x_commands.h>
#include <radiolib/modules/SX126x/SX126x_registers.h>

enum Sx126xCommands : std::uint8_t {
	// operational modes commands
	Nop = RADIOLIB_SX126X_CMD_NOP,
	SetSleep = RADIOLIB_SX126X_CMD_SET_SLEEP,
	SetStandby = RADIOLIB_SX126X_CMD_SET_STANDBY,
	SetFs = RADIOLIB_SX126X_CMD_SET_FS,
	SetTx = RADIOLIB_SX126X_CMD_SET_TX,
	SetRx = RADIOLIB_SX126X_CMD_SET_RX,
	StopTimerOnPreamble = RADIOLIB_SX126X_CMD_STOP_TIMER_ON_PREAMBLE,
	SetRxDutyCycle = RADIOLIB_SX126X_CMD_SET_RX_DUTY_CYCLE,
	SetCad = RADIOLIB_SX126X_CMD_SET_CAD,
	SetTxContinuousWave = RADIOLIB_SX126X_CMD_SET_TX_CONTINUOUS_WAVE,
	SetTxInfinitePreamble = RADIOLIB_SX126X_CMD_SET_TX_INFINITE_PREAMBLE,
	SetRegulatorMode = RADIOLIB_SX126X_CMD_SET_REGULATOR_MODE,
	Calibrate = RADIOLIB_SX126X_CMD_CALIBRATE,
	CalibrateImage = RADIOLIB_SX126X_CMD_CALIBRATE_IMAGE,
	SetPaConfig = RADIOLIB_SX126X_CMD_SET_PA_CONFIG,
	SetRxTxFallbackMode = RADIOLIB_SX126X_CMD_SET_RX_TX_FALLBACK_MODE,
	// operational modes commands
	WriteRegister = RADIOLIB_SX126X_CMD_WRITE_REGISTER,
	ReadRegister = RADIOLIB_SX126X_CMD_READ_REGISTER,
	WriteBuffer = RADIOLIB_SX126X_CMD_WRITE_BUFFER,
	ReadBuffer = RADIOLIB_SX126X_CMD_READ_BUFFER,
	// DIO and IRQ control
	SetDioIrqParams = RADIOLIB_SX126X_CMD_SET_DIO_IRQ_PARAMS,
	GetIrqStatus = RADIOLIB_SX126X_CMD_GET_IRQ_STATUS,
	ClearIrqStatus = RADIOLIB_SX126X_CMD_CLEAR_IRQ_STATUS,
	SetDio2AsRfSwitchCtrl = RADIOLIB_SX126X_CMD_SET_DIO2_AS_RF_SWITCH_CTRL,
	SetDio3AsTcxoCtrl = RADIOLIB_SX126X_CMD_SET_DIO3_AS_TCXO_CTRL,
	// RF, modulation and packet commands
	SetRfFrequency = RADIOLIB_SX126X_CMD_SET_RF_FREQUENCY,
	SetPacketType = RADIOLIB_SX126X_CMD_SET_PACKET_TYPE,
	GetPacketType = RADIOLIB_SX126X_CMD_GET_PACKET_TYPE,
	SetTxParams = RADIOLIB_SX126X_CMD_SET_TX_PARAMS,
	SetModulationParams = RADIOLIB_SX126X_CMD_SET_MODULATION_PARAMS,
	SetPacketParams = RADIOLIB_SX126X_CMD_SET_PACKET_PARAMS,
	SetCadParams = RADIOLIB_SX126X_CMD_SET_CAD_PARAMS,
	SetBufferBaseAddress = RADIOLIB_SX126X_CMD_SET_BUFFER_BASE_ADDRESS,
	SetLoraSymbNumTimeout = RADIOLIB_SX126X_CMD_SET_LORA_SYMB_NUM_TIMEOUT,
	// status commands
	GetStatus = RADIOLIB_SX126X_CMD_GET_STATUS,
	GetRssiInst = RADIOLIB_SX126X_CMD_GET_RSSI_INST,
	GetRxBufferStatus = RADIOLIB_SX126X_CMD_GET_RX_BUFFER_STATUS,
	GetPacketStatus = RADIOLIB_SX126X_CMD_GET_PACKET_STATUS,
	GetDeviceErrors = RADIOLIB_SX126X_CMD_GET_DEVICE_ERRORS,
	ClearDeviceErrors = RADIOLIB_SX126X_CMD_CLEAR_DEVICE_ERRORS,
	GetStats = RADIOLIB_SX126X_CMD_GET_STATS,
	ResetStats = RADIOLIB_SX126X_CMD_RESET_STATS,
	PramUpdate = RADIOLIB_SX126X_CMD_PRAM_UPDATE,
	SetLbtScanParams = RADIOLIB_SX126X_CMD_SET_LBT_SCAN_PARAMS,
	SetSpectrScanParams = RADIOLIB_SX126X_CMD_SET_SPECTR_SCAN_PARAMS,
};



void bind_sx126x_types(py::module& module) {
	py::native_enum<Sx126xCommands>(module, "Sx126xCommands", "enum.IntEnum")
	    // operational modes commands
	    .value("Nop", Nop)
	    .value("SetSleep", SetSleep)
	    .value("SetStandby", SetStandby)
	    .value("SetFs", SetFs)
	    .value("SetTx", SetTx)
	    .value("SetRx", SetRx)
	    .value("StopTimerOnPreamble", StopTimerOnPreamble)
	    .value("SetRxDutyCycle", SetRxDutyCycle)
	    .value("SetCad", SetCad)
	    .value("SetTxContinuousWave", SetTxContinuousWave)
	    .value("SetTxInfinitePreamble", SetTxInfinitePreamble)
	    .value("SetRegulatorMode", SetRegulatorMode)
	    .value("Calibrate", Calibrate)
	    .value("CalibrateImage", CalibrateImage)
	    .value("SetPaConfig", SetPaConfig)
	    .value("SetRxTxFallbackMode", SetRxTxFallbackMode)
	    // operational modes commands
	    .value("WriteRegister", WriteRegister)
	    .value("ReadRegister", ReadRegister)
	    .value("WriteBuffer", WriteBuffer)
	    .value("ReadBuffer", ReadBuffer)
	    // DIO and IRQ control
	    .value("SetDioIrqParams", SetDioIrqParams)
	    .value("GetIrqStatus", GetIrqStatus)
	    .value("ClearIrqStatus", ClearIrqStatus)
	    .value("SetDio2AsRfSwitchCtrl", SetDio2AsRfSwitchCtrl)
	    .value("SetDio3AsTcxoCtrl", SetDio3AsTcxoCtrl)
	    // RF, modulation and packet commands
	    .value("SetRfFrequency", SetRfFrequency)
	    .value("SetPacketType", SetPacketType)
	    .value("GetPacketType", GetPacketType)
	    .value("SetTxParams", SetTxParams)
	    .value("SetModulationParams", SetModulationParams)
	    .value("SetPacketParams", SetPacketParams)
	    .value("SetCadParams", SetCadParams)
	    .value("SetBufferBaseAddress", SetBufferBaseAddress)
	    .value("SetLoraSymbNumTimeout", SetLoraSymbNumTimeout)
	    // status commands
	    .value("GetStatus", GetStatus)
	    .value("GetRssiInst", GetRssiInst)
	    .value("GetRxBufferStatus", GetRxBufferStatus)
	    .value("GetPacketStatus", GetPacketStatus)
	    .value("GetDeviceErrors", GetDeviceErrors)
	    .value("ClearDeviceErrors", ClearDeviceErrors)
	    .value("GetStats", GetStats)
	    .value("ResetStats", ResetStats)
	    .value("PramUpdate", PramUpdate)
	    .value("SetLbtScanParams", SetLbtScanParams)
	    .value("SetSpectrScanParams", SetSpectrScanParams)
	    .export_values()
	    .finalize();


}
