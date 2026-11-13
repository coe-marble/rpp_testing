@0xd85ff216c059c458;
using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("schema::rpp_common");
using Msgs = import "rpp_common/msgs.capnp";
using Anot = import "rpp_common/anot.capnp";
interface DynamicalSystem(State) {
  step     @0 (state :State, dt :Float64) -> (new_state :State);
  validate @1 (state :State) -> (ok :Bool);
}

interface DynamicalSystem2D extends(DynamicalSystem(Msgs.Pose2D))
$Anot.plugin("DynamicalSystem2D"){}
interface DynamicalSystem3D extends(DynamicalSystem(Msgs.Pose3D))
$Anot.plugin("DynamicalSystem3D"){}