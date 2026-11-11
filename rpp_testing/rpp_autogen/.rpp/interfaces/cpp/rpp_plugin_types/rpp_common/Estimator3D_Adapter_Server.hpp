
#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <chrono>
#include "rpp_cpp/plugin.hpp"
#include "capnp_gen/rpp_common/estimator.capnp.h"
#include "rpp_cpp/adapter_bases.hpp"
#include "rpp_cpp/capnp_server.hpp"
#include "rpp_cpp/context.hpp"
#include "rpp_cpp/logger.hpp"

namespace rpp_common::hidden{

class Estimator3D_Adapter_Server
    : public rpp::ServerAdapter,
      public ::schema::rpp_common::Estimator3D::Server
{

private:
    rpp_common::Estimator3D* backend_;
    std::shared_ptr<rpp::ServerAdapterParams> params_ = nullptr;
    std::shared_ptr<rpp::RppLogger> logger_;
    rpp::ServerAdapterInfo info_;
    std::unique_ptr<rpp::runtime::CapnpServer> rpc_server_ = nullptr;

public:

    explicit Estimator3D_Adapter_Server(
        std::shared_ptr<rpp::RppLogger> logger = nullptr)
        : backend_(nullptr),
          logger_(std::move(logger))
    {
        info_.plugin_type = "rpp_common::Estimator3D";
        info_.created_at = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
    }

    capnp::Capability::Client create_capability_adapter_server__() override {
        RPP_LOG_DEBUG(*logger_, "Creating component capability: component=%s.",
                      info_.name.c_str());
        kj::Own<::schema::rpp_common::Estimator3D::Server> owned_server(
            static_cast<::schema::rpp_common::Estimator3D::Server*>(this),
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
        backend_ = dynamic_cast<rpp_common::Estimator3D*>(params->backend.get());
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



    virtual ~Estimator3D_Adapter_Server() noexcept = default;

    ::kj::Promise<void> step(StepContext context) override {
        auto state = context.getParams().getState();
        auto dt = context.getParams().getDt();
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=step.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->step(state, dt);
        context.getResults().setEstimated_state(result);
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=step.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
    ::kj::Promise<void> validate(ValidateContext context) override {
        auto state = context.getParams().getState();
        RPP_LOG_DEBUG(*logger_, "Received request: component=%s method=validate.", info_.name.c_str());
        // Call the backend method and set the results in the context
        auto result = backend_->validate(state);
        context.getResults().setOk(result);
        RPP_LOG_DEBUG(*logger_, "Backend completed: component=%s method=validate.", info_.name.c_str());
        return ::kj::READY_NOW;

}
    
};

}  // namespace

