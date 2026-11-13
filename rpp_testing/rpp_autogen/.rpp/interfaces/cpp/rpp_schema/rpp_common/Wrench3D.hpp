#pragma once
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_common/msgs.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>

#include "rpp_schema/rpp_common/Point3D.hpp"

namespace rpp_schema::rpp_common{


struct Wrench3D_Native {

    ::rpp_schema::rpp_common::Point3D_Native force;
    ::rpp_schema::rpp_common::Point3D_Native torque;
};


class Wrench3D {
public:


    class Const {

        private:
            schema::rpp_common::Wrench3D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Wrench3D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Wrench3D& main_wrapper);
            Const(Wrench3D&& main_wrapper)
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

            operator schema::rpp_common::Wrench3D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Wrench3D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Wrench3D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Wrench3D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Wrench3D>;

            inline ::rpp_schema::rpp_common::Point3D::Const force() const { return ::rpp_schema::rpp_common::Point3D::Const(reader_.getForce(), message_lifetime_); }


            inline ::rpp_schema::rpp_common::Point3D::Const torque() const { return ::rpp_schema::rpp_common::Point3D::Const(reader_.getTorque(), message_lifetime_); }


            Wrench3D_Native as_struct() const {

                return Wrench3D_Native{
                    ::rpp_schema::rpp_common::Point3D::Const(reader_.getForce()).as_struct(),
                    ::rpp_schema::rpp_common::Point3D::Const(reader_.getTorque()).as_struct()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Wrench3D::Builder builder_;

    public:
        using List = rpp::List<Wrench3D>;

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Wrench3D;
        Wrench3D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Wrench3D>()) {}
        Wrench3D(schema::rpp_common::Wrench3D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Wrench3D() = default;

        // Move constructor and move assignment operator
        Wrench3D(Wrench3D&&) = default;
        Wrench3D& operator=(Wrench3D&&) = default;
        // Delete copy constructor and copy assignment operator
        Wrench3D(const Wrench3D&) = delete;
        Wrench3D& operator=(const Wrench3D&) = delete;

        ::rpp_schema::rpp_common::Point3D force() { return ::rpp_schema::rpp_common::Point3D(builder_.getForce()); }
        ::rpp_schema::rpp_common::Point3D::Const force() const { return ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getForce()); }

        ::rpp_schema::rpp_common::Point3D torque() { return ::rpp_schema::rpp_common::Point3D(builder_.getTorque()); }
        ::rpp_schema::rpp_common::Point3D::Const torque() const { return ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getTorque()); }

        Wrench3D_Native as_struct() const {

            return Wrench3D_Native{
                ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getForce()).as_struct(),
                ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getTorque()).as_struct()
            };
        }

        Wrench3D::Const as_const() const {
            return Wrench3D::Const(builder_.asReader());
        }

};

inline Wrench3D::Const::Const(const Wrench3D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Wrench3D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
