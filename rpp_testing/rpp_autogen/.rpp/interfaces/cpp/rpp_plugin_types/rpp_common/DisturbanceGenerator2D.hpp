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
    class DisturbanceGenerator2D_Adapter_Client;
    class DisturbanceGenerator2D_Adapter_Server;
}

class DisturbanceGenerator2D : public rpp::LifecyclePlugin<void> {


public:
    DisturbanceGenerator2D() = default;
    virtual ~DisturbanceGenerator2D() = default;

    using AdapterClient = hidden::DisturbanceGenerator2D_Adapter_Client;
    using AdapterServer = hidden::DisturbanceGenerator2D_Adapter_Server;


    using Pose2D = rpp_schema::rpp_common::Pose2D;
    using Pose2D_S = rpp_schema::rpp_common::Pose2D_Native;

    virtual Pose2D::Const step(Pose2D::Const state, double dt) = 0;

    virtual bool validate(Pose2D::Const state) = 0;


};

}  // namespace

// Include the adapter headers explicitly when constructing communication adapters.
// Keeping their implementations separate prevents optimized native calls from
// acquiring references to the schema RPC implementations.
