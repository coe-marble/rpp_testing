from __future__ import annotations


from rpp_plugin_types.rpp_testing import MotionController2D
from rpp_plugin_types.rpp_testing import DisturbanceGenerator2D
from rpp_py.plugin import ParameterDescription

class SuperClass:
    def __init__(self, a = 1, b = 2):
        self.a = a
        self.b = b

class ComponentPluginSimplePy(MotionController2D):
    PARAMETERS = [
        ParameterDescription("param1", 2.0),
        ParameterDescription("param2", 3),
        ParameterDescription("param3", "default_string1"),
        ParameterDescription("param4", True),
        ParameterDescription("param5", [2, 3, 4]),
        ParameterDescription("param6", {"key1": "value2", "key2": 3}),
        ParameterDescription("param7", SuperClass(a=11))
    ]

    def __init__(self):
        super().__init__()

    def validate(self, state : MotionController2D.Odometry2D) -> bool:

        x = state.pose.position.x
        return x > 5.0

    def step(self, state: MotionController2D.Odometry2D, dt: float) -> None:
        # Implement the control logic here
        pass
