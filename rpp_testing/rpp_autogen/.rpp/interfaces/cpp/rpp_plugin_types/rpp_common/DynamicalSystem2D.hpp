#pragma once
#include <string>
#include "rpp_cpp/plugin.hpp"
#include "rpp_cpp/context.hpp"
#include "map"
#include <type_traits>
#include <memory>
#include "rpp_schema/rpp_common/Pose2D.hpp"



namespace rpp_common{

namespace hidden {
    class DynamicalSystem2D_Adapter_Client;
    class DynamicalSystem2D_Adapter_Server;
}

class DynamicalSystem2D : public rpp::LifecyclePlugin<void> {


public:
    DynamicalSystem2D() = default;
    virtual ~DynamicalSystem2D() = default;

    using AdapterClient = hidden::DynamicalSystem2D_Adapter_Client;
    using AdapterServer = hidden::DynamicalSystem2D_Adapter_Server;


    using Pose2D = rpp_schema::rpp_common::Pose2D;
    using Pose2D_S = rpp_schema::rpp_common::Pose2D_Native;

    virtual Pose2D::Const step(Pose2D::Const state, double dt) = 0;

    virtual bool validate(Pose2D::Const state) = 0;


};

}  // namespace

#include "DynamicalSystem2D_Adapter_Client.hpp"
#include "DynamicalSystem2D_Adapter_Server.hpp"
