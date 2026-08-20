
from __future__ import annotations

from rpp_orchestrator.orchestration_script import OrchestrationScript

from rpp_plugin_types.rpp_testing import MotionController2D
from rpp_plugin_types.rpp_testing import DisturbanceGenerator2D



class Example(OrchestrationScript):
    COMPONENTS = {
        "ctl_main": "rpp_testing::MotionController2D",
        "ctl_disturbance": "rpp_testing::DisturbanceGenerator2D",
    }
    def run(self) -> None:
        raise NotImplementedError("Define the workspace logic here.")


    