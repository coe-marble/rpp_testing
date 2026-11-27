@0xbadbadbadbadbbd1;
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

# Generated once with rpp_testing's packaged fixture and consumed by rpp_cpp.
struct AllocationFixedSample {
  a @0 :Float64;
  b @1 :Float64;
  c @2 :Float64;
  d @3 :Float64;
  e @4 :Float64;
  f @5 :Float64;
}

struct AllocationEnvelope {
  name @0 :Text;
  payload @1 :Data;
  values @2 :List(Float64);
  child @3 :AllocationFixedSample;
  history @4 :List(AllocationFixedSample);
}

# Same prefix, with fields an older AllocationFixedSample reader does not know.
struct AllocationEvolvedSample {
  a @0 :Float64;
  b @1 :Float64;
  c @2 :Float64;
  d @3 :Float64;
  e @4 :Float64;
  f @5 :Float64;
  name @6 :Text;
  values @7 :List(Float64);
}

struct AllocationHintedSample {
  values @0 :List(Float64) $Anot.hintSize(6);
  name @1 :Text $Anot.hintSize(15);
  payload @2 :Data $Anot.hintSize(9);
  flags @3 :List(Bool) $Anot.hintSize(65);
  history @4 :List(AllocationFixedSample) $Anot.hintSize(2);
}
