
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class TestStruct1:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    x: float = 0.0
    y: float = 0.0
    theta: float = 0.0
    