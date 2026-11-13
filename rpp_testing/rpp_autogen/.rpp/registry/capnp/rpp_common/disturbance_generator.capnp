@0xb97711affac7f79e;
using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("schema::rpp_common");
using Msgs = import "rpp_common/msgs.capnp";
using Anot = import "rpp_common/anot.capnp";
interface DisturbanceGenerator(State) {
  step     @0 (state :State, dt :Float64) -> (state_disturbed :State);
  validate @1 (state :State) -> (ok :Bool);
}

interface DisturbanceGenerator2D extends(DisturbanceGenerator(Msgs.Pose2D))
$Anot.plugin("DisturbanceGenerator2D"){}

interface DisturbanceGenerator3D extends(DisturbanceGenerator(Msgs.Pose3D))
$Anot.plugin("DisturbanceGenerator3D"){}