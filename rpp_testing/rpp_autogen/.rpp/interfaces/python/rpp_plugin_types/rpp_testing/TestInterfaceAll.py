
from typing import List, Dict, Any, Tuple
from rpp_py.plugin import Plugin
from rpp_py.context import ComponentContext
from rpp_py.lifecycle import CallbackResult, DeactivationResult
import inspect
from rpp_schema.rpp_testing.TestStruct1 import TestStruct1 as _TestStruct1
from rpp_schema.rpp_testing.TestStruct2 import TestStruct2 as _TestStruct2

class TestInterfaceAll(Plugin):

    TestStruct1 = _TestStruct1
    TestStruct2 = _TestStruct2

    
    def funcEmpty(self, **kwargs)-> None:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def funcEmpty_async(self, **kwargs)-> None:
        result = self.funcEmpty(**kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def funcWithSimpleParams(self, paramFloat: float, paramBool: bool, **kwargs)-> float:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def funcWithSimpleParams_async(self, paramFloat: float, paramBool: bool, **kwargs)-> float:
        result = self.funcWithSimpleParams(paramFloat=paramFloat, paramBool=paramBool, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def funcWithStructParam(self, paramStruct1: TestStruct1, paramStruct2: TestStruct2, **kwargs)-> TestStruct1:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def funcWithStructParam_async(self, paramStruct1: TestStruct1, paramStruct2: TestStruct2, **kwargs)-> TestStruct1:
        result = self.funcWithStructParam(paramStruct1=paramStruct1, paramStruct2=paramStruct2, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def funcWithListParam(self, paramListFloat: List[float], paramListStruct: List[TestStruct1], **kwargs)-> List[float]:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def funcWithListParam_async(self, paramListFloat: List[float], paramListStruct: List[TestStruct1], **kwargs)-> List[float]:
        result = self.funcWithListParam(paramListFloat=paramListFloat, paramListStruct=paramListStruct, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def funcWithListOfStructParam(self, paramListStruct: List[TestStruct1], **kwargs)-> List[TestStruct2]:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def funcWithListOfStructParam_async(self, paramListStruct: List[TestStruct1], **kwargs)-> List[TestStruct2]:
        result = self.funcWithListOfStructParam(paramListStruct=paramListStruct, **kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def funcWithMultipleSimpleReturns(self, **kwargs)-> Tuple[float, bool]:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def funcWithMultipleSimpleReturns_async(self, **kwargs)-> Tuple[float, bool]:
        result = self.funcWithMultipleSimpleReturns(**kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def funcWithMultipleStructReturns(self, **kwargs)-> Tuple[TestStruct1, TestStruct2]:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def funcWithMultipleStructReturns_async(self, **kwargs)-> Tuple[TestStruct1, TestStruct2]:
        result = self.funcWithMultipleStructReturns(**kwargs)
        if inspect.isawaitable(result):
            return await result
        return result

    def funcWithMultipleListReturns(self, **kwargs)-> Tuple[List[float], List[TestStruct1]]:
        raise NotImplementedError("This method should be implemented in the plugin class.")

    async def funcWithMultipleListReturns_async(self, **kwargs)-> Tuple[List[float], List[TestStruct1]]:
        result = self.funcWithMultipleListReturns(**kwargs)
        if inspect.isawaitable(result):
            return await result
        return result



    def on_configure(self, context: ComponentContext) -> CallbackResult:
        return CallbackResult()
