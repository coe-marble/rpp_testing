#pragma once
#include "DisturbanceGenerator2D.hpp"
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
#include "capnp_gen/rpp_common/disturbance_generator.capnp.h"

namespace rpp_common::hidden{

class DisturbanceGenerator2D_Adapter_Client
    : public rpp_common::DisturbanceGenerator2D,
      public rpp::ClientAdapter
{


private:
    std::shared_ptr<rpp::ClientAdapterParams> params_;
    std::shared_ptr<rpp::RppLogger> logger_;
    rpp::ClientAdapterInfo info_;

    const kj::AsyncIoContext* io_ = nullptr;
    std::optional<std::reference_wrapper<rpp::ComponentCallExecutor>> executor_;
    ::schema::rpp_common::DisturbanceGenerator2D::Client backend_;

public:
    explicit DisturbanceGenerator2D_Adapter_Client(
        std::shared_ptr<rpp::RppLogger> logger = nullptr)
        : params_(nullptr),
          logger_(std::move(logger)),
          backend_(nullptr)
    {
        info_.plugin_name = "rpp_common::{class_name}";
        info_.plugin_type = "rpp_common::DisturbanceGenerator2D";
        info_.created_at = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
    }

    virtual ~DisturbanceGenerator2D_Adapter_Client() noexcept = default;

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
            backend_ = response.getPluginRef().castAs<::schema::rpp_common::DisturbanceGenerator2D>();
            RPP_LOG_DEBUG(*logger_, "Component capability connected: component=%s.",
                          info_.name.c_str());
            return true;
        } catch (const kj::Exception& e) {
            // Try to reconnect using direct connection to the plugin server
            RPP_LOG_WARN(*logger_,
                         "Runtime capability request failed for component=%s; using direct client.",
                         info_.name.c_str());
            backend_ = client.castAs<::schema::rpp_common::DisturbanceGenerator2D>();
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


    Pose2D::Const step(Pose2D::Const state, double dt) override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=step.",
                          info_.name.c_str());
            auto request = backend_.stepRequest();
        request.setState(state);
        request.setDt(dt);

        auto response = request.send().wait(io_->waitScope);
        auto response_owner = std::make_shared<decltype(response)>(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=step.", info_.name.c_str());
        return Pose2D::Const(response_owner->getState_disturbed(), response_owner);
        }
        return executor_->get().call([this, &state, &dt](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=step.",
                      info_.name.c_str());
        auto request = backend_.stepRequest();
        request.setState(state);
        request.setDt(dt);

        auto response = request.send().wait(io.waitScope);
        auto response_owner = executor_->get().retain(std::move(response));
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=step.", info_.name.c_str());
        return Pose2D::Const(response_owner->getState_disturbed(), response_owner);
        });
    }

    bool validate(Pose2D::Const state) override {
        if (!executor_.has_value()) {
            RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=validate.",
                          info_.name.c_str());
            auto request = backend_.validateRequest();
        request.setState(state);

        auto response = request.send().wait(io_->waitScope);
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=validate.", info_.name.c_str());
        return response.getOk();
        }
        return executor_->get().call([this, &state](kj::AsyncIoContext& io) {
        RPP_LOG_DEBUG(*logger_, "Calling component: component=%s method=validate.",
                      info_.name.c_str());
        auto request = backend_.validateRequest();
        request.setState(state);

        auto response = request.send().wait(io.waitScope);
        RPP_LOG_DEBUG(*logger_, "Component call completed: component=%s method=validate.", info_.name.c_str());
        return response.getOk();
        });
    }

};

}  // namespace

