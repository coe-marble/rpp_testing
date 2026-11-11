
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple
from rpp_schema.rpp_testing.TestStruct1 import TestStruct1

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class TestStruct2:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    linear: float = 0.0
    angular: float = 0.0
    struct1: TestStruct1 = Field(default_factory=TestStruct1)
    