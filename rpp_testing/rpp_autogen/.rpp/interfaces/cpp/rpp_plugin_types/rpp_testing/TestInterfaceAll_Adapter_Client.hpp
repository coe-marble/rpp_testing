#pragma once
#include "TestInterfaceAll.hpp"
#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include "rpp_cpp/plugin.hpp"
#include "rpp_cpp/adapter_bases.hpp"
#include "rpp_cpp/component_call_executor.hpp"
#include "rpp_cpp/logger.hpp"
#include "rpp_cpp/plugin_runtime.capnp.h"
#include "capnp_gen/rpp_testing/test_plugin_types.capnp.h"

namespace rpp_testing::hidden{

class TestInterfaceAll_Adapter_Client
    : public rpp_testing::TestInterfaceAll,
      public rpp::ClientAdapter
{


private:
    std::shared_ptr<rpp::ClientAdapterParams> params_;
    std::shared_ptr<rpp::RppLogger> logger_;
    rpp::ClientAdapterInfo info_;

    const kj::AsyncIoContext* io_ = nullptr;
    std::optional<std::reference_wrapper<rpp::ComponentCallExecutor>> executor_;
    ::schema::rpp_testing::TestInterfaceAll::Client backend_;

public:
    explicit TestInterfaceAll_Adapter_Client(
        std::shared_ptr<rpp::RppLogger> logger = nullptr)
        : params_(nullptr),
          logger_(std::move(logger)),
          backend_(nullptr)
    {
        info_.plugin_name = "rpp_testing::{class_name}";
        info_.plugin_type = "rpp_testing::TestInterfaceAll";
        info_.created_at = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
    }

    virtual ~TestInterfaceAll_Adapter_Client() noexcept = default;

    bool configure_adapter_client__(std::shared_ptr<rpp::ClientAdapterParams> params) override {
        if (!params) {
            throw std::invalid_argument("Params cannot be null");
        }
        params_ = params;
        info_.name = params->name;
        info_.connection_name = params->connection_name;
        if (!logger_) {
            logger_ = std::make_shared<rpp::RppLogger>(info_.name);
        }
        RPP_LOG_DEBUG(*logger_, "Configured adapter client: component=%s connection=%s.",
                      info_.name.c_str(), info_.connection_name.c_str());
        return true;
    }

    bool connect_adapter_client__(
        const rpp::RppRuntimeClientContext& context,
        std::optional<std::reference_wrapper<rpp::ComponentCallExecutor>> executor =
            std::nullopt) override
    {
        RPP_LOG_DEBUG(*logger_,
                      "Requesting component capability: component=%s connection=%s.",
                      info_.name.c_str(), info_.connection_name.c_str());
        executor_ = executor;
        io_ = &context.get_io_context();

        auto client = context.get_client();
        auto bootstrap_runtime = client.castAs<rpp::runtime::PluginRuntime>();

        auto request = bootstrap_runtime.getComponentCapabilityRequest();
        request.setName(info_.connection_name);
        try {
            auto response = request.send().wait(io_->waitScope);
            backend_ = response.getPluginRef().castAs<::schema::rpp_testing::TestInterfaceAll>();
            RPP_LOG_DEBUG(*logger_, "Component capability connected: component=%s.",
                          info_.name.c_str());
            return true;
        } catch (const kj::Exception& e) {
            // Try to reconnect using direct connection to the plugin server
            RPP_LOG_WARN(*logger_,
                         "Runtime capability request failed for component=%s; using direct client.",
                         info_.name.c_str());
            backend_ = client.castAs<::schema::rpp_testing::TestInterfaceAll>();
            return true;
        }
    }

    const rpp::ClientAdapterInfo& get_info_adapter_client__() const override {
        return info_;
    }




    rpp::CallbackResult on_configure(const rpp::ComponentContext &) override {
        return rpp::CallbackResult::failure("Remote lifecycle control is not supported yet");
    }

    rpp::CallbackResult on_cleanup() override {
        return rpp::CallbackResult::failure("Remote lifecycle control is not supported yet");
    }

    rpp::CallbackResult on_activate() override {
        return rpp::CallbackResult::failure("Remote lifecycle control is not supported yet");
    }

    rpp::CallbackResult on_deactivate() override {
        return rpp::CallbackResult::failure("Remote lifecycle control is not supported yet");
    }


    void reset() override {
        // Reset logic if needed
    }


    void funcEmpty() override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcEmpty.",
                          info_.name.c_str());
            auto request = backend_.funcEmptyRequest();


