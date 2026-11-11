
from typing import List, Dict, Any, Tuple
from rpp_py.plugin import Plugin
from rpp_py.context import ComponentContext
from rpp_py.lifecycle import CallbackResult, DeactivationResult
import inspect
from rpp_schema.rpp_common.Pose2D import Pose2D as _Pose2D

class DisturbanceGenerator2D(Plugin):

    Pose2D = _Pose2D

    
    def step(self, state: Pose2D, dt: float, **kwargs)-> Pose2D:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def step_async(self, state: Pose2D, dt: float, **kwargs)-> Pose2D:
        result = self.step(state=state, dt=dt, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def validate(self, state: Pose2D, **kwargs)-> bool:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def validate_async(self, state: Pose2D, **kwargs)-> bool:
        result = self.validate(state=state, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def setData(self, data: bytes, **kwargs)-> bool:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def setData_async(self, data: bytes, **kwargs)-> bool:
        result = self.setData(data=data, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def getData(self, **kwargs)-> bytes:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def getData_async(self, **kwargs)-> bytes:
        result = self.getData(**kwargs)
        if inspect.isawaitable(result):
            return await result
        return result



    def on_configure(self, context: ComponentContext) -> CallbackResult:
        return CallbackResult()
