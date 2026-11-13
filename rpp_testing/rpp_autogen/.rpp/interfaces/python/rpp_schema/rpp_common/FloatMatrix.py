
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class FloatMatrix:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    rows: int = 0
    columns: int = 0
    values: List[float] = Field(default_factory=list)
    