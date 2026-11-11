
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple
from rpp_schema.rpp_common.Point3D import Point3D
from rpp_schema.rpp_common.Quaternion import Quaternion

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class Pose3D:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    position: Point3D = Field(default_factory=Point3D)
    orientation: Quaternion = Field(default_factory=Quaternion)
    