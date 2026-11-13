#pragma once
#include <string>
#include "rpp_cpp/plugin.hpp"
#include "rpp_cpp/context.hpp"
#include "map"
#include <type_traits>
#include <memory>
#include "rpp_schema/rpp_testing/TestStruct1.hpp"
#include "rpp_schema/rpp_testing/TestStruct2.hpp"



namespace rpp_testing{

namespace hidden {
    class TestInterfaceAll_Adapter_Client;
    class TestInterfaceAll_Adapter_Server;
}

class TestInterfaceAll : public rpp::LifecyclePlugin<void> {


public:
    TestInterfaceAll() = default;
    virtual ~TestInterfaceAll() = default;

    using AdapterClient = hidden::TestInterfaceAll_Adapter_Client;
    using AdapterServer = hidden::TestInterfaceAll_Adapter_Server;


    using TestStruct1 = rpp_schema::rpp_testing::TestStruct1;
    using TestStruct1_S = rpp_schema::rpp_testing::TestStruct1_Native;
    using TestStruct2 = rpp_schema::rpp_testing::TestStruct2;
    using TestStruct2_S = rpp_schema::rpp_testing::TestStruct2_Native;

    virtual void funcEmpty() = 0;

    virtual double funcWithSimpleParams(double paramFloat, bool paramBool) = 0;

    virtual TestStruct1::Const funcWithStructParam(TestStruct1::Const paramStruct1, TestStruct2::Const paramStruct2) = 0;

    virtual rpp::ListConst<double> funcWithListParam(rpp::ListConst<double> paramListFloat, TestStruct1::Const::List paramListStruct) = 0;

    virtual TestStruct2::Const::List funcWithListOfStructParam(TestStruct1::Const::List paramListStruct) = 0;

    virtual std::tuple<double, bool> funcWithMultipleSimpleReturns() = 0;

    virtual std::tuple<TestStruct1::Const, TestStruct2::Const> funcWithMultipleStructReturns() = 0;

    virtual std::tuple<rpp::ListConst<double>, TestStruct1::Const::List> funcWithMultipleListReturns() = 0;


};

}  // namespace

// Include the adapter headers explicitly when constructing communication adapters.
// Keeping their implementations separate prevents optimized native calls from
// acquiring references to the schema RPC implementations.
