
from typing import List, Dict, Any, Tuple
from pydantic import (
    BaseModel, ConfigDict, RootModel,
    ValidationError, Field
)
from pydantic.dataclasses import dataclass
from typing import List, Dict, Any, Tuple
from rpp_schema.rpp_common.Pose2D import Pose2D
from rpp_schema.rpp_common.Twist2D import Twist2D

@dataclass(config=ConfigDict(extra="forbid", validate_assignment=True))
class Odometry2D:

    def as_dict(self) -> Dict[str, Any]:

        return RootModel(self).model_dump()

    pose: Pose2D = Field(default_factory=Pose2D)
    twist: Twist2D = Field(default_factory=Twist2D)
    