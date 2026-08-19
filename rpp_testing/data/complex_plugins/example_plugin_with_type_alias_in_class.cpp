#include <rpp_plugin_types/rpp_testing/MotionController2D.hpp>


class ComponentPluginWithTypeAliasInClass : public rpp_testing::MotionController2D
{

    using Controller = rpp_testing::MotionController2D;

public:
    ComponentPluginWithTypeAliasInClass() = default;

    virtual ~ComponentPluginWithTypeAliasInClass() = default;

    void initialize(const rpp::ComponentContext& context) override
    {
        // Do nothing for this example plugin
    }

    Controller::VectorPlanar::Const step(Controller::Odometry2D::Const state, double dt) override
    {
        auto a = 5;
    }

    bool validate(rpp_testing::MotionController2D::Odometry2D::Const state) override
    {
        auto a = 5;
        return true;
    }

};


