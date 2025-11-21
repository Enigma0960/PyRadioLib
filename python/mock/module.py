from enum import IntEnum
from typing import Optional


class StandbyMode(IntEnum):
    Default = 0
    Warm = 1
    Cold = 2


class TcxoVoltage(IntEnum):
    V1p6 = 0
    V1p7 = 1
    V1p8 = 2
    V2p2 = 3
    V2p4 = 4
    V2p7 = 5
    V3p0 = 6
    V3p3 = 7

class PacketType(IntEnum):
    Fsk = 0
    LoRa = 1
    Fhss = 2



class MockModule:
    def transfer(self, data: bytes) -> Optional[bytes]:
        ...
