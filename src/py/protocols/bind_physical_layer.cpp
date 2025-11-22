#include "bind_physical_layer.h"

#include <py/bind_types.h>

void bind_physical_layer(py::module& module) {
	py::class_<PhysicalLayer, PyPhysicalLayer, std::shared_ptr<PhysicalLayer>>(module, "PhysicalLayer")
	    .def(py::init<>())
	.def("transmit", [](PhysicalLayer& self, py::buffer const& data, std::uint8_t addr) {
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
	    .def("receive", [](PhysicalLayer& self, uint8_t* data, size_t len, RadioLibTime_t timeout) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.receive(data, len, timeout));
		    }
		    return status; //
	    })
	    .def("startTransmit", [](PhysicalLayer& self, uint8_t const* data, size_t len, uint8_t addr) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.startTransmit(data, len, addr));
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
	    .def("readData", [](PhysicalLayer& self, uint8_t* data, size_t len) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.readData(data, len));
		    }
		    return status; //
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
	    .def("setSyncWord", [](PhysicalLayer& self, uint8_t* sync, size_t len) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setSyncWord(sync, len));
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
	    // .def("setDataRate", &PhysicalLayer::setDataRate)
	    // .def("checkDataRate", &PhysicalLayer::checkDataRate)
	    .def("getPacketLength", &PhysicalLayer::getPacketLength)
	    .def("getRSSI", &PhysicalLayer::getRSSI)
	    .def("getSNR", &PhysicalLayer::getSNR)
	    // .def("calculateTimeOnAir", &PhysicalLayer::calculateTimeOnAir)
	    .def("getTimeOnAir", &PhysicalLayer::getTimeOnAir)
	    .def("calculateRxTimeout", &PhysicalLayer::calculateRxTimeout)
	    .def("getIrqMapped", &PhysicalLayer::getIrqMapped)
	    // .def("checkIrq", &PhysicalLayer::checkIrq)
	    .def("setIrq", [](PhysicalLayer& self, RadioLibIrqFlags_t irq) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.setIrq(irq));
		    }
		    return status; //
	    })
	    .def("clearIrq", [](PhysicalLayer& self, RadioLibIrqFlags_t irq) {
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
	    // .def("stageMode", &PhysicalLayer::stageMode)
	    .def("launchMode", [](PhysicalLayer& self) {
		    ModuleStatus status{};
		    {
			    py::gil_scoped_release const release;
			    status = static_cast<ModuleStatus>(self.launchMode());
		    }
		    return status; //
	    });
}
