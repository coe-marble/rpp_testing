from __future__ import annotations

class EmptyWorkspace:
    COMPONENTS = {}

    def run(self) -> None:
        raise NotImplementedError("Define the workspace logic here.")
