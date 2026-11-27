
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple
from rpp_schema.rpp_testing.AllocationFixedSample import AllocationFixedSample

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class AllocationEnvelope:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    name: str = ""
    payload: bytes = b''
    values: List[float] = Field(default_factory=list)
    child: AllocationFixedSample = Field(default_factory=AllocationFixedSample)
    history: List[AllocationFixedSample] = Field(default_factory=list)
    