#pragma once
#include <rpp_cpp/list_definitions.hpp>
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_common/msgs.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>



namespace rpp_schema::rpp_common{


struct VectorPlanar_Native {

    double x;
    double y;
    double yaw;

    static constexpr const char* struct_name() noexcept { return "VectorPlanar"; }
    template<typename Visitor>
    void reflect(Visitor&& visitor) {
        visitor("x", x);
        visitor("y", y);
        visitor("yaw", yaw);
    }
};


class VectorPlanar {
public:


    class Const {

        private:
            schema::rpp_common::VectorPlanar::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::VectorPlanar::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const VectorPlanar& main_wrapper);
            Const(VectorPlanar&& main_wrapper)
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

            operator schema::rpp_common::VectorPlanar::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::VectorPlanar::Reader reader) {
                // The reader can include child data and fields from newer schemas.
                const auto words = rpp::message_segment_words(reader.totalSize().wordCount);
                auto message = std::make_unique<capnp::MallocMessageBuilder>(words);
                message->setRoot(reader);
                schema::rpp_common::VectorPlanar::Reader copied_reader =
                    message->getRoot<schema::rpp_common::VectorPlanar>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<VectorPlanar>;

            inline double x() const { return reader_.getX(); }


            inline double y() const { return reader_.getY(); }


            inline double yaw() const { return reader_.getYaw(); }


            VectorPlanar_Native as_struct() const {

                return VectorPlanar_Native{
                    reader_.getX(),
                    reader_.getY(),
                    reader_.getYaw()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::VectorPlanar::Builder builder_;

    public:
        using List = rpp::List<VectorPlanar>;

        struct x_Proxy {
            private:
                schema::rpp_common::VectorPlanar::Builder& builder_;
            public:
                x_Proxy(schema::rpp_common::VectorPlanar::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getX(); }
                x_Proxy& operator=(double value) {
                    builder_.setX(value);
                    return *this;
                }
        };

        struct y_Proxy {
            private:
                schema::rpp_common::VectorPlanar::Builder& builder_;
            public:
                y_Proxy(schema::rpp_common::VectorPlanar::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getY(); }
                y_Proxy& operator=(double value) {
                    builder_.setY(value);
                    return *this;
                }
        };

        struct yaw_Proxy {
            private:
                schema::rpp_common::VectorPlanar::Builder& builder_;
            public:
                yaw_Proxy(schema::rpp_common::VectorPlanar::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getYaw(); }
                yaw_Proxy& operator=(double value) {
                    builder_.setYaw(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::VectorPlanar;
        VectorPlanar() : VectorPlanar(0) {}
        // The hint includes the root pointer and any anticipated child storage.
        explicit VectorPlanar(std::uint64_t initial_segment_words)
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>(
                  rpp::message_segment_words(
                      default_content_words(), initial_segment_words))),
              builder_(msg_builder_->initRoot<schema::rpp_common::VectorPlanar>()) {}
        VectorPlanar(schema::rpp_common::VectorPlanar::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~VectorPlanar() = default;

        // Move constructor and move assignment operator
        VectorPlanar(VectorPlanar&&) = default;
        VectorPlanar& operator=(VectorPlanar&&) = default;
        // Delete copy constructor and copy assignment operator
        VectorPlanar(const VectorPlanar&) = delete;
        VectorPlanar& operator=(const VectorPlanar&) = delete;

    private:
        static std::uint64_t default_content_words() {
            return std::uint64_t{capnp::sizeInWords<CapnpType>()};
        }
    public:

        x_Proxy x() { return x_Proxy{builder_}; }
        double x() const { return builder_.asReader().getX(); }

        y_Proxy y() { return y_Proxy{builder_}; }
        double y() const { return builder_.asReader().getY(); }

        yaw_Proxy yaw() { return yaw_Proxy{builder_}; }
        double yaw() const { return builder_.asReader().getYaw(); }

        VectorPlanar_Native as_struct() const {

            return VectorPlanar_Native{
                builder_.asReader().getX(),
                builder_.asReader().getY(),
                builder_.asReader().getYaw()
            };
        }

        VectorPlanar::Const as_const() const {
            return VectorPlanar::Const(builder_.asReader());
        }

};

inline VectorPlanar::Const::Const(const VectorPlanar& main_wrapper)
    : reader_(const_cast<schema::rpp_common::VectorPlanar::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
