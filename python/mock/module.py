from enum import IntEnum
from typing import Optional


class StandbyMode(IntEnum):
    Default = 0
    Warm = 1
    Cold = 2


class MockModule:
    def transfer(self, data: bytes) -> Optional[bytes]:
        ...
