#pragma once
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_common/msgs.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>



namespace rpp_schema::rpp_common{


struct Vector3D_Native {

    double x;
    double y;
    double z;
};


class Vector3D {
public:


    class Const {

        private:
            schema::rpp_common::Vector3D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Vector3D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Vector3D& main_wrapper);
            Const(Vector3D&& main_wrapper)
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

            operator schema::rpp_common::Vector3D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Vector3D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Vector3D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Vector3D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Vector3D>;

            inline double x() const { return reader_.getX(); }


            inline double y() const { return reader_.getY(); }


            inline double z() const { return reader_.getZ(); }


            Vector3D_Native as_struct() const {

                return Vector3D_Native{
                    reader_.getX(),
                    reader_.getY(),
                    reader_.getZ()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Vector3D::Builder builder_;

    public:
        using List = rpp::List<Vector3D>;

        struct x_Proxy {
            private:
                schema::rpp_common::Vector3D::Builder& builder_;
            public:
                x_Proxy(schema::rpp_common::Vector3D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getX(); }
                x_Proxy& operator=(double value) {
                    builder_.setX(value);
                    return *this;
                }
        };

        struct y_Proxy {
            private:
                schema::rpp_common::Vector3D::Builder& builder_;
            public:
                y_Proxy(schema::rpp_common::Vector3D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getY(); }
                y_Proxy& operator=(double value) {
                    builder_.setY(value);
                    return *this;
                }
        };

        struct z_Proxy {
            private:
                schema::rpp_common::Vector3D::Builder& builder_;
            public:
                z_Proxy(schema::rpp_common::Vector3D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getZ(); }
                z_Proxy& operator=(double value) {
                    builder_.setZ(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Vector3D;
        Vector3D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Vector3D>()) {}
        Vector3D(schema::rpp_common::Vector3D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Vector3D() = default;

        // Move constructor and move assignment operator
        Vector3D(Vector3D&&) = default;
        Vector3D& operator=(Vector3D&&) = default;
        // Delete copy constructor and copy assignment operator
        Vector3D(const Vector3D&) = delete;
        Vector3D& operator=(const Vector3D&) = delete;

        x_Proxy x() { return x_Proxy{builder_}; }
        double x() const { return builder_.asReader().getX(); }

        y_Proxy y() { return y_Proxy{builder_}; }
        double y() const { return builder_.asReader().getY(); }

        z_Proxy z() { return z_Proxy{builder_}; }
        double z() const { return builder_.asReader().getZ(); }

        Vector3D_Native as_struct() const {

            return Vector3D_Native{
                builder_.asReader().getX(),
                builder_.asReader().getY(),
                builder_.asReader().getZ()
            };
        }

        Vector3D::Const as_const() const {
            return Vector3D::Const(builder_.asReader());
        }

};

inline Vector3D::Const::Const(const Vector3D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Vector3D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
