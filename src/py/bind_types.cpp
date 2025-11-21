#include "bind_types.h"

#include <pybind11/native_enum.h>

enum ModuleStatus : std::int16_t {
	Normal = RADIOLIB_ERR_NONE,
	Unknown = RADIOLIB_ERR_UNKNOWN,
	ChipNotFound = RADIOLIB_ERR_CHIP_NOT_FOUND,
	MemoryAllocationFailed = RADIOLIB_ERR_MEMORY_ALLOCATION_FAILED,
	PacketTooLong = RADIOLIB_ERR_PACKET_TOO_LONG,
	TxTimeout = RADIOLIB_ERR_TX_TIMEOUT,
	RxTimeout = RADIOLIB_ERR_RX_TIMEOUT,
	CrcMismatch = RADIOLIB_ERR_CRC_MISMATCH,
	InvalidBandwidth = RADIOLIB_ERR_INVALID_BANDWIDTH,
	InvalidSpreadingFactor = RADIOLIB_ERR_INVALID_SPREADING_FACTOR,
	InvalidCodingRate = RADIOLIB_ERR_INVALID_CODING_RATE,
	InvalidBitRange = RADIOLIB_ERR_INVALID_BIT_RANGE,
	InvalidFrequency = RADIOLIB_ERR_INVALID_FREQUENCY,
	InvalidOutputPower = RADIOLIB_ERR_INVALID_OUTPUT_POWER,
	PreambleDetected = RADIOLIB_PREAMBLE_DETECTED,
	ChannelFree = RADIOLIB_CHANNEL_FREE,
	SpiWriteFailed = RADIOLIB_ERR_SPI_WRITE_FAILED,
	InvalidCurrentLimit = RADIOLIB_ERR_INVALID_CURRENT_LIMIT,
	InvalidPreambleLength = RADIOLIB_ERR_INVALID_PREAMBLE_LENGTH,
	InvalidGain = RADIOLIB_ERR_INVALID_GAIN,
	WrongModem = RADIOLIB_ERR_WRONG_MODEM,
	InvalidNumSamples = RADIOLIB_ERR_INVALID_NUM_SAMPLES,
	InvalidRssiOffset = RADIOLIB_ERR_INVALID_RSSI_OFFSET,
	InvalidEncoding = RADIOLIB_ERR_INVALID_ENCODING,
	LoraHeaderDamaged = RADIOLIB_ERR_LORA_HEADER_DAMAGED,
	Unsupported = RADIOLIB_ERR_UNSUPPORTED,
	InvalidDioPin = RADIOLIB_ERR_INVALID_DIO_PIN,
};

