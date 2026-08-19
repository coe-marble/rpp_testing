from __future__ import annotations


from rpp_plugin_types.rpp_testing import MotionController2D
from rpp_plugin_types.rpp_testing import DisturbanceGenerator2D
from rpp_py.plugin import ParameterDescription

class SuperClass:
    def __init__(self, a = 1, b = 2):
        self.a = a
        self.b = b

class ComponentPluginComplexPy(MotionController2D):
    COMPONENTS = {
        "ctl_main": "rpp_testing::MotionController2D",
        "ctl_disturbance": "rpp_testing::DisturbanceGenerator2D",
    }

    PARAMETERS = [
        ParameterDescription("param1", 1.1),
        ParameterDescription("param2", 2),
        ParameterDescription("param3", "default_string"),
        ParameterDescription("param4", True),
        ParameterDescription("param5", [1, 2, 3]),
        ParameterDescription("param6", {"key1": "value1", "key2": 2}),
        ParameterDescription("param7", SuperClass(a=10))
    ]

    def __init__(self):
        super().__init__()

    def validate(self, state : MotionController2D.Odometry2D) -> bool:

        x = state.pose.position.x
        return x > 5.0

    def step(self, state: MotionController2D.Odometry2D, dt: float) -> None:
        # Implement the control logic here
        pass
