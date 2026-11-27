@0xaaaa000000000001;

struct Point2D {
    x @0 :Float64;
    y @1 :Float64;
}

struct Point3D {
    x @0 :Float64;
    y @1 :Float64;
    z @2 :Float64;
}

struct Quaternion {
    x @0 :Float64;
    y @1 :Float64;
    z @2 :Float64;
    w @3 :Float64;
}

struct Pose2D {
    position @0 :Point2D;
    yaw @1 :Float64;
}

struct Pose3D {
    position @0 :Point3D;
    orientation @1 :Quaternion;
}

struct Twist2D {
    linear @0 :Point2D;
    angular @1 :Float64;
}

struct Twist3D {
    linear @0 :Point3D;
    angular @1 :Point3D;
}

struct Wrench2D {
    force @0 :Point2D;
    torque @1 :Float64;
}

struct Wrench3D {
    force @0 :Point3D;
    torque @1 :Point3D;
}

struct Odometry2D {
    pose @0 :Pose2D;
    twist @1 :Twist2D;
}

struct Odometry3D {
    pose @0 :Pose3D;
    twist @1 :Twist3D;
}

struct Command {
    data @0 :List(Float64);
}

# Dense row-major matrix used for numeric component handover state. An empty
# matrix has zero rows, zero columns, and no values.
struct FloatMatrix {
    rows @0 :UInt32;
    columns @1 :UInt32;
    values @2 :List(Float64);
}

struct VectorPlanar {
    x @0 :Float64;
    y @1 :Float64;
    yaw @2 :Float64;
}

struct VectorSpatial {
    x @0 :Float64;
    y @1 :Float64;
    z @2 :Float64;
    roll @3 :Float64;
    pitch @4 :Float64;
    yaw @5 :Float64;
}

struct Vector3D {
    x @0 :Float64;
    y @1 :Float64;
    z @2 :Float64;
}

struct Path2D {
    points @0 :List(Point2D);
}

struct Path3D {
    points @0 :List(Point3D);
}
