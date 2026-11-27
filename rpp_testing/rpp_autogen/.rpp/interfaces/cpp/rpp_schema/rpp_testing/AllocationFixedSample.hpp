#pragma once
#include <rpp_cpp/list_definitions.hpp>
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_testing/test_plugin_types.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>



namespace rpp_schema::rpp_testing{


struct AllocationFixedSample_Native {

    double a;
    double b;
    double c;
    double d;
    double e;
    double f;

    static constexpr const char* struct_name() noexcept { return "AllocationFixedSample"; }
    template<typename Visitor>
    void reflect(Visitor&& visitor) {
        visitor("a", a);
        visitor("b", b);
        visitor("c", c);
        visitor("d", d);
        visitor("e", e);
        visitor("f", f);
    }
};


class AllocationFixedSample {
public:


    class Const {

        private:
            schema::rpp_testing::AllocationFixedSample::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_testing::AllocationFixedSample::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const AllocationFixedSample& main_wrapper);
            Const(AllocationFixedSample&& main_wrapper)
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

            operator schema::rpp_testing::AllocationFixedSample::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_testing::AllocationFixedSample::Reader reader) {
                // The reader can include child data and fields from newer schemas.
                const auto words = rpp::message_segment_words(reader.totalSize().wordCount);
                auto message = std::make_unique<capnp::MallocMessageBuilder>(words);
                message->setRoot(reader);
                schema::rpp_testing::AllocationFixedSample::Reader copied_reader =
                    message->getRoot<schema::rpp_testing::AllocationFixedSample>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<AllocationFixedSample>;

            inline double a() const { return reader_.getA(); }


            inline double b() const { return reader_.getB(); }


            inline double c() const { return reader_.getC(); }


            inline double d() const { return reader_.getD(); }


            inline double e() const { return reader_.getE(); }


            inline double f() const { return reader_.getF(); }


            AllocationFixedSample_Native as_struct() const {

                return AllocationFixedSample_Native{
                    reader_.getA(),
                    reader_.getB(),
                    reader_.getC(),
                    reader_.getD(),
                    reader_.getE(),
                    reader_.getF()
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_testing::AllocationFixedSample::Builder builder_;

    public:
        using List = rpp::List<AllocationFixedSample>;

        struct a_Proxy {
            private:
                schema::rpp_testing::AllocationFixedSample::Builder& builder_;
            public:
                a_Proxy(schema::rpp_testing::AllocationFixedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getA(); }
                a_Proxy& operator=(double value) {
                    builder_.setA(value);
                    return *this;
                }
        };

        struct b_Proxy {
            private:
                schema::rpp_testing::AllocationFixedSample::Builder& builder_;
            public:
                b_Proxy(schema::rpp_testing::AllocationFixedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getB(); }
                b_Proxy& operator=(double value) {
                    builder_.setB(value);
                    return *this;
                }
        };

        struct c_Proxy {
            private:
                schema::rpp_testing::AllocationFixedSample::Builder& builder_;
            public:
                c_Proxy(schema::rpp_testing::AllocationFixedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getC(); }
                c_Proxy& operator=(double value) {
                    builder_.setC(value);
                    return *this;
                }
        };

        struct d_Proxy {
            private:
                schema::rpp_testing::AllocationFixedSample::Builder& builder_;
            public:
                d_Proxy(schema::rpp_testing::AllocationFixedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getD(); }
                d_Proxy& operator=(double value) {
                    builder_.setD(value);
                    return *this;
                }
        };

        struct e_Proxy {
            private:
                schema::rpp_testing::AllocationFixedSample::Builder& builder_;
            public:
                e_Proxy(schema::rpp_testing::AllocationFixedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getE(); }
                e_Proxy& operator=(double value) {
                    builder_.setE(value);
                    return *this;
                }
        };

        struct f_Proxy {
            private:
                schema::rpp_testing::AllocationFixedSample::Builder& builder_;
            public:
                f_Proxy(schema::rpp_testing::AllocationFixedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getF(); }
                f_Proxy& operator=(double value) {
                    builder_.setF(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_testing::AllocationFixedSample;
        AllocationFixedSample() : AllocationFixedSample(0) {}
        // The hint includes the root pointer and any anticipated child storage.
        explicit AllocationFixedSample(std::uint64_t initial_segment_words)
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>(
                  rpp::message_segment_words(
                      default_content_words(), initial_segment_words))),
              builder_(msg_builder_->initRoot<schema::rpp_testing::AllocationFixedSample>()) {}
        AllocationFixedSample(schema::rpp_testing::AllocationFixedSample::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~AllocationFixedSample() = default;

        // Move constructor and move assignment operator
        AllocationFixedSample(AllocationFixedSample&&) = default;
        AllocationFixedSample& operator=(AllocationFixedSample&&) = default;
        // Delete copy constructor and copy assignment operator
        AllocationFixedSample(const AllocationFixedSample&) = delete;
        AllocationFixedSample& operator=(const AllocationFixedSample&) = delete;

    private:
        static std::uint64_t default_content_words() {
            return std::uint64_t{capnp::sizeInWords<CapnpType>()};
        }
    public:

        a_Proxy a() { return a_Proxy{builder_}; }
        double a() const { return builder_.asReader().getA(); }

        b_Proxy b() { return b_Proxy{builder_}; }
        double b() const { return builder_.asReader().getB(); }

        c_Proxy c() { return c_Proxy{builder_}; }
        double c() const { return builder_.asReader().getC(); }

        d_Proxy d() { return d_Proxy{builder_}; }
        double d() const { return builder_.asReader().getD(); }

        e_Proxy e() { return e_Proxy{builder_}; }
        double e() const { return builder_.asReader().getE(); }

        f_Proxy f() { return f_Proxy{builder_}; }
        double f() const { return builder_.asReader().getF(); }

        AllocationFixedSample_Native as_struct() const {

            return AllocationFixedSample_Native{
                builder_.asReader().getA(),
                builder_.asReader().getB(),
                builder_.asReader().getC(),
                builder_.asReader().getD(),
                builder_.asReader().getE(),
                builder_.asReader().getF()
            };
        }

        AllocationFixedSample::Const as_const() const {
            return AllocationFixedSample::Const(builder_.asReader());
        }

};

inline AllocationFixedSample::Const::Const(const AllocationFixedSample& main_wrapper)
    : reader_(const_cast<schema::rpp_testing::AllocationFixedSample::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_testing
