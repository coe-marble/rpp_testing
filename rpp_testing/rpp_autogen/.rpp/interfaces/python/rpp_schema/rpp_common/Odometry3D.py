
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple
from rpp_schema.rpp_common.Pose3D import Pose3D
from rpp_schema.rpp_common.Twist3D import Twist3D

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class Odometry3D:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    pose: Pose3D = Field(default_factory=Pose3D)
    twist: Twist3D = Field(default_factory=Twist3D)
    