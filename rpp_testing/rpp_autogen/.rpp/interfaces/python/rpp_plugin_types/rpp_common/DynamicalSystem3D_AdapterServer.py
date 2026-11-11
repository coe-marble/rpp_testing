

from typing import List, Dict, Any, Tuple
from rpp_schema.rpp_common.Pose3D import Pose3D as _Pose3D
import capnp
import rpp_py.capnp_schema as capnp_schema
import asyncio
import inspect
from rpp_py.capnp_runtime import CapnpRuntime
from rpp_py.context import ComponentContext
from rpp_py.adapter_info import AdapterServerParams, AdapterServerInfo
from rpp_py.logger import RppLogger
from rpp_py.lifecycle import CallbackResult
from rpp_plugin_types.rpp_common.DynamicalSystem3D import DynamicalSystem3D

class DynamicalSystem3D_AdapterServer(capnp_schema.get_server_class("rpp_common::DynamicalSystem3D", "dynamical_system.capnp")):
    Pose3D = _Pose3D

    def __init__(self, logger: RppLogger | None = None):
        super().__init__()
        self._adapter_server_params: AdapterServerParams = None
        self._logger = logger
        self._backend : DynamicalSystem3D = None
        self._asyncio_server = None
        self._rpc_server = None
        self.is_running = False
        self._runtime = None
        self._adapter_server_info = AdapterServerInfo()
        self._adapter_server_info.plugin_type = "rpp_common::DynamicalSystem3D"
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

    
    async def step(self, state: Pose3D, dt: float, **kwargs)-> Pose3D:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='step'.")
        result = self._backend.step(state=state, dt=dt)
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='step'.")
        return result

    async def validate(self, state: Pose3D, **kwargs)-> bool:
        if self._backend is None:
            raise RuntimeError("Backend is not configured. Please call configure_adapter_server__() first.")
        self._logger.debug(
            f"Received request: component={self._adapter_server_info.name!r}, "
            f"method='validate'.")
        result = self._backend.validate(state=state)
        if inspect.isawaitable(result):
            result = await result
        self._logger.debug(
            f"Backend completed: component={self._adapter_server_info.name!r}, "
            f"method='validate'.")
        return result

