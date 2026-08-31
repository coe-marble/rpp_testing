from __future__ import annotations
from typing import Any
from dataclasses import dataclass, field

@dataclass
class StructType:

    width: int = 1
    height: str = "2"
    fps: float = 3.0

@dataclass
class ComplextStructType:
    test_struct: StructType = StructType()
    test_struct_list: list[StructType] = field(default_factory=lambda: [StructType(), StructType(width=2, height="3", fps=4.0)])
    test_struct_map: dict[str, StructType] = field(default_factory=lambda: {
        "first": StructType(),
        "second": StructType(width=5, height="6", fps=7.0)
    })

class ComponentParameters:

    float_var: float = 5.0
    int_var: int = 1
    str_var: str = "test"
    list_var: list[int] = [1, 2, 3]
    dict_var: dict[str, str] = {"key": "value"}
    list_dict_var: list[dict[str, str]] = [{"key1": "value1"}, {"key2": "value2"}]
    dict_list_var: dict[str, list[int]] = {"key1": [1, 2, 3], "key2": [4, 5, 6]}
    struct_var: dict[str, Any] = StructType()
    complext_struct_var: dict[str, Any] = ComplextStructType()
    non_dataclass_var: dict[str, Any] = {
        "width": 1,
        "height": "2",
        "fps": 3.0,
        "dict_var": {"key": "value"},
        "test_struct": {"width": 1, "height": "2", "fps": 3.0}
    }