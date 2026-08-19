#include <rpp_plugin_types/rpp_testing/MotionController2D.hpp>


using Controller = rpp_testing::MotionController2D;

class ComponentPluginWithTypeAliasOutsideClass : public Controller
{


public:
    ComponentPluginWithTypeAliasOutsideClass() = default;

    virtual ~ComponentPluginWithTypeAliasOutsideClass() = default;

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


