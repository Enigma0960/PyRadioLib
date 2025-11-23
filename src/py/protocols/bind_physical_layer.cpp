#include "bind_physical_layer.h"

#include <py/bind_types.h>

namespace {

constexpr auto MAX_PACKET_LENGTH = 255;

}

void bind_physical_layer(py::module& module) {
	py::class_<PhysicalLayer, PyPhysicalLayer, std::shared_ptr<PhysicalLayer>>(module, "PhysicalLayer")
	    .def(py::init<>())
	    .def("transmit", [](PhysicalLayer& self, py::buffer const& data, std::uint8_t addr) {
		    py::buffer_info info = data.request();
		    auto* ptr = static_cast<std::uint8_t const*>(info.ptr);
		    auto len = static_cast<std::size_t>(info.size);

		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.transmit(ptr, len, addr));
		    }
		    return status; //
	    })
	    .def("sleep", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.sleep());
		    }
		    return status; //
	    })
	    .def("standby", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.standby());
		    }
		    return status; //
	    })
	    .def("startReceive", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.startReceive());
		    }
		    return status; //
	    })
	    .def("receive", [](PhysicalLayer& self, size_t len, uint32_t timeout) {
		    if (len > MAX_PACKET_LENGTH) {
			    len = MAX_PACKET_LENGTH;
		    }

		    std::vector<std::uint8_t> buffer(len);

		    if (len == 0) {
			    std::size_t packet_len = 0;
			    {
				    py::gil_scoped_release const release;
				    packet_len = self.getPacketLength(true);
			    }

			    if (packet_len == 0) {
				    return py::make_tuple(ModuleStatus::Normal, py::bytes());
			    }
		    }

		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(
			        self.receive(buffer.data(), buffer.size(), timeout));
		    }

		    py::bytes const data(reinterpret_cast<char const*>(buffer.data()), static_cast<py::ssize_t>(buffer.size()));

		    return py::make_tuple(status, data); //
	    })
	    .def("startTransmit", [](PhysicalLayer& self, py::buffer const& data, uint8_t addr) {
		    py::buffer_info info = data.request();
		    auto* ptr = static_cast<std::uint8_t const*>(info.ptr);
		    auto len = static_cast<std::size_t>(info.size);

		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.startTransmit(ptr, len, addr));
		    }
		    return status; //
	    })
	    .def("finishTransmit", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.finishTransmit());
		    }
		    return status; //
	    })
	    .def("finishReceive", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.finishReceive());
		    }
		    return status; //
	    })
	    .def("readData", [](PhysicalLayer& self, size_t len) {
		    if (len > MAX_PACKET_LENGTH) {
			    len = MAX_PACKET_LENGTH;
		    }

		    std::vector<std::uint8_t> buffer(len);
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(
			        self.readData(buffer.data(), buffer.size()));
		    }

		    py::bytes const data(reinterpret_cast<char const*>(buffer.data()), static_cast<py::ssize_t>(buffer.size()));

		    return py::make_tuple(status, data); //
	    })
	    .def("transmitDirect", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.transmitDirect());
		    }
		    return status; //
	    })
	    .def("receiveDirect", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.receiveDirect());
		    }
		    return status; //
	    })
	    .def("setFrequency", [](PhysicalLayer& self, float freq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setFrequency(freq));
		    }
		    return status; //
	    })
	    .def("setBitRate", [](PhysicalLayer& self, float br) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setBitRate(br));
		    }
		    return status; //
	    })
	    .def("setFrequencyDeviation", [](PhysicalLayer& self, float freqDev) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setFrequencyDeviation(freqDev));
		    }
		    return status; //
	    })
	    .def("setDataShaping", [](PhysicalLayer& self, uint8_t sh) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setDataShaping(sh));
		    }
		    return status; //
	    })
	    .def("setEncoding", [](PhysicalLayer& self, uint8_t encoding) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setEncoding(encoding));
		    }
		    return status; //
	    })
	    .def("invertIQ", [](PhysicalLayer& self, bool enable) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.invertIQ(enable));
		    }
		    return status; //
	    })
	    .def("setOutputPower", [](PhysicalLayer& self, int8_t power) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setOutputPower(power));
		    }
		    return status; //
	    })
	    .def("checkOutputPower", [](PhysicalLayer& self, int8_t power) {
		    std::int8_t clipped = 0;
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release release;
			    status = static_cast<ModuleStatus>(self.checkOutputPower(power, &clipped));
		    }
		    return py::make_tuple(status, clipped); //
	    })
	    .def("setSyncWord", [](PhysicalLayer& self, py::buffer const& words) {
		    py::buffer_info const info = words.request();
		    auto* ptr = static_cast<std::uint8_t*>(info.ptr);
		    auto len = static_cast<std::size_t>(info.size);
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setSyncWord(ptr, len));
		    }
		    return status; //
	    })
	    .def("setPreambleLength", [](PhysicalLayer& self, size_t len) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setPreambleLength(len));
		    }
		    return status; //
	    })
	    .def("setDataRate", [](PhysicalLayer& self, LoRaRate rate, ModemType modem) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.lora = rate;
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setDataRate(dr, modem));
		    }
		    return status; //
	    })
	    .def("setDataRate", [](PhysicalLayer& self, FSKRate rate, ModemType modem) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.fsk = rate;
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setDataRate(dr, modem));
		    }
		    return status; //
	    })
	    .def("setDataRate", [](PhysicalLayer& self, LrFhssRate rate, ModemType modem) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.lrFhss = rate;
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setDataRate(dr, modem));
		    }
		    return status; //
	    })
	    .def("checkDataRate", [](PhysicalLayer& self, LoRaRate rate, ModemType modem) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.lora = rate;
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.checkDataRate(dr, modem));
		    }
		    return status; //
	    })
	    .def("checkDataRate", [](PhysicalLayer& self, FSKRate rate, ModemType modem) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.fsk = rate;
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.checkDataRate(dr, modem));
		    }
		    return status; //
	    })
	    .def("checkDataRate", [](PhysicalLayer& self, LrFhssRate rate, ModemType modem) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.lrFhss = rate;
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.checkDataRate(dr, modem));
		    }
		    return status; //
	    })
	    .def("getPacketLength", &PhysicalLayer::getPacketLength)
	    .def("getRSSI", &PhysicalLayer::getRSSI)
	    .def("getSNR", &PhysicalLayer::getSNR)
	    .def("calculateTimeOnAir", [](PhysicalLayer& self, ModemType modem, LoRaRate rate, LoRaPacketConfig config, size_t len) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.lora = rate;
		    PacketConfig_t pc{};
		    pc.lora = config;

		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.calculateTimeOnAir(modem, dr, pc, len));
		    }
		    return status; //
	    })
	    .def("calculateTimeOnAir", [](PhysicalLayer& self, ModemType modem, FSKRate rate, FSKPacketConfig config, size_t len) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.fsk = rate;
		    PacketConfig_t pc{};
		    pc.fsk = config;

		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.calculateTimeOnAir(modem, dr, pc, len));
		    }
		    return status; //
	    })
	    .def("calculateTimeOnAir", [](PhysicalLayer& self, ModemType modem, LrFhssRate rate, LrFhssPacketConfig config, size_t len) {
		    ModuleStatus status{};
		    DataRate_t dr{};
		    dr.lrFhss = rate;
		    PacketConfig_t pc{};
		    pc.lrFhss = config;

		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.calculateTimeOnAir(modem, dr, pc, len));
		    }
		    return status; //
	    })
	    .def("getTimeOnAir", &PhysicalLayer::getTimeOnAir)
	    .def("calculateRxTimeout", &PhysicalLayer::calculateRxTimeout)
	    .def("getIrqMapped", &PhysicalLayer::getIrqMapped)
	    .def("checkIrq", [](PhysicalLayer& self, IrqType irq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.checkIrq(static_cast<RadioLibIrqType_t>(irq)));
		    }
		    return status; //
	    })
	    .def("setIrq", [](PhysicalLayer& self, uint32_t irq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setIrq(irq));
		    }
		    return status; //
	    })
	    .def("clearIrq", [](PhysicalLayer& self, uint32_t irq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.clearIrq(irq));
		    }
		    return status; //
	    })
	    .def("getIrqFlags", &PhysicalLayer::getIrqFlags)
	    .def("setIrqFlags", [](PhysicalLayer& self, uint32_t irq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setIrqFlags(irq));
		    }
		    return status; //
	    })
	    .def("clearIrqFlags", [](PhysicalLayer& self, uint32_t irq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.clearIrqFlags(irq));
		    }
		    return status; //
	    })
	    .def("startChannelScan", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.startChannelScan());
		    }
		    return status; //
	    })
	    .def("getChannelScanResult", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.getChannelScanResult());
		    }
		    return status; //
	    })
	    .def("scanChannel", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.scanChannel());
		    }
		    return status; //
	    })
	    .def("random", py::overload_cast<std::int32_t>(&PhysicalLayer::random))
	    .def("random", py::overload_cast<std::int32_t, std::int32_t>(&PhysicalLayer::random))
	    .def("randomByte", &PhysicalLayer::randomByte)
	    .def("startDirect", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.startDirect());
		    }
		    return status; //
	    })
	    .def("setDirectSyncWord", [](PhysicalLayer& self, uint32_t syncWord, uint8_t len) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setDirectSyncWord(syncWord, len));
		    }
		    return status; //
	    })
	    .def("setDirectAction", &PhysicalLayer::setDirectAction)
	    .def("readBit", &PhysicalLayer::readBit)
	    .def("available", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.available());
		    }
		    return status; //
	    })
	    .def("dropSync", &PhysicalLayer::dropSync)
	    .def("read", &PhysicalLayer::read)
	    .def("setDIOMapping", [](PhysicalLayer& self, uint32_t pin, uint32_t value) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setDIOMapping(pin, value));
		    }
		    return status; //
	    })
	    .def("setPacketReceivedAction", &PhysicalLayer::setPacketReceivedAction)
	    .def("clearPacketReceivedAction", &PhysicalLayer::clearPacketReceivedAction)
	    .def("setPacketSentAction", &PhysicalLayer::setPacketSentAction)
	    .def("clearPacketSentAction", &PhysicalLayer::clearPacketSentAction)
	    .def("setChannelScanAction", &PhysicalLayer::setChannelScanAction)
	    .def("clearChannelScanAction", &PhysicalLayer::clearChannelScanAction)
	    .def("setModem", [](PhysicalLayer& self, ModemType modem) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setModem(modem));
		    }
		    return status; //
	    })
	    .def("getModem", [](PhysicalLayer& self) {
		    ModemType modem{};
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.getModem(&modem));
		    }
		    return py::make_tuple(status, modem); //
	    })
	    .def("stageMode", [](PhysicalLayer& self, RadioModeType mode, StandbyConfig config) {
		    ModuleStatus status{};
		    RadioModeConfig_t cfg{};
		    cfg.standby = config;

		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.stageMode(mode, &cfg));
		    }
		    return status; //
	    })
	    .def("stageMode", [](PhysicalLayer& self, RadioModeType mode, ReceiveConfig config) {
		    ModuleStatus status{};
		    RadioModeConfig_t cfg{};
		    cfg.receive = config;

		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.stageMode(mode, &cfg));
		    }
		    return status; //
	    })
	    .def("stageMode", [](PhysicalLayer& self, RadioModeType mode, TransmitConfig config) {
		    ModuleStatus status{};
		    RadioModeConfig_t cfg{};
		    cfg.transmit = config;

		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.stageMode(mode, &cfg));
		    }
		    return status; //
	    })
	    .def("stageMode", [](PhysicalLayer& self, RadioModeType mode, ChannelScanConfig config) {
		    ModuleStatus status{};
		    RadioModeConfig_t cfg{};
		    cfg.scan = config;

		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.stageMode(mode, &cfg));
		    }
		    return status; //
	    })
	    .def("stageMode", [](PhysicalLayer& self, RadioModeType mode, SleepConfig config) {
		    ModuleStatus status{};
		    RadioModeConfig_t cfg{};
		    cfg.sleep = config;

		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.stageMode(mode, &cfg));
		    }
		    return status; //
	    })
	    .def("launchMode", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.launchMode());
		    }
		    return status; //
	    });
}
