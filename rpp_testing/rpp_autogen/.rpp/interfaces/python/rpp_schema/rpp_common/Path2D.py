
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple
from rpp_schema.rpp_common.Point2D import Point2D

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class Path2D:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    points: List[Point2D] = Field(default_factory=list)
    