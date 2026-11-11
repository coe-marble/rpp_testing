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


struct VectorSpatial_Native {

    double x;
    double y;
    double z;
    double roll;
    double pitch;
    double yaw;
};


class VectorSpatial {
public:


    class Const {

        private:
            schema::rpp_common::VectorSpatial::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
        public:
            Const(schema::rpp_common::VectorSpatial::Reader reader)
            : reader_(reader) {}
            virtual ~Const() = default;
            Const(const VectorSpatial& main_wrapper);
            Const(VectorSpatial&& main_wrapper)
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

            operator schema::rpp_common::VectorSpatial::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_);
            }
            static Const from_wire(schema::rpp_common::VectorSpatial::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::VectorSpatial::Reader copied_reader =
                    message->getRoot<schema::rpp_common::VectorSpatial>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<VectorSpatial>;

            inline double x() const { return reader_.getX(); }


            inline double y() const { return reader_.getY(); }


            inline double z() const { return reader_.getZ(); }


            inline double roll() const { return reader_.getRoll(); }


            inline double pitch() const { return reader_.getPitch(); }


            inline double yaw() const { return reader_.getYaw(); }


            VectorSpatial_Native as_struct() const {

                return VectorSpatial_Native{
                    reader_.getX(),
                    reader_.getY(),
                    reader_.getZ(),
                    reader_.getRoll(),
                    reader_.getPitch(),
                    reader_.getYaw()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::VectorSpatial::Builder builder_;

    public:
        using List = rpp::List<VectorSpatial>;

        struct x_Proxy {
            private:
                schema::rpp_common::VectorSpatial::Builder& builder_;
            public:
                x_Proxy(schema::rpp_common::VectorSpatial::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getX(); }
                x_Proxy& operator=(double value) {
                    builder_.setX(value);
                    return *this;
                }
        };

        struct y_Proxy {
            private:
                schema::rpp_common::VectorSpatial::Builder& builder_;
            public:
                y_Proxy(schema::rpp_common::VectorSpatial::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getY(); }
                y_Proxy& operator=(double value) {
                    builder_.setY(value);
                    return *this;
                }
        };

        struct z_Proxy {
            private:
                schema::rpp_common::VectorSpatial::Builder& builder_;
            public:
                z_Proxy(schema::rpp_common::VectorSpatial::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getZ(); }
                z_Proxy& operator=(double value) {
                    builder_.setZ(value);
                    return *this;
                }
        };

        struct roll_Proxy {
            private:
                schema::rpp_common::VectorSpatial::Builder& builder_;
            public:
                roll_Proxy(schema::rpp_common::VectorSpatial::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getRoll(); }
                roll_Proxy& operator=(double value) {
                    builder_.setRoll(value);
                    return *this;
                }
        };

        struct pitch_Proxy {
            private:
                schema::rpp_common::VectorSpatial::Builder& builder_;
            public:
                pitch_Proxy(schema::rpp_common::VectorSpatial::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getPitch(); }
                pitch_Proxy& operator=(double value) {
                    builder_.setPitch(value);
                    return *this;
                }
        };

        struct yaw_Proxy {
            private:
                schema::rpp_common::VectorSpatial::Builder& builder_;
            public:
                yaw_Proxy(schema::rpp_common::VectorSpatial::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getYaw(); }
                yaw_Proxy& operator=(double value) {
                    builder_.setYaw(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::VectorSpatial;
        VectorSpatial()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::VectorSpatial>()) {}
        VectorSpatial(schema::rpp_common::VectorSpatial::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~VectorSpatial() = default;

        // Move constructor and move assignment operator
        VectorSpatial(VectorSpatial&&) = default;
        VectorSpatial& operator=(VectorSpatial&&) = default;
        // Delete copy constructor and copy assignment operator
        VectorSpatial(const VectorSpatial&) = delete;
        VectorSpatial& operator=(const VectorSpatial&) = delete;

        x_Proxy x() { return x_Proxy{builder_}; }
        double x() const { return builder_.asReader().getX(); }

        y_Proxy y() { return y_Proxy{builder_}; }
        double y() const { return builder_.asReader().getY(); }

        z_Proxy z() { return z_Proxy{builder_}; }
        double z() const { return builder_.asReader().getZ(); }

        roll_Proxy roll() { return roll_Proxy{builder_}; }
        double roll() const { return builder_.asReader().getRoll(); }

        pitch_Proxy pitch() { return pitch_Proxy{builder_}; }
        double pitch() const { return builder_.asReader().getPitch(); }

        yaw_Proxy yaw() { return yaw_Proxy{builder_}; }
        double yaw() const { return builder_.asReader().getYaw(); }

        VectorSpatial_Native as_struct() const {

            return VectorSpatial_Native{
                builder_.asReader().getX(),
                builder_.asReader().getY(),
                builder_.asReader().getZ(),
                builder_.asReader().getRoll(),
                builder_.asReader().getPitch(),
                builder_.asReader().getYaw()
            };
        }

        VectorSpatial::Const as_const() const {
            return VectorSpatial::Const(builder_.asReader());
        }

};

inline VectorSpatial::Const::Const(const VectorSpatial& main_wrapper)
    : reader_(const_cast<schema::rpp_common::VectorSpatial::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
