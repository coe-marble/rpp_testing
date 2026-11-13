@0xa372834618a0bc4b;
using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("schema::rpp_testing");
using Msgs = import "rpp_common/msgs.capnp";
using Anot = import "rpp_common/anot.capnp";

interface Controller(State, Command) {
  step     @0 (state :State, dt :Float64) -> (command :Command);
  validate @1 (state :State) -> (ok :Bool);
}


interface DisturbanceGenerator(State) {
  step     @0 (state :State, dt :Float64) -> (state_disturbed :State);
  validate @1 (state :State) -> (ok :Bool);
  setData @2 (data :Data) -> (ok :Bool);
  getData @3 () -> (data :Data);
}

interface DisturbanceGenerator2D extends(DisturbanceGenerator(Msgs.Pose2D))
$Anot.plugin("DisturbanceGenerator2D"){}


interface MotionController2D extends(Controller(Msgs.Odometry2D, Msgs.VectorPlanar))
$Anot.plugin("MotionController2D"){}


struct TestStruct1 {
    x @0 :Float64;
    y @1 :Float64;
    theta @2 :Float64;
}

struct TestStruct2 {
    linear @0 :Float64;
    angular @1 :Float64;
    struct1 @2 :TestStruct1;
}

interface TestInterfaceAll $Anot.plugin("test") {
  funcEmpty @0 () -> ();
  funcWithSimpleParams @1 (paramFloat :Float64, paramBool :Bool) -> (resultFloat :Float64);
  funcWithStructParam @2 (paramStruct1 :TestStruct1, paramStruct2 :TestStruct2) -> (resultStruct1 :TestStruct1);
  funcWithListParam @3 (paramListFloat :List(Float64), paramListStruct :List(TestStruct1)) -> (resultList :List(Float64));
  funcWithListOfStructParam @4 (paramListStruct :List(TestStruct1)) -> (resultListStruct2 :List(TestStruct2));
  funcWithMultipleSimpleReturns @5 () -> (resultFloat :Float64, resultBool :Bool);
  funcWithMultipleStructReturns @6 () -> (resultStruct1 :TestStruct1, resultStruct2 :TestStruct2);
  funcWithMultipleListReturns @7 () -> (resultListFloat :List(Float64), resultListStruct :List(TestStruct1));
}