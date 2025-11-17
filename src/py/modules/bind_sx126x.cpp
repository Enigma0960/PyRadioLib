#include "bind_sx126x.h"

#include <py/bind_types.h>
#include <radiolib/modules/SX126x/SX126x.h>

void bind_sx126x(py::module& module) {
	py::class_<SX126x, std::shared_ptr<SX126x>>(module, "SX126x")
	    .def(py::init([](std::shared_ptr<Module> module) {
		    return std::make_shared<SX126x>(module.get());
	    }),
	        py::arg("module"),
	        py::keep_alive<1, 2>())
	    .def("begin", &SX126x::begin,
	        py::arg("ch"),
	        py::arg("syncWord"),
	        py::arg("preambleLength"),
	        py::arg("tcxoVoltage"),
	        py::arg("useRegulatorLDO") = false)
	    .def("beginFSK", &SX126x::beginFSK,
	        py::arg("br"),
	        py::arg("freqDev"),
	        py::arg("rxBw"),
	        py::arg("preambleLength"),
	        py::arg("tcxoVoltage"),
	        py::arg("useRegulatorLDO") = false)
	    .def("beginLRFHS", &SX126x::beginLRFHSS)
	    .def("setLrFhssConfig", &SX126x::beginLRFHSS)
	    .def("reset", &SX126x::reset)
	    .def("transmit", [](SX126x& self, py::buffer const& data, std::uint8_t addr) {
		    py::buffer_info info = data.request();
		    if (info.ndim != 1) {
			    throw py::value_error("data must be 1-D");
		    }
		    if (info.itemsize != 1) {
			    throw py::value_error("element size must be 1 byte");
		    }
		    if (!(info.strides.empty() || info.strides[0] == 1)) {
			    throw py::value_error("data must be C-contiguous");
		    }
		    auto* ptr = static_cast<std::uint8_t const*>(info.ptr);
		    auto len = static_cast<std::size_t>(info.size);
		    py::gil_scoped_release release;
		    return self.transmit(ptr, len, addr); //
	    },
	        py::arg("data"), py::arg("addr") = 0)
	    .def("receive", &SX126x::receive)
	    .def("transmitDirect", &SX126x::transmitDirect)
	    .def("receiveDirect", &SX126x::receiveDirect)
	    .def("scanChannel", py::overload_cast<>(&SX126x::scanChannel))
	    // .def("scanChannel", py::overload_cast<>(&SX126x::scanChannel))
	    .def("sleep", py::overload_cast<>(&SX126x::sleep))
	    .def("sleep", py::overload_cast<bool>(&SX126x::sleep))
	    .def("standby", py::overload_cast<>(&SX126x::standby))
	    .def("standby", py::overload_cast<uint8_t, bool>(&SX126x::standby))
	    .def("hopLRFHSS", &SX126x::hopLRFHSS)
	    // .def("setDio1Action", &SX126x::setDio1Action)
	    .def("clearDio1Action", &SX126x::clearDio1Action)
	    // .def("setPacketReceivedAction", &SX126x::setPacketReceivedAction)
	    .def("clearPacketReceivedAction", &SX126x::clearPacketReceivedAction)
	    // .def("setPacketSentAction", &SX126x::setPacketSentAction)
	    .def("clearPacketSentAction", &SX126x::clearPacketSentAction)
	    // .def("setChannelScanAction", &SX126x::setChannelScanAction)
	    .def("clearChannelScanAction", &SX126x::clearChannelScanAction)
	    .def("finishTransmit", &SX126x::finishTransmit)
	    .def("finishReceive", &SX126x::finishReceive)
	    .def("startReceive", [](SX126x& self) { return self.finishTransmit(); })
	    .def("startReceiveDutyCycle", &SX126x::startReceiveDutyCycle)
	    .def("startReceiveDutyCycleAuto", &SX126x::startReceiveDutyCycleAuto)
	    .def("readData", &SX126x::readData)
	    .def("startChannelScan", py::overload_cast<>(&SX126x::startChannelScan))
	    // .def("startChannelScan",py::overload_cast<>( &SX126x::startChannelScan))
	    .def("getChannelScanResult", &SX126x::getChannelScanResult)
	    .def("setBandwidth", &SX126x::setBandwidth)
	    .def("setSpreadingFactor", &SX126x::setSpreadingFactor)
	    .def("setCodingRate", &SX126x::setCodingRate)
	    .def("setSyncWord", py::overload_cast<uint8_t, uint8_t>(&SX126x::setSyncWord))
	    .def("setCurrentLimit", &SX126x::setCurrentLimit)
	    .def("getCurrentLimit", &SX126x::getCurrentLimit)
	    .def("setPreambleLength", &SX126x::setPreambleLength)
	    .def("setFrequencyDeviation", &SX126x::setFrequencyDeviation)
	    .def("setBitRate", &SX126x::setBitRate)
	    // .def("setDataRate", &SX126x::setDataRate)
	    // .def("checkDataRate", &SX126x::checkDataRate)
	    .def("setRxBandwidth", &SX126x::setRxBandwidth)
	    .def("setRxBoostedGainMode", &SX126x::setRxBoostedGainMode)
	    .def("setDataShaping", &SX126x::setDataShaping)
	    .def("setSyncBits", &SX126x::setSyncBits)
	    .def("setCRC", &SX126x::setCRC)
	    .def("setWhitening", &SX126x::setWhitening)
	    .def("setTCXO", &SX126x::setTCXO)
	    .def("setDio2AsRfSwitch", &SX126x::setDio2AsRfSwitch)
	    .def("getDataRate", &SX126x::getDataRate)
	    .def("getRSSI", py::overload_cast<>(&SX126x::getRSSI))
	    .def("getRSSI", py::overload_cast<bool>(&SX126x::getRSSI))
	    .def("getSNR", &SX126x::getSNR)
	    .def("getFrequencyError", &SX126x::getFrequencyError)
	    .def("getPacketLength", py::overload_cast<bool>(&SX126x::getPacketLength))
	    //.def("getPacketLength", py::overload_cast<bool, >(&SX126x::getPacketLength))
	    .def("getLoRaRxHeaderInfo", &SX126x::getLoRaRxHeaderInfo)
	    .def("fixedPacketLengthMode", &SX126x::fixedPacketLengthMode)
	    .def("variablePacketLengthMode", &SX126x::variablePacketLengthMode)
	    // .def("calculateTimeOnAir", &SX126x::calculateTimeOnAir)
	    .def("getTimeOnAir", &SX126x::getTimeOnAir)
	    .def("calculateRxTimeout", &SX126x::calculateRxTimeout)
	    .def("getIrqFlags", &SX126x::getIrqFlags)
	    .def("setIrqFlags", &SX126x::setIrqFlags)
	    .def("clearIrqFlags", &SX126x::clearIrqFlags)
	    .def("implicitHeader", &SX126x::implicitHeader)
	    .def("explicitHeader", &SX126x::explicitHeader)
	    .def("setRegulatorLDO", &SX126x::setRegulatorLDO)
	    .def("setRegulatorDCDC", &SX126x::setRegulatorDCDC)
	    .def("setEncoding", &SX126x::setEncoding)
	    .def("setRfSwitchPins", &SX126x::setRfSwitchPins)
	    // .def("setRfSwitchTable", &SX126x::setRfSwitchTable)
	    .def("forceLDRO", &SX126x::forceLDRO)
	    .def("autoLDRO", &SX126x::autoLDRO)
	    .def("randomByte", &SX126x::randomByte)
	    .def("invertIQ", &SX126x::invertIQ)
	    .def("getModem", &SX126x::getModem)
	    // .def("stageMode", &SX126x::stageMode)
	    .def("launchMode", &SX126x::launchMode)
	    // .def("setDirectAction", &SX126x::setDirectAction)
	    .def("readBit", &SX126x::readBit)
	    .def("uploadPatch", &SX126x::uploadPatch)
	    .def("spectralScanStart", &SX126x::spectralScanStart)
	    .def("spectralScanAbort", &SX126x::spectralScanAbort)
	    .def("spectralScanGetStatus", &SX126x::spectralScanGetStatus)
	    .def("spectralScanGetResult", &SX126x::spectralScanGetResult)
	    .def("setPaConfig", &SX126x::setPaConfig)
	    .def("calibrateImage", py::overload_cast<float>(&SX126x::calibrateImage))
	    .def("calibrateImageRejection", &SX126x::calibrateImageRejection)
	    .def("setPaRampTime", &SX126x::setPaRampTime);
}
