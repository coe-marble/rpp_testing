

from typing import List, Dict, Any, Tuple
from rpp_schema.rpp_testing.TestStruct1 import TestStruct1 as _TestStruct1
from rpp_schema.rpp_testing.TestStruct2 import TestStruct2 as _TestStruct2
import capnp
import rpp_py.capnp_schema as capnp_schema
import asyncio
import inspect
from rpp_py.capnp_runtime import CapnpRuntime
from rpp_py.context import ComponentContext
from rpp_py.adapter_info import AdapterServerParams, AdapterServerInfo
from rpp_py.logger import RppLogger
from rpp_py.lifecycle import CallbackResult
from rpp_plugin_types.rpp_testing.TestInterfaceAll import TestInterfaceAll

class TestInterfaceAll_AdapterServer(capnp_schema.get_server_class("rpp_testing::TestInterfaceAll", "test_plugin_types.capnp")):
    TestStruct1 = _TestStruct1
    TestStruct2 = _TestStruct2

    def __init__(self, logger: RppLogger | None = None):
        super().__init__()
        self._adapter_server_params: AdapterServerParams = None
        self._logger = logger
        self._backend : TestInterfaceAll = None
        self._asyncio_server = None
        self._rpc_server = None
        self.is_running = False
        self._runtime = None
        self._adapter_server_info = AdapterServerInfo()
        self._adapter_server_info.plugin_type = "rpp_testing::TestInterfaceAll"
        self._adapter_server_info.created_at = ""

    def configure_adapter_server__(self, adapter_server_params: AdapterServerParams):
        self._adapter_server_params = adapter_server_params
        self._adapter_server_info.plugin_name = adapter_server_params.plugin_name
        self._adapter_server_info.name = adapter_server_params.name \
            if adapter_server_params.name else \
                f"{adapter_server_params.plugin_name}_adapter_server"
        self._adapter_server_info.connection_name = adapter_server_params.connection_name \
            if adapter_server_params.connection_name else \
                f"{adapter_server_params.plugin_name}_connection"
        self._backend = adapter_server_params.backend
        if self._logger is None:
            self._logger = RppLogger(self._adapter_server_info.name)

    def create_capability_adapter_server__(self):
        return self

    async def handle_connection_adapter_server__(self, stream):
        self._rpc_server = capnp.TwoPartyServer(stream, bootstrap=self)
        await self._rpc_server.on_disconnect()

    async def start_adapter_server__(self, runtime: CapnpRuntime, host: str, port: int):
        self._runtime = runtime
        if self._adapter_server_params is None:
            raise RuntimeError("Adapter server params are not configured. " \
                + "Please call configure_adapter_server__() first.")

        self._asyncio_server = await capnp.AsyncIoStream.create_server( \
                self.handle_connection_adapter_server__, host, port)
        self.is_running = True


    async def stop_adapter_server__(self):
        if self._asyncio_server:
            self._asyncio_server.close()
            await self._asyncio_server.wait_closed()
        self._asyncio_server = None
        self._rpc_server = None
        self._runtime = None
        self.is_running = False

    def get_info_adapter_server__(self) -> AdapterServerInfo:
        return self._adapter_server_info

    def decode_lifecycle_state__(self, schema_id, payload):
        if schema_id:
            return CallbackResult.failure("This plugin does not accept lifecycle state"), None
        return CallbackResult(), None

    def encode_lifecycle_state__(self, state, wire):
        if state is not None:
            return CallbackResult.failure("This plugin does not provide lifecycle state")
        wire.schemaId = 0
        return CallbackResult()

    
    async def funcEmpty(self, **kwargs)-> None:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='funcEmpty'.")
        result = self._backend.funcEmpty()
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='funcEmpty'.")
        return result

    async def funcWithSimpleParams(self, paramFloat: float, paramBool: bool, **kwargs)-> float:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='funcWithSimpleParams'.")
        result = self._backend.funcWithSimpleParams(paramFloat=paramFloat, paramBool=paramBool)
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='funcWithSimpleParams'.")
        return result

    async def funcWithStructParam(self, paramStruct1: TestStruct1, paramStruct2: TestStruct2, **kwargs)-> TestStruct1:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='funcWithStructParam'.")
        result = self._backend.funcWithStructParam(paramStruct1=paramStruct1, paramStruct2=paramStruct2)
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='funcWithStructParam'.")
        return result

    async def funcWithListParam(self, paramListFloat: List[float], paramListStruct: List[TestStruct1], **kwargs)-> List[float]:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='funcWithListParam'.")
        result = self._backend.funcWithListParam(paramListFloat=paramListFloat, paramListStruct=paramListStruct)
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='funcWithListParam'.")
        return result

    async def funcWithListOfStructParam(self, paramListStruct: List[TestStruct1], **kwargs)-> List[TestStruct2]:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='funcWithListOfStructParam'.")
        result = self._backend.funcWithListOfStructParam(paramListStruct=paramListStruct)
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='funcWithListOfStructParam'.")
        return result

    async def funcWithMultipleSimpleReturns(self, **kwargs)-> Tuple[float, bool]:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='funcWithMultipleSimpleReturns'.")
        result = self._backend.funcWithMultipleSimpleReturns()
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='funcWithMultipleSimpleReturns'.")
        return result

    async def funcWithMultipleStructReturns(self, **kwargs)-> Tuple[TestStruct1, TestStruct2]:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='funcWithMultipleStructReturns'.")
        result = self._backend.funcWithMultipleStructReturns()
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='funcWithMultipleStructReturns'.")
        return result

    async def funcWithMultipleListReturns(self, **kwargs)-> Tuple[List[float], List[TestStruct1]]:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='funcWithMultipleListReturns'.")
        result = self._backend.funcWithMultipleListReturns()
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='funcWithMultipleListReturns'.")
        return result

