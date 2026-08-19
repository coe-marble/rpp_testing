#include <rpp_plugin_types/rpp_testing/TestInterfaceAll.hpp>




class AllInterfaceTypesCpp : public rpp_testing::TestInterfaceAll
{
    public:

    AllInterfaceTypesCpp() = default;

    virtual ~AllInterfaceTypesCpp() = default;


    void initialize(const rpp::ComponentContext& context) override
    {
        // Do nothing for this example plugin
    }


    void funcEmpty() override
    {
        // Do nothing
    }

    double funcWithSimpleParams(double paramFloat, bool paramBool) override
    {
        return paramFloat * (paramBool ? 2.0 : 1.0);
    }

    TestStruct1::Const funcWithStructParam(TestStruct1::Const paramStruct1, TestStruct2::Const paramStruct2) override
    {
        TestStruct1 result;
        result.x() = paramStruct1.x() + paramStruct2.linear();
        result.y() = paramStruct1.y() + paramStruct2.angular();
        result.theta() = paramStruct1.theta() + (paramStruct2.linear() + paramStruct2.angular()) / 2.0;
        return result;
    }

    rpp::ListConst<double> funcWithListParam(rpp::ListConst<double> paramListFloat, rpp::ListConst<TestStruct1> paramListStruct) override
    {
        rpp::List<double> result;
        result.resize(paramListFloat.size() + paramListStruct.size());
        for (size_t i = 0; i < paramListFloat.size(); ++i)
        {
            result[i] = paramListFloat[i];
        }
        for (size_t i = 0; i < paramListStruct.size(); ++i)
        {
            result[paramListFloat.size() + i] = paramListStruct[i].x() + paramListStruct[i].y();
        }
        return result;
    }

    TestStruct2::Const::List funcWithListOfStructParam(TestStruct1::Const::List paramListStruct) override
    {
        TestStruct2::List result;
        result.resize(paramListStruct.size());
        for (size_t i = 0; i < paramListStruct.size(); ++i)
        {
            result[i].linear() = paramListStruct[i].x() + paramListStruct[i].y();
            result[i].angular() = paramListStruct[i].theta();

            result[i].struct1().x() = paramListStruct[i].x() * 2.0;
            result[i].struct1().y() = paramListStruct[i].y() * 2.0;
            result[i].struct1().theta() = paramListStruct[i].theta() * 2.0;
        }
        return result;
    }

    std::tuple<double, bool> funcWithMultipleSimpleReturns() override
    {
        return std::make_tuple(3.14, true);
    }

    std::tuple<TestStruct1::Const, TestStruct2::Const> funcWithMultipleStructReturns() override
    {
        TestStruct1 result1;
        result1.x() = 1.0;
        result1.y() = 2.0;
        result1.theta() = 3.0;

        TestStruct2 result2;
        result2.linear() = 4.0;
        result2.angular() = 5.0;
        result2.struct1().x() = 2.0;
        result2.struct1().y() = 3.0;
        result2.struct1().theta() = 4.0;



        return std::make_tuple(std::move(result1), std::move(result2));
    }

    std::tuple<rpp::ListConst<double>, TestStruct1::Const::List> funcWithMultipleListReturns() override
    {
        rpp::List<double> resultListFloat;
        resultListFloat.resize(3);
        resultListFloat[0] = 1.0;
        resultListFloat[1] = 2.0;
        resultListFloat[2] = 3.0;

        TestStruct1::List resultListStruct;
        resultListStruct.resize(2);
        resultListStruct[0].x() = 4.0;
        resultListStruct[0].y() = 5.0;
        resultListStruct[0].theta() = 6.0;
        resultListStruct[1].x() = 7.0;
        resultListStruct[1].y() = 8.0;
        resultListStruct[1].theta() = 9.0;

        return std::make_tuple(std::move(resultListFloat), std::move(resultListStruct));
    }


};

// interface TestInterfaceAll $Anot.plugin("test") {
//   funcEmpty @0 () -> ();
//   funcWithSimpleParams @1 (paramFloat :Float64, paramBool :Bool) -> (resultFloat :Float64);
//   funcWithStructParam @2 (paramStruct1 :TestStruct1, paramStruct2 :TestStruct2) -> (resultStruct1 :TestStruct1);
//   funcWithListParam @3 (paramListFloat :List(Float64), paramListStruct :List(TestStruct1)) -> (resultList :List(Float64));
//   funcWithListOfStructParam @4 (paramListStruct :List(TestStruct1)) -> (resultListStruct2 :List(TestStruct2));
//   funcWithMultipleSimpleReturns @5 () -> (resultFloat :Float64, resultBool :Bool);
//   funcWithMultipleStructReturns @6 () -> (resultStruct1 :TestStruct1, resultStruct2 :TestStruct2);
//   funcWithMultipleListReturns @7 () -> (resultListFloat :List(Float64), resultListStruct :List(TestStruct1));
// }

// struct TestStruct1 {
//     x @0 :Float64;
//     y @1 :Float64;
//     theta @2 :Float64;
// }

// struct TestStruct2 {
//     linear @0 :Float64;
//     angular @1 :Float64;
// }