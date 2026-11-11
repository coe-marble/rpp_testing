
from typing import List, Dict, Any, Tuple
from rpp_py.plugin import Plugin
from rpp_py.context import ComponentContext
from rpp_py.lifecycle import CallbackResult, DeactivationResult
import inspect
from rpp_schema.rpp_common.Pose3D import Pose3D as _Pose3D

class DynamicalSystem3D(Plugin):

    Pose3D = _Pose3D

    
    def step(self, state: Pose3D, dt: float, **kwargs)-> Pose3D:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def step_async(self, state: Pose3D, dt: float, **kwargs)-> Pose3D:
        result = self.step(state=state, dt=dt, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def validate(self, state: Pose3D, **kwargs)-> bool:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def validate_async(self, state: Pose3D, **kwargs)-> bool:
        result = self.validate(state=state, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result



    def on_configure(self, context: ComponentContext) -> CallbackResult:
        return CallbackResult()
