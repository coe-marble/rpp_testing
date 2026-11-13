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


struct Twist3D_Native {

    ::rpp_schema::rpp_common::Point3D_Native linear;
    ::rpp_schema::rpp_common::Point3D_Native angular;
};


class Twist3D {
public:


    class Const {

        private:
            schema::rpp_common::Twist3D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Twist3D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Twist3D& main_wrapper);
            Const(Twist3D&& main_wrapper)
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

            operator schema::rpp_common::Twist3D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Twist3D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Twist3D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Twist3D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Twist3D>;

            inline ::rpp_schema::rpp_common::Point3D::Const linear() const { return ::rpp_schema::rpp_common::Point3D::Const(reader_.getLinear(), message_lifetime_); }


            inline ::rpp_schema::rpp_common::Point3D::Const angular() const { return ::rpp_schema::rpp_common::Point3D::Const(reader_.getAngular(), message_lifetime_); }


            Twist3D_Native as_struct() const {

                return Twist3D_Native{
                    ::rpp_schema::rpp_common::Point3D::Const(reader_.getLinear()).as_struct(),
                    ::rpp_schema::rpp_common::Point3D::Const(reader_.getAngular()).as_struct()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Twist3D::Builder builder_;

    public:
        using List = rpp::List<Twist3D>;

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Twist3D;
        Twist3D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Twist3D>()) {}
        Twist3D(schema::rpp_common::Twist3D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Twist3D() = default;

        // Move constructor and move assignment operator
        Twist3D(Twist3D&&) = default;
        Twist3D& operator=(Twist3D&&) = default;
        // Delete copy constructor and copy assignment operator
        Twist3D(const Twist3D&) = delete;
        Twist3D& operator=(const Twist3D&) = delete;

        ::rpp_schema::rpp_common::Point3D linear() { return ::rpp_schema::rpp_common::Point3D(builder_.getLinear()); }
        ::rpp_schema::rpp_common::Point3D::Const linear() const { return ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getLinear()); }

        ::rpp_schema::rpp_common::Point3D angular() { return ::rpp_schema::rpp_common::Point3D(builder_.getAngular()); }
        ::rpp_schema::rpp_common::Point3D::Const angular() const { return ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getAngular()); }

        Twist3D_Native as_struct() const {

            return Twist3D_Native{
                ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getLinear()).as_struct(),
                ::rpp_schema::rpp_common::Point3D::Const(builder_.asReader().getAngular()).as_struct()
            };
        }

        Twist3D::Const as_const() const {
            return Twist3D::Const(builder_.asReader());
        }

};

inline Twist3D::Const::Const(const Twist3D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Twist3D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
