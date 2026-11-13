#pragma once
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_common/msgs.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>

#include "rpp_schema/rpp_common/Point2D.hpp"

namespace rpp_schema::rpp_common{


struct Wrench2D_Native {

    ::rpp_schema::rpp_common::Point2D_Native force;
    double torque;
};


class Wrench2D {
public:


    class Const {

        private:
            schema::rpp_common::Wrench2D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Wrench2D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Wrench2D& main_wrapper);
            Const(Wrench2D&& main_wrapper)
            : reader_(main_wrapper.builder_.asReader()),
              orphaned_msg_builder_(std::move(main_wrapper.msg_builder_)) {}

            Const(Const&& other) noexcept
            : reader_(other.reader_),
              orphaned_msg_builder_(std::move(other.orphaned_msg_builder_)),
              message_lifetime_(std::move(other.message_lifetime_)) {}

            Const& operator=(Const&& other) noexcept {
                if (this != &other) {
                    reader_ = other.reader_;
                    orphaned_msg_builder_ = std::move(other.orphaned_msg_builder_);
                    message_lifetime_ = std::move(other.message_lifetime_);
                }
                return *this;
            }

            Const(const Const& other) = delete;
            Const& operator=(const Const& other) = delete;

            operator schema::rpp_common::Wrench2D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Wrench2D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Wrench2D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Wrench2D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Wrench2D>;

            inline ::rpp_schema::rpp_common::Point2D::Const force() const { return ::rpp_schema::rpp_common::Point2D::Const(reader_.getForce(), message_lifetime_); }


            inline double torque() const { return reader_.getTorque(); }


            Wrench2D_Native as_struct() const {

                return Wrench2D_Native{
                    ::rpp_schema::rpp_common::Point2D::Const(reader_.getForce()).as_struct(),
                    reader_.getTorque()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Wrench2D::Builder builder_;

    public:
        using List = rpp::List<Wrench2D>;

        struct torque_Proxy {
            private:
                schema::rpp_common::Wrench2D::Builder& builder_;
            public:
                torque_Proxy(schema::rpp_common::Wrench2D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getTorque(); }
                torque_Proxy& operator=(double value) {
                    builder_.setTorque(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Wrench2D;
        Wrench2D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Wrench2D>()) {}
        Wrench2D(schema::rpp_common::Wrench2D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Wrench2D() = default;

        // Move constructor and move assignment operator
        Wrench2D(Wrench2D&&) = default;
        Wrench2D& operator=(Wrench2D&&) = default;
        // Delete copy constructor and copy assignment operator
        Wrench2D(const Wrench2D&) = delete;
        Wrench2D& operator=(const Wrench2D&) = delete;

        ::rpp_schema::rpp_common::Point2D force() { return ::rpp_schema::rpp_common::Point2D(builder_.getForce()); }
        ::rpp_schema::rpp_common::Point2D::Const force() const { return ::rpp_schema::rpp_common::Point2D::Const(builder_.asReader().getForce()); }

        torque_Proxy torque() { return torque_Proxy{builder_}; }
        double torque() const { return builder_.asReader().getTorque(); }

        Wrench2D_Native as_struct() const {

            return Wrench2D_Native{
                ::rpp_schema::rpp_common::Point2D::Const(builder_.asReader().getForce()).as_struct(),
                builder_.asReader().getTorque()
            };
        }

        Wrench2D::Const as_const() const {
            return Wrench2D::Const(builder_.asReader());
        }

};

inline Wrench2D::Const::Const(const Wrench2D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Wrench2D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