void bind_types(py::module& module) {
	py::enum_<ModemType>(module, "ModemType", py::arithmetic())
	    .value("RADIOLIB_MODEM_FSK", RADIOLIB_MODEM_FSK)
	    .value("RADIOLIB_MODEM_LORA", RADIOLIB_MODEM_LORA)
	    .value("RADIOLIB_MODEM_LRFHSS", RADIOLIB_MODEM_LRFHSS)
	    .value("RADIOLIB_MODEM_NONE", RADIOLIB_MODEM_NONE);

	py::enum_<RadioModeType>(module, "RadioMode", py::arithmetic())
	    .value("RADIOLIB_RADIO_MODE_NONE", RADIOLIB_RADIO_MODE_NONE)
	    .value("RADIOLIB_RADIO_MODE_STANDBY", RADIOLIB_RADIO_MODE_STANDBY)
	    .value("RADIOLIB_RADIO_MODE_RX", RADIOLIB_RADIO_MODE_RX)
	    .value("RADIOLIB_RADIO_MODE_TX", RADIOLIB_RADIO_MODE_TX)
	    .value("RADIOLIB_RADIO_MODE_SCAN", RADIOLIB_RADIO_MODE_SCAN)
	    .value("RADIOLIB_RADIO_MODE_SLEEP", RADIOLIB_RADIO_MODE_SLEEP);

	py::class_<LoRaRate>(module, "LoRaRate")
	    .def_readwrite("spreadingFactor", &LoRaRate::spreadingFactor)
	    .def_readwrite("bandwidth", &LoRaRate::bandwidth)
	    .def_readwrite("codingRate", &LoRaRate::codingRate);

	py::class_<FSKRate>(module, "FSKRate")
	    .def_readwrite("bitRate", &FSKRate::bitRate)
	    .def_readwrite("freqDev", &FSKRate::freqDev);

	py::class_<LrFhssRate>(module, "LrFhssRate")
	    .def_readwrite("bw", &LrFhssRate::bw)
	    .def_readwrite("cr", &LrFhssRate::cr)
	    .def_readwrite("narrowGrid", &LrFhssRate::narrowGrid);

	py::class_<LoRaPacketConfig>(module, "LoRaPacketConfig")
	    .def_readwrite("crcEnabled", &LoRaPacketConfig::crcEnabled)
	    .def_readwrite("implicitHeader", &LoRaPacketConfig::implicitHeader)
	    .def_readwrite("ldrOptimize", &LoRaPacketConfig::ldrOptimize)
	    .def_readwrite("preambleLength", &LoRaPacketConfig::preambleLength);

	py::class_<FSKPacketConfig>(module, "FSKPacketConfig")
	    .def_readwrite("syncWordLength", &FSKPacketConfig::syncWordLength)
	    .def_readwrite("crcLength", &FSKPacketConfig::crcLength)
	    .def_readwrite("preambleLength", &FSKPacketConfig::preambleLength);

	py::class_<LrFhssPacketConfig>(module, "LrFhssPacketConfig")
	    .def_readwrite("hdrCount", &LrFhssPacketConfig::hdrCount);

	py::class_<CADScanConfig>(module, "CADScanConfig")
	    .def_readwrite("symNum", &CADScanConfig::symNum)
	    .def_readwrite("detPeak", &CADScanConfig::detPeak)
	    .def_readwrite("detMin", &CADScanConfig::detMin)
	    .def_readwrite("exitMode", &CADScanConfig::exitMode)
	    .def_readwrite("timeout", &CADScanConfig::timeout)
	    .def_readwrite("irqFlags", &CADScanConfig::irqFlags)
	    .def_readwrite("irqMask", &CADScanConfig::irqMask);

	py::class_<RSSIScanConfig>(module, "RSSIScanConfig")
	    .def_readwrite("limit", &RSSIScanConfig::limit);

	py::class_<StandbyConfig>(module, "StandbyConfig")
	    .def_readwrite("mode", &StandbyConfig::mode);

	py::class_<ReceiveConfig>(module, "ReceiveConfig")
	    .def_readwrite("irqFlags", &ReceiveConfig::irqFlags)
	    .def_readwrite("irqMask", &ReceiveConfig::irqMask)
	    .def_readwrite("len", &ReceiveConfig::len)
	    .def_readwrite("timeout", &ReceiveConfig::timeout);

	py::class_<TransmitConfig>(module, "TransmitConfig")
	    .def_readwrite("len", &TransmitConfig::len)
	    .def_readwrite("addr", &TransmitConfig::addr)
	    .def_readwrite("data", &TransmitConfig::data);

	py::class_<ChannelScanConfig>(module, "ChannelScanConfig")
	    .def_readwrite("cad", &ChannelScanConfig::cad)
	    .def_readwrite("rssi", &ChannelScanConfig::rssi);

	py::class_<SleepConfig>(module, "SleepConfig")
	    .def_readwrite("mode", &SleepConfig::mode);

	py::native_enum<ModuleStatus>(module, "ModuleStatus", "enum.IntEnum")
	    .value("Normal", Normal)
	    .value("Unknown", Unknown)
	    .value("ChipNotFound", ChipNotFound)
	    .value("MemoryAllocationFailed", MemoryAllocationFailed)
	    .value("PacketTooLong", PacketTooLong)
	    .value("TxTimeout", TxTimeout)
	    .value("RxTimeout", RxTimeout)
	    .value("CrcMismatch", CrcMismatch)
	    .value("InvalidBandwidth", InvalidBandwidth)
	    .value("InvalidSpreadingFactor", InvalidSpreadingFactor)
	    .value("InvalidCodingRate", InvalidCodingRate)
	    .value("InvalidBitRange", InvalidBitRange)
	    .value("InvalidFrequency", InvalidFrequency)
	    .value("InvalidOutputPower", InvalidOutputPower)
	    .value("PreambleDetected", PreambleDetected)
	    .value("ChannelFree", ChannelFree)
	    .value("SpiWriteFailed", SpiWriteFailed)
	    .value("InvalidCurrentLimit", InvalidCurrentLimit)
	    .value("InvalidPreambleLength", InvalidPreambleLength)
	    .value("InvalidGain", InvalidGain)
	    .value("WrongModem", WrongModem)
	    .value("InvalidNumSamples", InvalidNumSamples)
	    .value("InvalidRssiOffset", InvalidRssiOffset)
	    .value("InvalidEncoding", InvalidEncoding)
	    .value("LoraHeaderDamaged", LoraHeaderDamaged)
	    .value("Unsupported", Unsupported)
	    .value("InvalidDioPin", InvalidDioPin)
	    .export_values()
	    .finalize();
}
