#pragma once
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_testing/test_plugin_types.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>



namespace rpp_schema::rpp_testing{


struct TestStruct1_Native {

    double x;
    double y;
    double theta;
};


class TestStruct1 {
public:


    class Const {

        private:
            schema::rpp_testing::TestStruct1::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_testing::TestStruct1::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const TestStruct1& main_wrapper);
            Const(TestStruct1&& main_wrapper)
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

            operator schema::rpp_testing::TestStruct1::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_testing::TestStruct1::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_testing::TestStruct1::Reader copied_reader =
                    message->getRoot<schema::rpp_testing::TestStruct1>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<TestStruct1>;

            inline double x() const { return reader_.getX(); }


            inline double y() const { return reader_.getY(); }


            inline double theta() const { return reader_.getTheta(); }


            TestStruct1_Native as_struct() const {

                return TestStruct1_Native{
                    reader_.getX(),
                    reader_.getY(),
                    reader_.getTheta()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_testing::TestStruct1::Builder builder_;

    public:
        using List = rpp::List<TestStruct1>;

        struct x_Proxy {
            private:
                schema::rpp_testing::TestStruct1::Builder& builder_;
            public:
                x_Proxy(schema::rpp_testing::TestStruct1::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getX(); }
                x_Proxy& operator=(double value) {
                    builder_.setX(value);
                    return *this;
                }
        };

        struct y_Proxy {
            private:
                schema::rpp_testing::TestStruct1::Builder& builder_;
            public:
                y_Proxy(schema::rpp_testing::TestStruct1::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getY(); }
                y_Proxy& operator=(double value) {
                    builder_.setY(value);
                    return *this;
                }
        };

        struct theta_Proxy {
            private:
                schema::rpp_testing::TestStruct1::Builder& builder_;
            public:
                theta_Proxy(schema::rpp_testing::TestStruct1::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getTheta(); }
                theta_Proxy& operator=(double value) {
                    builder_.setTheta(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_testing::TestStruct1;
        TestStruct1()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_testing::TestStruct1>()) {}
        TestStruct1(schema::rpp_testing::TestStruct1::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~TestStruct1() = default;

        // Move constructor and move assignment operator
        TestStruct1(TestStruct1&&) = default;
        TestStruct1& operator=(TestStruct1&&) = default;
        // Delete copy constructor and copy assignment operator
        TestStruct1(const TestStruct1&) = delete;
        TestStruct1& operator=(const TestStruct1&) = delete;

        x_Proxy x() { return x_Proxy{builder_}; }
        double x() const { return builder_.asReader().getX(); }

        y_Proxy y() { return y_Proxy{builder_}; }
        double y() const { return builder_.asReader().getY(); }

        theta_Proxy theta() { return theta_Proxy{builder_}; }
        double theta() const { return builder_.asReader().getTheta(); }

        TestStruct1_Native as_struct() const {

            return TestStruct1_Native{
                builder_.asReader().getX(),
                builder_.asReader().getY(),
                builder_.asReader().getTheta()
            };
        }

        TestStruct1::Const as_const() const {
            return TestStruct1::Const(builder_.asReader());
        }

};

inline TestStruct1::Const::Const(const TestStruct1& main_wrapper)
    : reader_(const_cast<schema::rpp_testing::TestStruct1::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_testing
