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
#include "rpp_schema/rpp_common/Quaternion.hpp"

namespace rpp_schema::rpp_common{


struct Pose3D_Native {

    ::rpp_schema::rpp_common::Point3D_Native position;
    ::rpp_schema::rpp_common::Quaternion_Native orientation;
};


class Pose3D {
public:


    class Const {

        private:
            schema::rpp_common::Pose3D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Pose3D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Pose3D& main_wrapper);
            Const(Pose3D&& main_wrapper)
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

            operator schema::rpp_common::Pose3D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Pose3D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Pose3D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Pose3D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Pose3D>;

            inline ::rpp_schema::rpp_common::Point3D::Const position() const { return ::rpp_schema::rpp_common::Point3D::Const(reader_.getPosition(), message_lifetime_); }


            inline ::rpp_schema::rpp_common::Quaternion::Const orientation() const { return ::rpp_schema::rpp_common::Quaternion::Const(reader_.getOrientation(), message_lifetime_); }


            Pose3D_Native as_struct() const {

                return Pose3D_Native{
                    ::rpp_schema::rpp_common::Point3D::Const(reader_.getPosition()).as_struct(),
                    ::rpp_schema::rpp_common::Quaternion::Const(reader_.getOrientation()).as_struct()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Pose3D::Builder builder_;

    public:
        using List = rpp::List<Pose3D>;

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Pose3D;
        Pose3D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Pose3D>()) {}
        Pose3D(schema::rpp_common::Pose3D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Pose3D() = default;

        // Move constructor and move assignment operator
        Pose3D(Pose3D&&) = default;
        Pose3D& operator=(Pose3D&&) = default;
        // Delete copy constructor and copy assignment operator
        Pose3D(const Pose3D&) = delete;
        Pose3D& operator=(const Pose3D&) = delete;

        ::rpp_schema::rpp_common::Point3D position() { return ::rpp_schema::rpp_common::Point3D(builder_.getPosition()); }
        ::rpp_schema::rpp_common::Point3D::Const position() const { return ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getPosition()); }

        ::rpp_schema::rpp_common::Quaternion orientation() { return ::rpp_schema::rpp_common::Quaternion(builder_.getOrientation()); }
        ::rpp_schema::rpp_common::Quaternion::Const orientation() const { return ::rpp_schema::rpp_common::Quaternion::Const(builder_.asReader().getOrientation()); }

        Pose3D_Native as_struct() const {

            return Pose3D_Native{
                ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getPosition()).as_struct(),
                ::rpp_schema::rpp_common::Quaternion::Const(builder_.asReader().getOrientation()).as_struct()
            };
        }

        Pose3D::Const as_const() const {
            return Pose3D::Const(builder_.asReader());
        }

};

inline Pose3D::Const::Const(const Pose3D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Pose3D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
