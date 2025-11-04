#include "bind_enums.h"

void bind_enums(py::module& module)  {
	py::enum_<ModemType>(module, "ModemType", py::arithmetic())
	.value("RADIOLIB_MODEM_FSK", RADIOLIB_MODEM_FSK)
	.value("RADIOLIB_MODEM_LORA", RADIOLIB_MODEM_LORA)
	.value("RADIOLIB_MODEM_LRFHSS", RADIOLIB_MODEM_LRFHSS)
	.value("RADIOLIB_MODEM_NONE", RADIOLIB_MODEM_NONE);
}