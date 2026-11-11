
#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <chrono>
#include "rpp_cpp/plugin.hpp"
#include "capnp_gen/rpp_testing/test_plugin_types.capnp.h"
#include "rpp_cpp/adapter_bases.hpp"
#include "rpp_cpp/capnp_server.hpp"
#include "rpp_cpp/context.hpp"
#include "rpp_cpp/logger.hpp"

namespace rpp_testing::hidden{

class TestInterfaceAll_Adapter_Server
    : public rpp::ServerAdapter,
      public ::schema::rpp_testing::TestInterfaceAll::Server
{

private:
    rpp_testing::TestInterfaceAll* backend_;
    std::shared_ptr<rpp::ServerAdapterParams> params_ = nullptr;
    std::shared_ptr<rpp::RppLogger> logger_;
    rpp::ServerAdapterInfo info_;
    std::unique_ptr<rpp::runtime::CapnpServer> rpc_server_ = nullptr;

public:

    explicit TestInterfaceAll_Adapter_Server(
        std::shared_ptr<rpp::RppLogger> logger = nullptr)
        : backend_(nullptr),
          logger_(std::move(logger))
    {
        info_.plugin_type = "rpp_testing::TestInterfaceAll";
        info_.created_at = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
    }

    capnp::Capability::Client create_capability_adapter_server__() override {
        RPP_LOG_DEBUG(*logger_, "Creating component capability: component=%s.",
                      info_.name.c_str());
        kj::Own<::schema::rpp_testing::TestInterfaceAll::Server> owned_server(
            static_cast<::schema::rpp_testing::TestInterfaceAll::Server*>(this),
            kj::NullDisposer::instance
        );
        return capnp::Capability::Client(std::move(owned_server));
    }

    void start_adapter_server__(kj::AsyncIoContext& io, std::string host, uint16_t port) override {
        if (!backend_) {
            throw std::runtime_error("RPC server is not initialized. Call configure_adapter_server__ first.");
        }
        auto server_cap = create_capability_adapter_server__();
        rpc_server_ = std::make_unique<rpp::runtime::CapnpServer>(io, host, port, server_cap);
        RPP_LOG_DEBUG(*logger_, "Started adapter RPC server: component=%s host=%s port=%d.",
                      info_.name.c_str(), host.c_str(), port);
    }

    bool configure_adapter_server__(std::shared_ptr<rpp::ServerAdapterParams> params) override {
        if (!params) {
            throw std::invalid_argument("Params cannot be null");
        }
        params_ = params;
        info_.name = params->name;
        info_.plugin_name = params->plugin_name;
        info_.connection_name = params->connection_name;
        backend_ = dynamic_cast<rpp_testing::TestInterfaceAll*>(params->backend.get());
        if (!logger_) {
            logger_ = std::make_shared<rpp::RppLogger>(info_.name);
        }
        RPP_LOG_DEBUG(*logger_, "Configured adapter server: component=%s connection=%s.",
                      info_.name.c_str(), info_.connection_name.c_str());
        return true;
    }

    void close_adapter_server__() override {
        RPP_LOG_DEBUG(*logger_, "Stopping adapter RPC server: component=%s.",
                      info_.name.c_str());
        rpc_server_.reset();
    }

    const rpp::ServerAdapterInfo& get_info_adapter_server__() const override {
        return info_;
    }



    virtual ~TestInterfaceAll_Adapter_Server() noexcept = default;

    ::kj::Promise<void> funcEmpty(FuncEmptyContext /* context */) override {
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=funcEmpty.", info_.name.c_str());
        // Call the backend method and set the results in the context
        backend_->funcEmpty();        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=funcEmpty.", info_.name.c_str());
        return ::kj::READY_NOW;
}
    
    ::kj::Promise<void> funcWithSimpleParams(FuncWithSimpleParamsContext context) override {
        auto paramFloat = context.getParams().getParamFloat();
        auto paramBool = context.getParams().getParamBool();
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=funcWithSimpleParams.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->funcWithSimpleParams(paramFloat, paramBool);
        context.getResults().setResultFloat(result);
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=funcWithSimpleParams.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
    ::kj::Promise<void> funcWithStructParam(FuncWithStructParamContext context) override {
        auto paramStruct1 = context.getParams().getParamStruct1();
        auto paramStruct2 = context.getParams().getParamStruct2();
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=funcWithStructParam.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->funcWithStructParam(paramStruct1, paramStruct2);
        context.getResults().setResultStruct1(result);
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=funcWithStructParam.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
    ::kj::Promise<void> funcWithListParam(FuncWithListParamContext context) override {
        auto paramListFloat = context.getParams().getParamListFloat();
        auto paramListStruct = context.getParams().getParamListStruct();
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=funcWithListParam.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->funcWithListParam(paramListFloat, paramListStruct);
        context.getResults().setResultList(result);
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=funcWithListParam.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
    ::kj::Promise<void> funcWithListOfStructParam(FuncWithListOfStructParamContext context) override {
        auto paramListStruct = context.getParams().getParamListStruct();
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=funcWithListOfStructParam.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->funcWithListOfStructParam(paramListStruct);
        context.getResults().setResultListStruct2(result);
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=funcWithListOfStructParam.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
    ::kj::Promise<void> funcWithMultipleSimpleReturns(FuncWithMultipleSimpleReturnsContext context) override {
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=funcWithMultipleSimpleReturns.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->funcWithMultipleSimpleReturns();
        context.getResults().setResultFloat(std::get<0>(result));
        context.getResults().setResultBool(std::get<1>(result));
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=funcWithMultipleSimpleReturns.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
    ::kj::Promise<void> funcWithMultipleStructReturns(FuncWithMultipleStructReturnsContext context) override {
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=funcWithMultipleStructReturns.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->funcWithMultipleStructReturns();
        context.getResults().setResultStruct1(std::get<0>(result));
        context.getResults().setResultStruct2(std::get<1>(result));
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=funcWithMultipleStructReturns.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
    ::kj::Promise<void> funcWithMultipleListReturns(FuncWithMultipleListReturnsContext context) override {
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=funcWithMultipleListReturns.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->funcWithMultipleListReturns();
        context.getResults().setResultListFloat(std::get<0>(result));
        context.getResults().setResultListStruct(std::get<1>(result));
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=funcWithMultipleListReturns.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
};

}  // namespace

