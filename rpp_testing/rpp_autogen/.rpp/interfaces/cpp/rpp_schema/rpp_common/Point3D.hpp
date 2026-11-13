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


struct Point3D_Native {

    double x;
    double y;
    double z;
};


class Point3D {
public:


    class Const {

        private:
            schema::rpp_common::Point3D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Point3D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Point3D& main_wrapper);
            Const(Point3D&& main_wrapper)
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

            operator schema::rpp_common::Point3D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Point3D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Point3D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Point3D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Point3D>;

            inline double x() const { return reader_.getX(); }


            inline double y() const { return reader_.getY(); }


            inline double z() const { return reader_.getZ(); }


            Point3D_Native as_struct() const {

                return Point3D_Native{
                    reader_.getX(),
                    reader_.getY(),
                    reader_.getZ()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Point3D::Builder builder_;

    public:
        using List = rpp::List<Point3D>;

        struct x_Proxy {
            private:
                schema::rpp_common::Point3D::Builder& builder_;
            public:
                x_Proxy(schema::rpp_common::Point3D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getX(); }
                x_Proxy& operator=(double value) {
                    builder_.setX(value);
                    return *this;
                }
        };

        struct y_Proxy {
            private:
                schema::rpp_common::Point3D::Builder& builder_;
            public:
                y_Proxy(schema::rpp_common::Point3D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getY(); }
                y_Proxy& operator=(double value) {
                    builder_.setY(value);
                    return *this;
                }
        };

        struct z_Proxy {
            private:
                schema::rpp_common::Point3D::Builder& builder_;
            public:
                z_Proxy(schema::rpp_common::Point3D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getZ(); }
                z_Proxy& operator=(double value) {
                    builder_.setZ(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Point3D;
        Point3D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Point3D>()) {}
        Point3D(schema::rpp_common::Point3D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Point3D() = default;

        // Move constructor and move assignment operator
        Point3D(Point3D&&) = default;
        Point3D& operator=(Point3D&&) = default;
        // Delete copy constructor and copy assignment operator
        Point3D(const Point3D&) = delete;
        Point3D& operator=(const Point3D&) = delete;

        x_Proxy x() { return x_Proxy{builder_}; }
        double x() const { return builder_.asReader().getX(); }

        y_Proxy y() { return y_Proxy{builder_}; }
        double y() const { return builder_.asReader().getY(); }

        z_Proxy z() { return z_Proxy{builder_}; }
        double z() const { return builder_.asReader().getZ(); }

        Point3D_Native as_struct() const {

            return Point3D_Native{
                builder_.asReader().getX(),
                builder_.asReader().getY(),
                builder_.asReader().getZ()
            };
        }

        Point3D::Const as_const() const {
            return Point3D::Const(builder_.asReader());
        }

};

inline Point3D::Const::Const(const Point3D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Point3D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
