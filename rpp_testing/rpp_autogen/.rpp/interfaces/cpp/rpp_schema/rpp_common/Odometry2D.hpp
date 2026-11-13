#pragma once
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_common/msgs.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>

#include "rpp_schema/rpp_common/Pose2D.hpp"
#include "rpp_schema/rpp_common/Twist2D.hpp"

namespace rpp_schema::rpp_common{


struct Odometry2D_Native {

    ::rpp_schema::rpp_common::Pose2D_Native pose;
    ::rpp_schema::rpp_common::Twist2D_Native twist;
};


class Odometry2D {
public:


    class Const {

        private:
            schema::rpp_common::Odometry2D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Odometry2D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Odometry2D& main_wrapper);
            Const(Odometry2D&& main_wrapper)
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

            operator schema::rpp_common::Odometry2D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Odometry2D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Odometry2D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Odometry2D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Odometry2D>;

            inline ::rpp_schema::rpp_common::Pose2D::Const pose() const { return ::rpp_schema::rpp_common::Pose2D::Const(reader_.getPose(), message_lifetime_); }


            inline ::rpp_schema::rpp_common::Twist2D::Const twist() const { return ::rpp_schema::rpp_common::Twist2D::Const(reader_.getTwist(), message_lifetime_); }


            Odometry2D_Native as_struct() const {

                return Odometry2D_Native{
                    ::rpp_schema::rpp_common::Pose2D::Const(reader_.getPose()).as_struct(),
                    ::rpp_schema::rpp_common::Twist2D::Const(reader_.getTwist()).as_struct()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Odometry2D::Builder builder_;

    public:
        using List = rpp::List<Odometry2D>;

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Odometry2D;
        Odometry2D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Odometry2D>()) {}
        Odometry2D(schema::rpp_common::Odometry2D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Odometry2D() = default;

        // Move constructor and move assignment operator
        Odometry2D(Odometry2D&&) = default;
        Odometry2D& operator=(Odometry2D&&) = default;
        // Delete copy constructor and copy assignment operator
        Odometry2D(const Odometry2D&) = delete;
        Odometry2D& operator=(const Odometry2D&) = delete;

        ::rpp_schema::rpp_common::Pose2D pose() { return ::rpp_schema::rpp_common::Pose2D(builder_.getPose()); }
        ::rpp_schema::rpp_common::Pose2D::Const pose() const { return ::rpp_schema::rpp_common::Pose2D::Const(builder_.asReader().getPose()); }

        ::rpp_schema::rpp_common::Twist2D twist() { return ::rpp_schema::rpp_common::Twist2D(builder_.getTwist()); }
        ::rpp_schema::rpp_common::Twist2D::Const twist() const { return ::rpp_schema::rpp_common::Twist2D::Const(builder_.asReader().getTwist()); }

        Odometry2D_Native as_struct() const {

            return Odometry2D_Native{
                ::rpp_schema::rpp_common::Pose2D::Const(builder_.asReader().getPose()).as_struct(),
                ::rpp_schema::rpp_common::Twist2D::Const(builder_.asReader().getTwist()).as_struct()
            };
        }

        Odometry2D::Const as_const() const {
            return Odometry2D::Const(builder_.asReader());
        }

};

inline Odometry2D::Const::Const(const Odometry2D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Odometry2D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
