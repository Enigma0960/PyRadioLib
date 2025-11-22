#include "bind_sx126x.h"

#include <filesystem>
#include <py/bind_types.h>
#include <radiolib/modules/SX126x/SX126x.h>

void bind_sx126x(py::module& module) {
	py::class_<SX126x, PhysicalLayer, std::shared_ptr<SX126x>>(module, "SX126x")
	    .def(py::init([](std::shared_ptr<Module> module) {
		    return std::make_shared<SX126x>(module.get());
	    }),
	        py::arg("module"),
	        py::keep_alive<1, 2>())
	    .def("begin", [](SX126x& self, std::uint8_t cr, std::uint8_t syncWord, std::uint16_t preambleLength, float tcxoVoltage, bool useRegulatorLDO) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(
			        self.begin(cr, syncWord, preambleLength, tcxoVoltage, useRegulatorLDO));
		    }
		    return status; //
	    },
	        py::arg("ch"), py::arg("syncWord"), py::arg("preambleLength"), py::arg("tcxoVoltage"), py::arg("useRegulatorLDO") = false)
	    .def("beginFSK", [](SX126x& self, float br, float freqDev, float rxBw, uint16_t preambleLength, float tcxoVoltage, bool useRegulatorLDO) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(
			        self.beginFSK(br, freqDev, rxBw, preambleLength, tcxoVoltage, useRegulatorLDO));
		    }
		    return status; //
	    },
	        py::arg("br"), py::arg("freqDev"), py::arg("rxBw"), py::arg("preambleLength"), py::arg("tcxoVoltage"), py::arg("useRegulatorLDO") = false)
	    .def("beginLRFHSS", [](SX126x& self, std::uint8_t bw, std::uint8_t cr, bool narrowGrid, float tcxoVoltage, bool useRegulatorLDO) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(
			        self.beginLRFHSS(bw, cr, narrowGrid, tcxoVoltage, useRegulatorLDO));
		    }
		    return status; //
	    })
	    .def("setLrFhssConfig", [](SX126x& self, std::uint8_t bw, std::uint8_t cr, std::uint8_t hdrCount, std::uint16_t hopSeqId) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(
			        self.setLrFhssConfig(bw, cr, hdrCount, hopSeqId));
		    }
		    return status; //
	    })
	    .def("reset", [](SX126x& self, bool verify) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.reset(verify));
		    }
		    return status; //
	    })
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

		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.transmit(ptr, len, addr));
		    }
		    return status; //
	    },
	        py::arg("data"), py::arg("addr") = 0)
	    .def("receive", [](SX126x& self, uint8_t* data, size_t len, RadioLibTime_t timeout) {
		    // TODO: Fix data read!

		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.receive(data, len, timeout));
		    }
		    return status; //
	    })
	    .def("transmitDirect", [](SX126x& self, uint32_t frf) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.transmitDirect(frf));
		    }
		    return status; //
	    })
	    .def("receiveDirect", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.receiveDirect());
		    }
		    return status; //
	    })
	    .def("scanChannel", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.scanChannel());
		    }
		    return status; //
	    })
	    .def("scanChannel", [](SX126x& self, CADScanConfig config) {
		    ChannelScanConfig_t cfg{};
		    cfg.cad = config;

		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.scanChannel(cfg));
		    }
		    return status; //
	    })
	    .def("scanChannel", [](SX126x& self, RSSIScanConfig config) {
		    ChannelScanConfig_t cfg{};
		    cfg.rssi = config;

		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.scanChannel(cfg));
		    }
		    return status; //
	    })
	    .def("sleep", [](SX126x& self, bool retainConfig) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.sleep(retainConfig));
		    }
		    return status; //
	    },
	        py::arg("retainConfig") = true)
	    .def("standby", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.standby());
		    }
		    return status; //
	    })
	    .def("standby", [](SX126x& self, std::uint8_t mode, bool wakeup) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.standby(mode, wakeup));
		    }
		    return status; //
	    })
	    .def("hopLRFHSS", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.hopLRFHSS());
		    }
		    return status; //
	    })
	    // .def("setDio1Action", &SX126x::setDio1Action) // func
	    .def("clearDio1Action", &SX126x::clearDio1Action)
	    // .def("setPacketReceivedAction", &SX126x::setPacketReceivedAction) // func
	    .def("clearPacketReceivedAction", &SX126x::clearPacketReceivedAction)
	    // .def("setPacketSentAction", &SX126x::setPacketSentAction)  // func
	    .def("clearPacketSentAction", &SX126x::clearPacketSentAction)
	    // .def("setChannelScanAction", &SX126x::setChannelScanAction)  // func
	    .def("clearChannelScanAction", &SX126x::clearChannelScanAction)
	    .def("finishTransmit", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.finishTransmit());
		    }
		    return status; //
	    })
	    .def("finishReceive", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.finishReceive());
		    }
		    return status; //
	    })
	    .def("startReceive", [](SX126x& self) { return self.finishTransmit(); })
	    .def("startReceiveDutyCycle", &SX126x::startReceiveDutyCycle)
	    .def("startReceiveDutyCycleAuto", &SX126x::startReceiveDutyCycleAuto)
	    .def("readData", &SX126x::readData)
	    .def("startChannelScan", py::overload_cast<>(&SX126x::startChannelScan))
	    .def("startChannelScan", py::overload_cast<ChannelScanConfig_t const&>(&SX126x::startChannelScan))
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
	    .def("setDataRate", [](SX126x& self, LoRaRate rate) {
		    DataRate_t dr{};
		    dr.lora = rate;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.setDataRate(dr, RADIOLIB_MODEM_LORA);
		    }
		    return status; //
	    })
	    .def("setDataRate", [](SX126x& self, FSKRate rate) {
		    DataRate_t dr{};
		    dr.fsk = rate;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.setDataRate(dr, RADIOLIB_MODEM_FSK);
		    }
		    return status; //
	    })
	    .def("setDataRate", [](SX126x& self, LrFhssRate rate) {
		    DataRate_t dr{};
		    dr.lrFhss = rate;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.setDataRate(dr, RADIOLIB_MODEM_LRFHSS);
		    }
		    return status; //
	    })
	    .def("checkDataRate", [](SX126x& self, LoRaRate rate) {
		    DataRate_t dr{};
		    dr.lora = rate;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.checkDataRate(dr, RADIOLIB_MODEM_LORA);
		    }
		    return status; //
	    })
	    .def("checkDataRate", [](SX126x& self, FSKRate rate) {
		    DataRate_t dr{};
		    dr.fsk = rate;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.checkDataRate(dr, RADIOLIB_MODEM_FSK);
		    }
		    return status; //
	    })
	    .def("checkDataRate", [](SX126x& self, LrFhssRate rate) {
		    DataRate_t dr{};
		    dr.lrFhss = rate;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.checkDataRate(dr, RADIOLIB_MODEM_LRFHSS);
		    }
		    return status; //
	    })
	    .def("setRxBandwidth", [](SX126x& self, float rxBw) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setRxBandwidth(rxBw));
		    }
		    return status; //
	    })
	    .def("setRxBoostedGainMode", [](SX126x& self, bool rxbgm, bool persis) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setRxBoostedGainMode(rxbgm, persis));
		    }
		    return status; //
	    })
	    .def("setDataShaping", [](SX126x& self, uint8_t sh) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setDataShaping(sh));
		    }
		    return status; //
	    })
	    .def("setSyncBits", [](SX126x& self, uint8_t* syncWord, uint8_t bitsLen) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setSyncBits(syncWord, bitsLen));
		    }
		    return status; //
	    })
	    .def("setCRC", [](SX126x& self, uint8_t len, uint16_t initial, uint16_t polynomial, bool inverted) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setCRC(len, initial, polynomial, inverted));
		    }
		    return status; //
	    })
	    .def("setWhitening", [](SX126x& self, bool enabled, uint16_t initial) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setWhitening(enabled, initial));
		    }
		    return status; //
	    })
	    .def("setTCXO", [](SX126x& self, float voltage, uint32_t delay) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setTCXO(voltage, delay));
		    }
		    return status; //
	    })
	    .def("setDio2AsRfSwitch", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setDio2AsRfSwitch());
		    }
		    return status; //
	    })
	    .def("getDataRate", &SX126x::getDataRate)
	    .def("getRSSI", py::overload_cast<>(&SX126x::getRSSI))
	    .def("getRSSI", py::overload_cast<bool>(&SX126x::getRSSI))
	    .def("getSNR", &SX126x::getSNR)
	    .def("getFrequencyError", &SX126x::getFrequencyError)
	    .def("getPacketLength", py::overload_cast<bool>(&SX126x::getPacketLength))
	    .def("getPacketLength", py::overload_cast<bool, std::uint8_t*>(&SX126x::getPacketLength))
	    .def("getLoRaRxHeaderInfo", [](SX126x& self, uint8_t* cr, bool* hasCRC) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.getLoRaRxHeaderInfo(cr, hasCRC));
		    }
		    return status; //
	    })
	    .def("fixedPacketLengthMode", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.fixedPacketLengthMode());
		    }
		    return status; //
	    })
	    .def("variablePacketLengthMode", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.variablePacketLengthMode());
		    }
		    return status; //
	    })
	    .def("calculateTimeOnAir", [](SX126x& self, LoRaRate rate, LoRaPacketConfig config, size_t len) {
		    DataRate_t dr{};
		    PacketConfig_t cfg{};

		    dr.lora = rate;
		    cfg.lora = config;

		    RadioLibTime_t time = 0;
		    {
			    py::gil_scoped_release const release;
			    time = self.calculateTimeOnAir(RADIOLIB_MODEM_LORA, dr, cfg, len);
		    }
		    return time; //
	    })
	    .def("calculateTimeOnAir", [](SX126x& self, FSKRate rate, FSKPacketConfig config, size_t len) {
		    DataRate_t dr{};
		    PacketConfig_t cfg{};

		    dr.fsk = rate;
		    cfg.fsk = config;

		    RadioLibTime_t time = 0;
		    {
			    py::gil_scoped_release const release;
			    time = self.calculateTimeOnAir(RADIOLIB_MODEM_FSK, dr, cfg, len);
		    }
		    return time; //
	    })
	    .def("calculateTimeOnAir", [](SX126x& self, LrFhssRate rate, LrFhssPacketConfig config, size_t len) {
		    DataRate_t dr{};
		    PacketConfig_t cfg{};

		    dr.lrFhss = rate;
		    cfg.lrFhss = config;

		    RadioLibTime_t time = 0;
		    {
			    py::gil_scoped_release const release;
			    time = self.calculateTimeOnAir(RADIOLIB_MODEM_LRFHSS, dr, cfg, len);
		    }
		    return time; //
	    })
	    .def("getTimeOnAir", &SX126x::getTimeOnAir)
	    .def("calculateRxTimeout", &SX126x::calculateRxTimeout)
	    .def("getIrqFlags", &SX126x::getIrqFlags)
	    .def("setIrqFlags", [](SX126x& self, uint32_t irq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setIrqFlags(irq));
		    }
		    return status; //
	    })
	    .def("clearIrqFlags", [](SX126x& self, uint32_t irq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.clearIrqFlags(irq));
		    }
		    return status; //
	    })
	    .def("implicitHeader", [](SX126x& self, size_t len) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.implicitHeader(len));
		    }
		    return status; //
	    })
	    .def("explicitHeader", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.explicitHeader());
		    }
		    return status; //
	    })
	    .def("setRegulatorLDO", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setRegulatorLDO());
		    }
		    return status; //
	    })
	    .def("setRegulatorDCDC", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setRegulatorDCDC());
		    }
		    return status; //
	    })
	    .def("setEncoding", [](SX126x& self, uint8_t encoding) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setEncoding(encoding));
		    }
		    return status; //
	    })
	    .def("setRfSwitchPins", &SX126x::setRfSwitchPins)
	    // .def("setRfSwitchTable", &SX126x::setRfSwitchTable) // struct
	    .def("forceLDRO", [](SX126x& self, bool enable) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.forceLDRO(enable));
		    }
		    return status; //
	    })
	    .def("autoLDRO", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.autoLDRO());
		    }
		    return status; //
	    })
	    .def("randomByte", &SX126x::randomByte)
	    .def("invertIQ", [](SX126x& self, bool enable) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.invertIQ(enable));
		    }
		    return status; //
	    })
	    .def("getModem", [](SX126x& self, ModemType_t* modem) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.getModem(modem));
		    }
		    return status; //
	    })
	    .def("stageMode", [](SX126x& self, StandbyConfig config) {
		    RadioModeConfig_t cfg{};
		    cfg.standby = config;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.stageMode(RADIOLIB_RADIO_MODE_STANDBY, &cfg);
		    }
		    return status; //
	    })
	    .def("stageMode", [](SX126x& self, ReceiveConfig config) {
		    RadioModeConfig_t cfg{};
		    cfg.receive = config;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.stageMode(RADIOLIB_RADIO_MODE_RX, &cfg);
		    }
		    return status; //
	    })
	    .def("stageMode", [](SX126x& self, TransmitConfig config) {
		    RadioModeConfig_t cfg{};
		    cfg.transmit = config;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.stageMode(RADIOLIB_RADIO_MODE_TX, &cfg);
		    }
		    return status; //
	    })
	    .def("stageMode", [](SX126x& self, ChannelScanConfig config) {
		    RadioModeConfig_t cfg{};
		    cfg.scan = config;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.stageMode(RADIOLIB_RADIO_MODE_SCAN, &cfg);
		    }
		    return status; //
	    })
	    .def("stageMode", [](SX126x& self, SleepConfig config) {
		    RadioModeConfig_t cfg{};
		    cfg.sleep = config;
		    uint16_t status = 0;
		    {
			    py::gil_scoped_release const release;
			    status = self.stageMode(RADIOLIB_RADIO_MODE_SLEEP, &cfg);
		    }
		    return status; //
	    })
	    .def("launchMode", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.launchMode());
		    }
		    return status; //
	    })
	    .def("setDirectAction", &SX126x::setDirectAction)
	    .def("readBit", &SX126x::readBit)
	    .def("uploadPatch", [](SX126x& self, std::uint32_t const* patch, size_t len, bool nonvolatile) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.uploadPatch(patch, len, nonvolatile));
		    }
		    return status; //
	    })
	    .def("spectralScanStart", [](SX126x& self, std::uint16_t numSamples, std::uint8_t window, std::uint8_t interval) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.spectralScanStart(numSamples, window, interval));
		    }
		    return status; //
	    })
	    .def("spectralScanAbort", &SX126x::spectralScanAbort)
	    .def("spectralScanGetStatus", [](SX126x& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.spectralScanGetStatus());
		    }
		    return status; //
	    })
	    .def("spectralScanGetResult", [](SX126x& self, uint16_t* results) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.spectralScanGetResult(results));
		    }
		    return status; //
	    })
	    .def("setPaConfig", [](SX126x& self, std::uint8_t paDutyCycle, std::uint8_t deviceSel, std::uint8_t hpMax, std::uint8_t paLut) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setPaConfig(paDutyCycle, deviceSel, hpMax, paLut));
		    }
		    return status; //
	    })
	    .def("calibrateImage", [](SX126x& self, float freq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.calibrateImage(freq));
		    }
		    return status; //
	    })
	    .def("calibrateImageRejection", [](SX126x& self, float freqMin, float freqMax) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.calibrateImageRejection(freqMin, freqMax));
		    }
		    return status; //
	    })
	    .def("setPaRampTime", [](SX126x& self, std::uint8_t rampTime) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setPaRampTime(rampTime));
		    }
		    return status; //
	    });
}
