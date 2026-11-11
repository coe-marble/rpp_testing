#pragma once
#include <string>
#include "rpp_cpp/plugin.hpp"
#include "rpp_cpp/context.hpp"
#include "map"
#include <type_traits>
#include <memory>
#include "rpp_schema/rpp_common/Pose3D.hpp"



namespace rpp_common{

namespace hidden {
    class Estimator3D_Adapter_Client;
    class Estimator3D_Adapter_Server;
}

class Estimator3D : public rpp::LifecyclePlugin<void> {


public:
    Estimator3D() = default;
    virtual ~Estimator3D() = default;

    using AdapterClient = hidden::Estimator3D_Adapter_Client;
    using AdapterServer = hidden::Estimator3D_Adapter_Server;


    using Pose3D = rpp_schema::rpp_common::Pose3D;
    using Pose3D_S = rpp_schema::rpp_common::Pose3D_Native;

    virtual Pose3D::Const step(Pose3D::Const state, double dt) = 0;

    virtual bool validate(Pose3D::Const state) = 0;


};

}  // namespace

#include "Estimator3D_Adapter_Client.hpp"
#include "Estimator3D_Adapter_Server.hpp"
