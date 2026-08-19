#include <rpp_plugin_types/rpp_testing/MotionController2D.hpp>
#include <rpp_schema/rpp_common/Path2D.hpp>
#include <rpp_schema/rpp_common/Command.hpp>


RPP_PARAM_STRUCT(TestStruct1,
    RPP_MEMBER(int, width, 641),
    RPP_MEMBER(std::string, height, "481"),
    RPP_MEMBER(double, fps, 31.0)
)

RPP_PARAM_STRUCT(TestStruct2,
    RPP_MEMBER(TestStruct1, struct1, TestStruct1()),
    RPP_MEMBER(std::vector<int>, values, std::vector<int>{2, 3, 4})
)


class ComponentPluginSimpleCpp : public rpp_testing::MotionController2D
{
    public:

    RPP_PARAMETERS(
        rpp::params::ParameterDescription::create<int>("int_var", 2),
        rpp::params::ParameterDescription::create<float>("float_var", 6.0f),
        rpp::params::ParameterDescription::create<std::string>("str_var", "test1"),
        rpp::params::ParameterDescription::create<TestStruct1>("struct1_var", TestStruct1{}),
        rpp::params::ParameterDescription::create<TestStruct2>("struct2_var", TestStruct2{})
    )

    ComponentPluginSimpleCpp() = default;

    virtual ~ComponentPluginSimpleCpp() = default;

    void initialize(const rpp::ComponentContext& context) override
    {
        // Do nothing for this example plugin
    }

    VectorPlanar::Const step(Odometry2D::Const state, double dt) override
    {

        rpp_schema::rpp_common::Path2D path;
        path.points().resize(2);
        path.points()[0].x() = 1.0;
        path.points()[0].y() = 2.0;
        path.points()[1].x() = 3.0;
        path.points()[1].y() = 4.0;

        auto point_as_struct = path.points()[1].as_struct();

        rpp_schema::rpp_common::Command command;

        command.data().resize(2);
        command.data()[0] = 0.0;
        command.data()[1] = 1.0;

        VectorPlanar vector;
        vector.x() = point_as_struct.x;
        vector.y() = command.data()[1];
        vector.yaw() = 3.14;
        return std::move(vector);
    }

    bool validate(Odometry2D::Const state) override
    {
        auto x = state.pose().position().x();
        return x > 5.0;
    }

};