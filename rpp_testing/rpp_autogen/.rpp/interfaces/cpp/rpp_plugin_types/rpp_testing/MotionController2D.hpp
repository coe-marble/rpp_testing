#pragma once
#include <string>
#include "rpp_cpp/plugin.hpp"
#include "rpp_cpp/context.hpp"
#include "map"
#include <type_traits>
#include <memory>
#include "rpp_schema/rpp_common/Odometry2D.hpp"
#include "rpp_schema/rpp_common/VectorPlanar.hpp"



namespace rpp_testing{

namespace hidden {
    class MotionController2D_Adapter_Client;
    class MotionController2D_Adapter_Server;
}

class MotionController2D : public rpp::LifecyclePlugin<void> {


public:
    MotionController2D() = default;
    virtual ~MotionController2D() = default;

    using AdapterClient = hidden::MotionController2D_Adapter_Client;
    using AdapterServer = hidden::MotionController2D_Adapter_Server;


    using Odometry2D = rpp_schema::rpp_common::Odometry2D;
    using Odometry2D_S = rpp_schema::rpp_common::Odometry2D_Native;
    using VectorPlanar = rpp_schema::rpp_common::VectorPlanar;
    using VectorPlanar_S = rpp_schema::rpp_common::VectorPlanar_Native;

    virtual VectorPlanar::Const step(Odometry2D::Const state, double dt) = 0;

    virtual bool validate(Odometry2D::Const state) = 0;


};

}  // namespace

#include "MotionController2D_Adapter_Client.hpp"
#include "MotionController2D_Adapter_Server.hpp"
