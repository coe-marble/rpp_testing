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


struct Twist2D_Native {

    ::rpp_schema::rpp_common::Point2D_Native linear;
    double angular;

    static constexpr const char* struct_name() noexcept { return "Twist2D"; }
    template<typename Visitor>
    void reflect(Visitor&& visitor) {
        visitor("linear", linear);
        visitor("angular", angular);
    }
};


class Twist2D {
public:


    class Const {

        private:
            schema::rpp_common::Twist2D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::Twist2D::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const Twist2D& main_wrapper);
            Const(Twist2D&& main_wrapper)
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

            operator schema::rpp_common::Twist2D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::Twist2D::Reader reader) {
                // The reader can include child data and fields from newer schemas.
                const auto words = rpp::message_segment_words(reader.totalSize().wordCount);
                auto message = std::make_unique<capnp::MallocMessageBuilder>(words);
                message->setRoot(reader);
                schema::rpp_common::Twist2D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Twist2D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Twist2D>;

            inline ::rpp_schema::rpp_common::Point2D::Const linear() const { return ::rpp_schema::rpp_common::Point2D::Const(reader_.getLinear(), message_lifetime_); }


            inline double angular() const { return reader_.getAngular(); }


            Twist2D_Native as_struct() const {

                return Twist2D_Native{
                    ::rpp_schema::rpp_common::Point2D::Const(reader_.getLinear()).as_struct(),
                    reader_.getAngular()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Twist2D::Builder builder_;

    public:
        using List = rpp::List<Twist2D>;

        struct angular_Proxy {
            private:
                schema::rpp_common::Twist2D::Builder& builder_;
            public:
                angular_Proxy(schema::rpp_common::Twist2D::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getAngular(); }
                angular_Proxy& operator=(double value) {
                    builder_.setAngular(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Twist2D;
        Twist2D() : Twist2D(0) {}
        // The hint includes the root pointer and any anticipated child storage.
        explicit Twist2D(std::uint64_t initial_segment_words)
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>(
                  rpp::message_segment_words(
                      default_content_words(), initial_segment_words))),
              builder_(msg_builder_->initRoot<schema::rpp_common::Twist2D>()) {}
        Twist2D(schema::rpp_common::Twist2D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Twist2D() = default;

        // Move constructor and move assignment operator
        Twist2D(Twist2D&&) = default;
        Twist2D& operator=(Twist2D&&) = default;
        // Delete copy constructor and copy assignment operator
        Twist2D(const Twist2D&) = delete;
        Twist2D& operator=(const Twist2D&) = delete;

    private:
        static std::uint64_t default_content_words() {
            return std::uint64_t{capnp::sizeInWords<CapnpType>()};
        }
    public:

        ::rpp_schema::rpp_common::Point2D linear() { return ::rpp_schema::rpp_common::Point2D(builder_.getLinear()); }
        ::rpp_schema::rpp_common::Point2D::Const linear() const { return ::rpp_schema::rpp_common::Point2D::Const(builder_.asReader().getLinear()); }

        angular_Proxy angular() { return angular_Proxy{builder_}; }
        double angular() const { return builder_.asReader().getAngular(); }

        Twist2D_Native as_struct() const {

            return Twist2D_Native{
                ::rpp_schema::rpp_common::Point2D::Const(builder_.asReader().getLinear()).as_struct(),
                builder_.asReader().getAngular()
            };
        }

        Twist2D::Const as_const() const {
            return Twist2D::Const(builder_.asReader());
        }

};

inline Twist2D::Const::Const(const Twist2D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Twist2D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
