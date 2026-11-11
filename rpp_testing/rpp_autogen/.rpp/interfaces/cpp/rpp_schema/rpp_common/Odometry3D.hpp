#pragma once
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_common/msgs.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>

#include "rpp_schema/rpp_common/Pose3D.hpp"
#include "rpp_schema/rpp_common/Twist3D.hpp"

namespace rpp_schema::rpp_common{


struct Odometry3D_Native {

    Pose3D_Native pose;
    Twist3D_Native twist;
};


class Odometry3D {
public:


    class Const {

        private:
            schema::rpp_common::Odometry3D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
        public:
            Const(schema::rpp_common::Odometry3D::Reader reader)
            : reader_(reader) {}
            virtual ~Const() = default;
            Const(const Odometry3D& main_wrapper);
            Const(Odometry3D&& main_wrapper)
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

            operator schema::rpp_common::Odometry3D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_);
            }
            static Const from_wire(schema::rpp_common::Odometry3D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Odometry3D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Odometry3D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Odometry3D>;

            inline Pose3D::Const pose() const { return Pose3D::Const(reader_.getPose()); }


            inline Twist3D::Const twist() const { return Twist3D::Const(reader_.getTwist()); }


            Odometry3D_Native as_struct() const {

                return Odometry3D_Native{
                    Pose3D::Const(reader_.getPose()).as_struct(),
                    Twist3D::Const(reader_.getTwist()).as_struct()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Odometry3D::Builder builder_;

    public:
        using List = rpp::List<Odometry3D>;

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Odometry3D;
        Odometry3D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Odometry3D>()) {}
        Odometry3D(schema::rpp_common::Odometry3D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Odometry3D() = default;

        // Move constructor and move assignment operator
        Odometry3D(Odometry3D&&) = default;
        Odometry3D& operator=(Odometry3D&&) = default;
        // Delete copy constructor and copy assignment operator
        Odometry3D(const Odometry3D&) = delete;
        Odometry3D& operator=(const Odometry3D&) = delete;

        Pose3D pose() { return Pose3D(builder_.getPose()); }
        Pose3D::Const pose() const { return Pose3D::Const(builder_.asReader().getPose()); }

        Twist3D twist() { return Twist3D(builder_.getTwist()); }
        Twist3D::Const twist() const { return Twist3D::Const(builder_.asReader().getTwist()); }

        Odometry3D_Native as_struct() const {

            return Odometry3D_Native{
                Pose3D::Const(builder_.asReader().getPose()).as_struct(),
                Twist3D::Const(builder_.asReader().getTwist()).as_struct()
            };
        }

        Odometry3D::Const as_const() const {
            return Odometry3D::Const(builder_.asReader());
        }

};

inline Odometry3D::Const::Const(const Odometry3D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Odometry3D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
