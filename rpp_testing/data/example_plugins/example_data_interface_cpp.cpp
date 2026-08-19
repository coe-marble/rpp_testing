#include <rpp_plugin_types/rpp_testing/DisturbanceGenerator2D.hpp>


class DataInterfaceCpp : public rpp_testing::DisturbanceGenerator2D
{
    public:

    DataInterfaceCpp() = default;

    virtual ~DataInterfaceCpp() = default;

    void initialize(const rpp::ComponentContext& context) override
    {
        // Do nothing for this example plugin
    }

    bool validate(Pose2D::Const state) override
    {
        // For demonstration, we will consider a state valid if x and y are both non-negative
        return state.position().x() >= 0 && state.position().y() >= 0;
    }

    Pose2D::Const step(Pose2D::Const state, double dt) override
    {
        Pose2D new_state;
        new_state.position().x() = 5;
        new_state.position().y() = 6;
        new_state.yaw() = 7;
        return new_state;
    }

    rpp::DataConst getData() override
    {
        // For demonstration, we will fill the data with some example bytes
        rpp::Data data;
        data.resize(5);
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;
        return data;
    }


    bool setData(rpp::DataConst data) override
    {
        return data.size() == 5 && data[0] == 1 &&
            data[1] == 2 && data[2] == 3 && data[3] == 4 && data[4] == 5;
    }


};

// interface DataInterface {
//   getData @0 () -> (data :Data);
//   setData @1 (data :Data) -> (ok :Bool);
// }
