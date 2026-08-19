#include <rpp_plugin_types/rpp_testing/MotionController2D.hpp>



using namespace rpp_testing;

class ComponentPluginWithUsingNamespace : public MotionController2D
{
public:
    ComponentPluginWithUsingNamespace() = default;

    virtual ~ComponentPluginWithUsingNamespace() = default;

    void initialize(const rpp::ComponentContext& context) override
    {
        // Do nothing for this example plugin
    }

    VectorPlanar::Const step(Odometry2D::Const state, double dt) override
    {
        auto a = 5;
    }

    bool validate(Odometry2D::Const state) override
    {
        Odometry2D_S native_struct = state.as_struct();
        auto x = native_struct.pose.position.x;
        return x > 5.0;
    }

};


