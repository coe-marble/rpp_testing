#pragma once
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_testing/test_plugin_types.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>

#include "rpp_schema/rpp_testing/TestStruct1.hpp"

namespace rpp_schema::rpp_testing{


struct TestStruct2_Native {

    double linear;
    double angular;
    ::rpp_schema::rpp_testing::TestStruct1_Native struct1;
};


class TestStruct2 {
public:


    class Const {

        private:
            schema::rpp_testing::TestStruct2::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_testing::TestStruct2::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const TestStruct2& main_wrapper);
            Const(TestStruct2&& main_wrapper)
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

            operator schema::rpp_testing::TestStruct2::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_testing::TestStruct2::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_testing::TestStruct2::Reader copied_reader =
                    message->getRoot<schema::rpp_testing::TestStruct2>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<TestStruct2>;

            inline double linear() const { return reader_.getLinear(); }


            inline double angular() const { return reader_.getAngular(); }


            inline ::rpp_schema::rpp_testing::TestStruct1::Const struct1() const { return ::rpp_schema::rpp_testing::TestStruct1::Const(reader_.getStruct1(), message_lifetime_); }


            TestStruct2_Native as_struct() const {

                return TestStruct2_Native{
                    reader_.getLinear(),
                    reader_.getAngular(),
                    ::rpp_schema::rpp_testing::TestStruct1::Const(reader_.getStruct1()).as_struct()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_testing::TestStruct2::Builder builder_;

    public:
        using List = rpp::List<TestStruct2>;

        struct linear_Proxy {
            private:
                schema::rpp_testing::TestStruct2::Builder& builder_;
            public:
                linear_Proxy(schema::rpp_testing::TestStruct2::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getLinear(); }
                linear_Proxy& operator=(double value) {
                    builder_.setLinear(value);
                    return *this;
                }
        };

        struct angular_Proxy {
            private:
                schema::rpp_testing::TestStruct2::Builder& builder_;
            public:
                angular_Proxy(schema::rpp_testing::TestStruct2::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getAngular(); }
                angular_Proxy& operator=(double value) {
                    builder_.setAngular(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_testing::TestStruct2;
        TestStruct2()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_testing::TestStruct2>()) {}
        TestStruct2(schema::rpp_testing::TestStruct2::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~TestStruct2() = default;

        // Move constructor and move assignment operator
        TestStruct2(TestStruct2&&) = default;
        TestStruct2& operator=(TestStruct2&&) = default;
        // Delete copy constructor and copy assignment operator
        TestStruct2(const TestStruct2&) = delete;
        TestStruct2& operator=(const TestStruct2&) = delete;

        linear_Proxy linear() { return linear_Proxy{builder_}; }
        double linear() const { return builder_.asReader().getLinear(); }

        angular_Proxy angular() { return angular_Proxy{builder_}; }
        double angular() const { return builder_.asReader().getAngular(); }

        ::rpp_schema::rpp_testing::TestStruct1 struct1() { return ::rpp_schema::rpp_testing::TestStruct1(builder_.getStruct1()); }
        ::rpp_schema::rpp_testing::TestStruct1::Const struct1() const { return ::rpp_schema::rpp_testing::TestStruct1::Const(builder_.asReader().getStruct1()); }

        TestStruct2_Native as_struct() const {

            return TestStruct2_Native{
                builder_.asReader().getLinear(),
                builder_.asReader().getAngular(),
                ::rpp_schema::rpp_testing::TestStruct1::Const(builder_.asReader().getStruct1()).as_struct()
            };
        }

        TestStruct2::Const as_const() const {
            return TestStruct2::Const(builder_.asReader());
        }

};

inline TestStruct2::Const::Const(const TestStruct2& main_wrapper)
    : reader_(const_cast<schema::rpp_testing::TestStruct2::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_testing
