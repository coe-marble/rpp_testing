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

#include "rpp_schema/rpp_common/Point2D.hpp"

namespace rpp_schema::rpp_common{


struct Pose2D_Native {

    ::rpp_schema::rpp_common::Point2D_Native position;
    double yaw;

    static constexpr const char* struct_name() noexcept { return "Pose2D"; }
    template<typename Visitor>
    void reflect(Visitor&& visitor) {
        visitor("position", position);
        visitor("yaw", yaw);
    }
};


class Pose2D {
public:


    class Const {

        private:
            schema::rpp_common::Pose2D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Pose2D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Pose2D& main_wrapper);
            Const(Pose2D&& main_wrapper)
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

            operator schema::rpp_common::Pose2D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Pose2D::Reader reader) {
                // The reader can include child data and fields from newer schemas.
                const auto words = rpp::message_segment_words(reader.totalSize().wordCount);
                auto message = std::make_unique<capnp::MallocMessageBuilder>(words);
                message->setRoot(reader);
                schema::rpp_common::Pose2D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Pose2D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Pose2D>;

            inline ::rpp_schema::rpp_common::Point2D::Const position() const { return ::rpp_schema::rpp_common::Point2D::Const(reader_.getPosition(), message_lifetime_); }


            inline double yaw() const { return reader_.getYaw(); }


            Pose2D_Native as_struct() const {

                return Pose2D_Native{
                    ::rpp_schema::rpp_common::Point2D::Const(reader_.getPosition()).as_struct(),
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
        Pose2D() : Pose2D(0) {}
        // The hint includes the root pointer and any anticipated child storage.
        explicit Pose2D(std::uint64_t initial_segment_words)
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>(
                  rpp::message_segment_words(
                      default_content_words(), initial_segment_words))),
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

    private:
        static std::uint64_t default_content_words() {
            return std::uint64_t{capnp::sizeInWords<CapnpType>()};
        }
    public:

        ::rpp_schema::rpp_common::Point2D position() { return ::rpp_schema::rpp_common::Point2D(builder_.getPosition()); }
        ::rpp_schema::rpp_common::Point2D::Const position() const { return ::rpp_schema::rpp_common::Point2D::Const(builder_.asReader().getPosition()); }

        yaw_Proxy yaw() { return yaw_Proxy{builder_}; }
        double yaw() const { return builder_.asReader().getYaw(); }

        Pose2D_Native as_struct() const {

            return Pose2D_Native{
                ::rpp_schema::rpp_common::Point2D::Const(builder_.asReader().getPosition()).as_struct(),
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
