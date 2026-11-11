
from typing import List, Dict, Any, Tuple
from rpp_py.plugin import Plugin
from rpp_py.context import ComponentContext
from rpp_py.lifecycle import CallbackResult, DeactivationResult
import inspect
from rpp_schema.rpp_common.Odometry2D import Odometry2D as _Odometry2D
from rpp_schema.rpp_common.VectorPlanar import VectorPlanar as _VectorPlanar

class MotionController2D(Plugin):

    Odometry2D = _Odometry2D
    VectorPlanar = _VectorPlanar

    
    def step(self, state: Odometry2D, dt: float, **kwargs)-> VectorPlanar:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def step_async(self, state: Odometry2D, dt: float, **kwargs)-> VectorPlanar:
        result = self.step(state=state, dt=dt, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def validate(self, state: Odometry2D, **kwargs)-> bool:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def validate_async(self, state: Odometry2D, **kwargs)-> bool:
        result = self.validate(state=state, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result



    def on_configure(self, context: ComponentContext) -> CallbackResult:
        return CallbackResult()
