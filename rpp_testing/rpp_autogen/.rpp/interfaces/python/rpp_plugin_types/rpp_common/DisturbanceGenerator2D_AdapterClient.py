
from typing import List, Dict, Any, Tuple
import capnp
import rpp_py.capnp_schema as capnp_schema
from rpp_py.rpp_runtime_client_context import RppRuntimeClientContext
from rpp_py.component_call_executor import ComponentCallExecutor
from rpp_py.adapter_info import AdapterClientParams, AdapterClientInfo
from rpp_py.logger import RppLogger
from rpp_plugin_types.rpp_common.DisturbanceGenerator2D import DisturbanceGenerator2D
from rpp_py.plugin_runtime import RuntimeConstants
from rpp_py.lifecycle import CallbackResult, DeactivationResult
import asyncio
from rpp_schema.rpp_common.Pose2D import Pose2D as _Pose2D

def _to_capnp_value(value):
    if hasattr(value, "as_dict"):
        return value.as_dict()
    if hasattr(value, "to_dict"):
        return value.to_dict()
    if isinstance(value, (list, tuple)):
        return [_to_capnp_value(item) for item in value]
    if isinstance(value, dict):
        return {key: _to_capnp_value(item) for key, item in value.items()}
    return value

class DisturbanceGenerator2D_AdapterClient(DisturbanceGenerator2D):
    Pose2D = _Pose2D

    def on_configure(self, context) -> CallbackResult:
        return CallbackResult.failure("Remote lifecycle control is not supported yet")

    def on_cleanup(self) -> CallbackResult:
        return CallbackResult.failure("Remote lifecycle control is not supported yet")

    def on_activate(self) -> CallbackResult:
        return CallbackResult.failure("Remote lifecycle control is not supported yet")

    def on_deactivate(self) -> CallbackResult:
        return CallbackResult.failure("Remote lifecycle control is not supported yet")

    def __init__(self, logger: RppLogger | None = None):
        self._adapter_client_params: AdapterClientParams = None
        self._logger = logger
        self._client = None
        self._runtime = None
        self._component_call_executor = None
        self._owned_component_call_executor = None
        self._runtime_client_context = None
        self._owns_runtime_client_context = False
        self._caller_loop = None

    def configure_adapter_client__(self, adapter_client_params: AdapterClientParams):
        self._adapter_client_params = adapter_client_params
        self._adapter_client_info = AdapterClientInfo()
        self._adapter_client_info.plugin_name = adapter_client_params.plugin_name
        self._adapter_client_info.name = adapter_client_params.name \
            if adapter_client_params.name else \
                f"{adapter_client_params.plugin_name}_adapter_client"
        self._adapter_client_info.connection_name = adapter_client_params.connection_name \
            if adapter_client_params.connection_name else \
                f"{adapter_client_params.plugin_name}_connection"
        if self._logger is None:
            self._logger = RppLogger(self._adapter_client_info.name)

    def connect_adapter_client__(
            self, context: RppRuntimeClientContext, executor=None):
        if self._adapter_client_params is None:
            raise RuntimeError("Adapter client params is not configured. Please call configure_adapter_client__() first.")
        owns_runtime_client_context = executor is None
        owned_executor = None
        if owns_runtime_client_context:
            if context.is_started:
                raise RuntimeError(
                    "An adapter-owned executor requires an unstarted runtime context.")
            owned_executor = ComponentCallExecutor()
            owned_executor.start()
            executor = owned_executor

        self._configure_adapter_client_connection__(
            context, executor, owns_runtime_client_context, owned_executor)
        try:
            return executor.call(self._connect_adapter_client_on_executor__())
        except Exception:
            try:
                executor.call(self._disconnect_adapter_client_on_executor__())
            finally:
                if owned_executor is not None:
                    owned_executor.stop()
            raise

    async def _connect_adapter_client_with_executor__(
            self, context: RppRuntimeClientContext, executor):
        if self._adapter_client_params is None:
            raise RuntimeError("Adapter client params is not configured. Please call configure_adapter_client__() first.")
        self._configure_adapter_client_connection__(
            context, executor, False, None)
        return await self._connect_adapter_client_on_executor__()

    async def connect_adapter_client_async(self, context: RppRuntimeClientContext):
        if self._adapter_client_params is None:
            raise RuntimeError("Configure adapter client parameters before connecting.")
        self._configure_adapter_client_connection__(context, None, not context.is_started, None)
        self._caller_loop = asyncio.get_running_loop()
        try:
            return await self._connect_adapter_client_on_executor__()
        except Exception:
            try:
                await self._disconnect_adapter_client_on_executor__()
            except Exception as error:
                self._logger.error(f"Async component connection rollback failed: {error!r}")
            raise

    async def disconnect_adapter_client_async(self):
        if self._caller_loop is None:
            raise RuntimeError("This component client is not owned by the calling asyncio loop.")
        if asyncio.get_running_loop() is not self._caller_loop:
            raise RuntimeError("Use the asyncio loop that owns this component client.")
        await self._disconnect_adapter_client_on_executor__()

    def _configure_adapter_client_connection__(
            self, context: RppRuntimeClientContext, executor,
            owns_runtime_client_context: bool, owned_executor):
        self._runtime_client_context = context
        self._component_call_executor = executor
        self._owns_runtime_client_context = owns_runtime_client_context
        self._owned_component_call_executor = owned_executor
        self._caller_loop = None

    async def _connect_adapter_client_on_executor__(self):
        if self._owns_runtime_client_context:
            connected, error = await self._runtime_client_context.start()
            if not connected:
                raise RuntimeError("Failed to connect adapter client runtime.") from error
        self._runtime = self._runtime_client_context.get_runtime()

        runtime_class = RuntimeConstants.get_capnp_schema().PluginRuntime
        self._runtime_client = self._runtime_client_context.get_client().cast_as(runtime_class)
        capability = await self._runtime_client.getComponentCapability(
            self._adapter_client_info.connection_name)
        interface_class = capnp_schema.get_client_class("rpp_common::DisturbanceGenerator2D", "disturbance_generator.capnp")
        # Cap'n Proto represents an ``AnyPointer`` capability result as a
        # dynamic object reader. Convert that reader to the concrete
        # interface first; ``cast_as()`` is only available once it is a
        # capability client.
        self._client = capability.pluginRef.as_interface(interface_class)
        return True

    def disconnect_adapter_client__(self):
        if self._caller_loop is not None:
            raise RuntimeError("Use disconnect_adapter_client_async for an asyncio-owned client.")
        executor = self._component_call_executor
        if executor is None:
            return
        owned_executor = self._owned_component_call_executor
        try:
            executor.call(self._disconnect_adapter_client_on_executor__())
        finally:
            if owned_executor is not None:
                owned_executor.stop()

    async def _disconnect_adapter_client_on_executor__(self):
        self._adapter_client_params = None
        self._client = None
        self._runtime = None
        self._component_call_executor = None
        if self._owns_runtime_client_context and \
                self._runtime_client_context is not None:
            await self._runtime_client_context.stop()
        self._runtime_client_context = None
        self._owns_runtime_client_context = False
        self._owned_component_call_executor = None
        self._caller_loop = None

    def decode_lifecycle_state__(self, schema_id, payload):
        if schema_id:
            return CallbackResult.failure("This plugin does not accept lifecycle state"), None
        return CallbackResult(), None

    def encode_lifecycle_state__(self, state, wire):
        if state is not None:
            return CallbackResult.failure("This plugin does not provide lifecycle state")
        wire.schemaId = 0
        return CallbackResult()

    
    def step(self, state: Pose2D, dt: float, **kwargs)-> Pose2D:
        if self._component_call_executor is None:
            if self._caller_loop is not None:
                raise RuntimeError("Use step_async for a client owned by an asyncio loop.")
            raise RuntimeError(
                "Client is not connected. Call connect_adapter_client__() first.")
        return self._component_call_executor.call(
            self._step_on_executor__(state=state, dt=dt))

    async def step_async(self, state: Pose2D, dt: float, **kwargs)-> Pose2D:
        if self._component_call_executor is None:
            if self._caller_loop is not None:
                if asyncio.get_running_loop() is not self._caller_loop:
                    raise RuntimeError("Use the asyncio loop that owns this component client.")
                return await self._step_on_executor__(state=state, dt=dt)
            raise RuntimeError(
                "Client is not connected. Call connect_adapter_client__() first.")
        return await asyncio.wrap_future(
            self._component_call_executor.submit(
                self._step_on_executor__(state=state, dt=dt)))

    async def _step_on_executor__(self, state: Pose2D, dt: float, **kwargs)-> Pose2D:
        if self._client is None:
            raise RuntimeError("Client is not configured. Please call configure_adapter_client__() first.")
        self._logger.debug(
            f"Calling component: component={self._adapter_client_info.name!r}, "
            f"method='step'.")
        response = await self._client.step(state=_to_capnp_value(state), dt=_to_capnp_value(dt))
        self._logger.debug(
            f"Component call completed: component={self._adapter_client_info.name!r}, "
            f"method='step'.")
        return response.state_disturbed

    def validate(self, state: Pose2D, **kwargs)-> bool:
        if self._component_call_executor is None:
            if self._caller_loop is not None:
                raise RuntimeError("Use validate_async for a client owned by an asyncio loop.")
            raise RuntimeError(
                "Client is not connected. Call connect_adapter_client__() first.")
        return self._component_call_executor.call(
            self._validate_on_executor__(state=state))

    async def validate_async(self, state: Pose2D, **kwargs)-> bool:
        if self._component_call_executor is None:
            if self._caller_loop is not None:
                if asyncio.get_running_loop() is not self._caller_loop:
                    raise RuntimeError("Use the asyncio loop that owns this component client.")
                return await self._validate_on_executor__(state=state)
            raise RuntimeError(
                "Client is not connected. Call connect_adapter_client__() first.")
        return await asyncio.wrap_future(
            self._component_call_executor.submit(
                self._validate_on_executor__(state=state)))

    async def _validate_on_executor__(self, state: Pose2D, **kwargs)-> bool:
        if self._client is None:
            raise RuntimeError("Client is not configured. Please call configure_adapter_client__() first.")
        self._logger.debug(
            f"Calling component: component={self._adapter_client_info.name!r}, "
            f"method='validate'.")
        response = await self._client.validate(state=_to_capnp_value(state))
        self._logger.debug(
            f"Component call completed: component={self._adapter_client_info.name!r}, "
            f"method='validate'.")
        return response.ok

