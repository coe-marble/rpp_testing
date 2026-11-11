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


struct Quaternion_Native {

    double x;
    double y;
    double z;
    double w;
};


class Quaternion {
public:


    class Const {

        private:
            schema::rpp_common::Quaternion::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
        public:
            Const(schema::rpp_common::Quaternion::Reader reader)
            : reader_(reader) {}
            virtual ~Const() = default;
            Const(const Quaternion& main_wrapper);
            Const(Quaternion&& main_wrapper)
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

            operator schema::rpp_common::Quaternion::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_);
            }
            static Const from_wire(schema::rpp_common::Quaternion::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Quaternion::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Quaternion>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Quaternion>;

            inline double x() const { return reader_.getX(); }


            inline double y() const { return reader_.getY(); }


            inline double z() const { return reader_.getZ(); }


            inline double w() const { return reader_.getW(); }


            Quaternion_Native as_struct() const {

                return Quaternion_Native{
                    reader_.getX(),
                    reader_.getY(),
                    reader_.getZ(),
                    reader_.getW()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Quaternion::Builder builder_;

    public:
        using List = rpp::List<Quaternion>;

        struct x_Proxy {
            private:
                schema::rpp_common::Quaternion::Builder& builder_;
            public:
                x_Proxy(schema::rpp_common::Quaternion::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getX(); }
                x_Proxy& operator=(double value) {
                    builder_.setX(value);
                    return *this;
                }
        };

        struct y_Proxy {
            private:
                schema::rpp_common::Quaternion::Builder& builder_;
            public:
                y_Proxy(schema::rpp_common::Quaternion::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getY(); }
                y_Proxy& operator=(double value) {
                    builder_.setY(value);
                    return *this;
                }
        };

        struct z_Proxy {
            private:
                schema::rpp_common::Quaternion::Builder& builder_;
            public:
                z_Proxy(schema::rpp_common::Quaternion::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getZ(); }
                z_Proxy& operator=(double value) {
                    builder_.setZ(value);
                    return *this;
                }
        };

        struct w_Proxy {
            private:
                schema::rpp_common::Quaternion::Builder& builder_;
            public:
                w_Proxy(schema::rpp_common::Quaternion::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getW(); }
                w_Proxy& operator=(double value) {
                    builder_.setW(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Quaternion;
        Quaternion()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Quaternion>()) {}
        Quaternion(schema::rpp_common::Quaternion::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Quaternion() = default;

        // Move constructor and move assignment operator
        Quaternion(Quaternion&&) = default;
        Quaternion& operator=(Quaternion&&) = default;
        // Delete copy constructor and copy assignment operator
        Quaternion(const Quaternion&) = delete;
        Quaternion& operator=(const Quaternion&) = delete;

        x_Proxy x() { return x_Proxy{builder_}; }
        double x() const { return builder_.asReader().getX(); }

        y_Proxy y() { return y_Proxy{builder_}; }
        double y() const { return builder_.asReader().getY(); }

        z_Proxy z() { return z_Proxy{builder_}; }
        double z() const { return builder_.asReader().getZ(); }

        w_Proxy w() { return w_Proxy{builder_}; }
        double w() const { return builder_.asReader().getW(); }

        Quaternion_Native as_struct() const {

            return Quaternion_Native{
                builder_.asReader().getX(),
                builder_.asReader().getY(),
                builder_.asReader().getZ(),
                builder_.asReader().getW()
            };
        }

        Quaternion::Const as_const() const {
            return Quaternion::Const(builder_.asReader());
        }

};

inline Quaternion::Const::Const(const Quaternion& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Quaternion::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
