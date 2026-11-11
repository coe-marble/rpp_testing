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


struct Pose2D_Native {

    Point2D_Native position;
    double yaw;
};


class Pose2D {
public:


    class Const {

        private:
            schema::rpp_common::Pose2D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
        public:
            Const(schema::rpp_common::Pose2D::Reader reader)
            : reader_(reader) {}
            virtual ~Const() = default;
            Const(const Pose2D& main_wrapper);
            Const(Pose2D&& main_wrapper)
            : reader_(main_wrapper.builder_.asReader()),
              orphaned_msg_builder_(std::move(main_wrapper.msg_builder_)) {}

            Const(Const&& other) noexcept
            : reader_(other.reader_),
              orphaned_msg_builder_(std::move(other.orphaned_msg_builder_)) {}

            Const& operator=(Const&& other) noexcept {
                if (this != &other) {
                    reader_ = other.reader_;
                    orphaned_msg_builder_ = std::move(other.orphaned_msg_builder_);
                }
                return *this;
            }

            Const(const Const& other) = delete;
            Const& operator=(const Const& other) = delete;

            operator schema::rpp_common::Pose2D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_);
            }
            static Const from_wire(schema::rpp_common::Pose2D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Pose2D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Pose2D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Pose2D>;

            inline Point2D::Const position() const { return Point2D::Const(reader_.getPosition()); }


            inline double yaw() const { return reader_.getYaw(); }


            Pose2D_Native as_struct() const {

                return Pose2D_Native{
                    Point2D::Const(reader_.getPosition()).as_struct(),
                    reader_.getYaw()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Pose2D::Builder builder_;

    public:
        using List = rpp::List<Pose2D>;

        struct yaw_Proxy {
            private:
                schema::rpp_common::Pose2D::Builder& builder_;
            public:
                yaw_Proxy(schema::rpp_common::Pose2D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getYaw(); }
                yaw_Proxy& operator=(double value) {
                    builder_.setYaw(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Pose2D;
        Pose2D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Pose2D>()) {}
        Pose2D(schema::rpp_common::Pose2D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Pose2D() = default;

        // Move constructor and move assignment operator
        Pose2D(Pose2D&&) = default;
        Pose2D& operator=(Pose2D&&) = default;
        // Delete copy constructor and copy assignment operator
        Pose2D(const Pose2D&) = delete;
        Pose2D& operator=(const Pose2D&) = delete;

        Point2D position() { return Point2D(builder_.getPosition()); }
        Point2D::Const position() const { return Point2D::Const(builder_.asReader().getPosition()); }

        yaw_Proxy yaw() { return yaw_Proxy{builder_}; }
        double yaw() const { return builder_.asReader().getYaw(); }

        Pose2D_Native as_struct() const {

            return Pose2D_Native{
                Point2D::Const(builder_.asReader().getPosition()).as_struct(),
                builder_.asReader().getYaw()
            };
        }

        Pose2D::Const as_const() const {
            return Pose2D::Const(builder_.asReader());
        }

};

inline Pose2D::Const::Const(const Pose2D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Pose2D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
