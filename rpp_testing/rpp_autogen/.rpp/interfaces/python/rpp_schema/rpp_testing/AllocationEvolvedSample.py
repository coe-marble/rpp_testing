
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class AllocationEvolvedSample:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    a: float = 0.0
    b: float = 0.0
    c: float = 0.0
    d: float = 0.0
    e: float = 0.0
    f: float = 0.0
    name: str = ""
    values: List[float] = Field(default_factory=list)
    