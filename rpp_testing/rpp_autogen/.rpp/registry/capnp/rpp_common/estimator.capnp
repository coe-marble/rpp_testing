@0xdc068c96e8d1f566;
using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("schema::rpp_common");
using Msgs = import "rpp_common/msgs.capnp";
using Anot = import "rpp_common/anot.capnp";
interface Estimator(State) {
  step     @0 (state :State, dt :Float64) -> (estimated_state :State);
  validate @1 (state :State) -> (ok :Bool);
}

interface Estimator2D extends(Estimator(Msgs.Pose2D))
$Anot.plugin("Estimator2D"){}
interface Estimator3D extends(Estimator(Msgs.Pose3D))
$Anot.plugin("Estimator3D"){}