        request.send().wait(io_->waitScope);
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcEmpty.", info_.name.c_str());
        return;
        }
        return executor_->get().call([this](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcEmpty.",
                      info_.name.c_str());
        auto request = backend_.funcEmptyRequest();


        request.send().wait(io.waitScope);
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcEmpty.", info_.name.c_str());

        });
    }

    double funcWithSimpleParams(double paramFloat, bool paramBool) override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithSimpleParams.",
                          info_.name.c_str());
            auto request = backend_.funcWithSimpleParamsRequest();
        request.setParamFloat(paramFloat);
        request.setParamBool(paramBool);

        auto response = request.send().wait(io_->waitScope);
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithSimpleParams.", info_.name.c_str());
        return response.getResultFloat();
        }
        return executor_->get().call([this, &paramFloat, &paramBool](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithSimpleParams.",
                      info_.name.c_str());
        auto request = backend_.funcWithSimpleParamsRequest();
        request.setParamFloat(paramFloat);
        request.setParamBool(paramBool);

        auto response = request.send().wait(io.waitScope);
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithSimpleParams.", info_.name.c_str());
        return response.getResultFloat();
        });
    }

    TestStruct1::Const funcWithStructParam(TestStruct1::Const paramStruct1, TestStruct2::Const paramStruct2) override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithStructParam.",
                          info_.name.c_str());
            auto request = backend_.funcWithStructParamRequest();
        request.setParamStruct1(paramStruct1);
        request.setParamStruct2(paramStruct2);

        auto response = request.send().wait(io_->waitScope);
        auto response_owner = std::make_shared<decltype(response)>(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithStructParam.", info_.name.c_str());
        return TestStruct1::Const(response_owner->getResultStruct1(), response_owner);
        }
        return executor_->get().call([this, &paramStruct1, &paramStruct2](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithStructParam.",
                      info_.name.c_str());
        auto request = backend_.funcWithStructParamRequest();
        request.setParamStruct1(paramStruct1);
        request.setParamStruct2(paramStruct2);

        auto response = request.send().wait(io.waitScope);
        auto response_owner = executor_->get().retain(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithStructParam.", info_.name.c_str());
        return TestStruct1::Const(response_owner->getResultStruct1(), response_owner);
        });
    }

    rpp::ListConst<double> funcWithListParam(rpp::ListConst<double> paramListFloat, TestStruct1::Const::List paramListStruct) override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithListParam.",
                          info_.name.c_str());
            auto request = backend_.funcWithListParamRequest();
        request.setParamListFloat(paramListFloat);
        request.setParamListStruct(paramListStruct);

        auto response = request.send().wait(io_->waitScope);
        auto response_owner = std::make_shared<decltype(response)>(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithListParam.", info_.name.c_str());
        return rpp::ListConst<double>(response_owner->getResultList(), response_owner);
        }
        return executor_->get().call([this, &paramListFloat, &paramListStruct](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithListParam.",
                      info_.name.c_str());
        auto request = backend_.funcWithListParamRequest();
        request.setParamListFloat(paramListFloat);
        request.setParamListStruct(paramListStruct);

        auto response = request.send().wait(io.waitScope);
        auto response_owner = executor_->get().retain(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithListParam.", info_.name.c_str());
        return rpp::ListConst<double>(response_owner->getResultList(), response_owner);
        });
    }

    TestStruct2::Const::List funcWithListOfStructParam(TestStruct1::Const::List paramListStruct) override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithListOfStructParam.",
                          info_.name.c_str());
            auto request = backend_.funcWithListOfStructParamRequest();
        request.setParamListStruct(paramListStruct);

        auto response = request.send().wait(io_->waitScope);
        auto response_owner = std::make_shared<decltype(response)>(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithListOfStructParam.", info_.name.c_str());
        return TestStruct2::Const::List(response_owner->getResultListStruct2(), response_owner);
        }
        return executor_->get().call([this, &paramListStruct](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithListOfStructParam.",
                      info_.name.c_str());
        auto request = backend_.funcWithListOfStructParamRequest();
        request.setParamListStruct(paramListStruct);

        auto response = request.send().wait(io.waitScope);
        auto response_owner = executor_->get().retain(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithListOfStructParam.", info_.name.c_str());
        return TestStruct2::Const::List(response_owner->getResultListStruct2(), response_owner);
        });
    }

    std::tuple<double, bool> funcWithMultipleSimpleReturns() override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithMultipleSimpleReturns.",
                          info_.name.c_str());
            auto request = backend_.funcWithMultipleSimpleReturnsRequest();


        auto response = request.send().wait(io_->waitScope);
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithMultipleSimpleReturns.", info_.name.c_str());
        return std::make_tuple(response.getResultFloat(), response.getResultBool());
        }
        return executor_->get().call([this](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithMultipleSimpleReturns.",
                      info_.name.c_str());
        auto request = backend_.funcWithMultipleSimpleReturnsRequest();


        auto response = request.send().wait(io.waitScope);
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithMultipleSimpleReturns.", info_.name.c_str());
        return std::make_tuple(response.getResultFloat(), response.getResultBool());
        });
    }

    std::tuple<TestStruct1::Const, TestStruct2::Const> funcWithMultipleStructReturns() override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithMultipleStructReturns.",
                          info_.name.c_str());
            auto request = backend_.funcWithMultipleStructReturnsRequest();


        auto response = request.send().wait(io_->waitScope);
        auto response_owner = std::make_shared<decltype(response)>(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithMultipleStructReturns.", info_.name.c_str());
        return std::make_tuple(TestStruct1::Const(response_owner->getResultStruct1(), response_owner), TestStruct2::Const(response_owner->getResultStruct2(), response_owner));
        }
        return executor_->get().call([this](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithMultipleStructReturns.",
                      info_.name.c_str());
        auto request = backend_.funcWithMultipleStructReturnsRequest();


        auto response = request.send().wait(io.waitScope);
        auto response_owner = executor_->get().retain(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithMultipleStructReturns.", info_.name.c_str());
        return std::make_tuple(TestStruct1::Const(response_owner->getResultStruct1(), response_owner), TestStruct2::Const(response_owner->getResultStruct2(), response_owner));
        });
    }

    std::tuple<rpp::ListConst<double>, TestStruct1::Const::List> funcWithMultipleListReturns() override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithMultipleListReturns.",
                          info_.name.c_str());
            auto request = backend_.funcWithMultipleListReturnsRequest();


        auto response = request.send().wait(io_->waitScope);
        auto response_owner = std::make_shared<decltype(response)>(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithMultipleListReturns.", info_.name.c_str());
        return std::make_tuple(rpp::ListConst<double>(response_owner->getResultListFloat(), response_owner), TestStruct1::Const::List(response_owner->getResultListStruct(), response_owner));
        }
        return executor_->get().call([this](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=funcWithMultipleListReturns.",
                      info_.name.c_str());
        auto request = backend_.funcWithMultipleListReturnsRequest();


        auto response = request.send().wait(io.waitScope);
        auto response_owner = executor_->get().retain(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=funcWithMultipleListReturns.", info_.name.c_str());
        return std::make_tuple(rpp::ListConst<double>(response_owner->getResultListFloat(), response_owner), TestStruct1::Const::List(response_owner->getResultListStruct(), response_owner));
        });
    }

};

}  // namespace

