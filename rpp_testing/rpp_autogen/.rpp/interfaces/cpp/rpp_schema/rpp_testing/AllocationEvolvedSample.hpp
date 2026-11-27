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


struct AllocationEvolvedSample_Native {

    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    std::string name;
    std::vector<double> values;

    static constexpr const char* struct_name() noexcept { return "AllocationEvolvedSample"; }
    template<typename Visitor>
    void reflect(Visitor&& visitor) {
        visitor("a", a);
        visitor("b", b);
        visitor("c", c);
        visitor("d", d);
        visitor("e", e);
        visitor("f", f);
        visitor("name", name);
        visitor("values", values);
    }
};


class AllocationEvolvedSample {
public:


    class Const {

        private:
            schema::rpp_testing::AllocationEvolvedSample::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_testing::AllocationEvolvedSample::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const AllocationEvolvedSample& main_wrapper);
            Const(AllocationEvolvedSample&& main_wrapper)
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

            operator schema::rpp_testing::AllocationEvolvedSample::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_testing::AllocationEvolvedSample::Reader reader) {
                // The reader can include child data and fields from newer schemas.
                const auto words = rpp::message_segment_words(reader.totalSize().wordCount);
                auto message = std::make_unique<capnp::MallocMessageBuilder>(words);
                message->setRoot(reader);
                schema::rpp_testing::AllocationEvolvedSample::Reader copied_reader =
                    message->getRoot<schema::rpp_testing::AllocationEvolvedSample>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<AllocationEvolvedSample>;

            inline double a() const { return reader_.getA(); }


            inline double b() const { return reader_.getB(); }


            inline double c() const { return reader_.getC(); }


            inline double d() const { return reader_.getD(); }


            inline double e() const { return reader_.getE(); }


            inline double f() const { return reader_.getF(); }


            inline std::string name() const { return reader_.getName().cStr(); }


            inline rpp::ListConst<double> values() const { return rpp::ListConst<double>{reader_.getValues(), message_lifetime_}; }


            AllocationEvolvedSample_Native as_struct() const {

                std::vector<double> values_vec;
                auto capnp_values = reader_.getValues();
                values_vec.reserve(capnp_values.size());
                for (size_t i = 0; i < capnp_values.size(); ++i) {
                    values_vec.push_back(capnp_values[i]);
                }


                return AllocationEvolvedSample_Native{
                    reader_.getA(),
                    reader_.getB(),
                    reader_.getC(),
                    reader_.getD(),
                    reader_.getE(),
                    reader_.getF(),
                    reader_.getName(),
                    std::move(values_vec)
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_testing::AllocationEvolvedSample::Builder builder_;

    public:
        using List = rpp::List<AllocationEvolvedSample>;

        struct a_Proxy {
            private:
                schema::rpp_testing::AllocationEvolvedSample::Builder& builder_;
            public:
                a_Proxy(schema::rpp_testing::AllocationEvolvedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getA(); }
                a_Proxy& operator=(double value) {
                    builder_.setA(value);
                    return *this;
                }
        };

        struct b_Proxy {
            private:
                schema::rpp_testing::AllocationEvolvedSample::Builder& builder_;
            public:
                b_Proxy(schema::rpp_testing::AllocationEvolvedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getB(); }
                b_Proxy& operator=(double value) {
                    builder_.setB(value);
                    return *this;
                }
        };

        struct c_Proxy {
            private:
                schema::rpp_testing::AllocationEvolvedSample::Builder& builder_;
            public:
                c_Proxy(schema::rpp_testing::AllocationEvolvedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getC(); }
                c_Proxy& operator=(double value) {
                    builder_.setC(value);
                    return *this;
                }
        };

        struct d_Proxy {
            private:
                schema::rpp_testing::AllocationEvolvedSample::Builder& builder_;
            public:
                d_Proxy(schema::rpp_testing::AllocationEvolvedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getD(); }
                d_Proxy& operator=(double value) {
                    builder_.setD(value);
                    return *this;
                }
        };

        struct e_Proxy {
            private:
                schema::rpp_testing::AllocationEvolvedSample::Builder& builder_;
            public:
                e_Proxy(schema::rpp_testing::AllocationEvolvedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getE(); }
                e_Proxy& operator=(double value) {
                    builder_.setE(value);
                    return *this;
                }
        };

        struct f_Proxy {
            private:
                schema::rpp_testing::AllocationEvolvedSample::Builder& builder_;
            public:
                f_Proxy(schema::rpp_testing::AllocationEvolvedSample::Builder& builder) : builder_(builder) {}
                operator double() const { return builder_.getF(); }
                f_Proxy& operator=(double value) {
                    builder_.setF(value);
                    return *this;
                }
        };

        struct name_Proxy {
            private:
                schema::rpp_testing::AllocationEvolvedSample::Builder& builder_;
            public:
                name_Proxy(schema::rpp_testing::AllocationEvolvedSample::Builder& builder) : builder_(builder) {}
                operator std::string() const { return builder_.getName().cStr(); }
                name_Proxy& operator=(std::string value) {
                    builder_.setName(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_testing::AllocationEvolvedSample;
        AllocationEvolvedSample() : AllocationEvolvedSample(0) {}
        // The hint includes the root pointer and any anticipated child storage.
        explicit AllocationEvolvedSample(std::uint64_t initial_segment_words)
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>(
                  rpp::message_segment_words(
                      default_content_words(), initial_segment_words))),
              builder_(msg_builder_->initRoot<schema::rpp_testing::AllocationEvolvedSample>()) {}
        AllocationEvolvedSample(schema::rpp_testing::AllocationEvolvedSample::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~AllocationEvolvedSample() = default;

        // Move constructor and move assignment operator
        AllocationEvolvedSample(AllocationEvolvedSample&&) = default;
        AllocationEvolvedSample& operator=(AllocationEvolvedSample&&) = default;
        // Delete copy constructor and copy assignment operator
        AllocationEvolvedSample(const AllocationEvolvedSample&) = delete;
        AllocationEvolvedSample& operator=(const AllocationEvolvedSample&) = delete;

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

        name_Proxy name() { return name_Proxy{builder_}; }
        std::string name() const { return builder_.asReader().getName(); }

        rpp::List<double> values() { return rpp::List<double>{builder_.getValues(),
                [builder = builder_](size_t new_size) mutable {
                    return builder.initValues(new_size);
                }
            };
        }
        rpp::ListConst<double> values() const { return rpp::ListConst<double>{builder_.asReader().getValues()}; }

        AllocationEvolvedSample_Native as_struct() const {

            std::vector<double> values_vec;
            auto capnp_values = builder_.asReader().getValues();
            values_vec.reserve(capnp_values.size());
            for (size_t i = 0; i < capnp_values.size(); ++i) {
                values_vec.push_back(capnp_values[i]);
            }


            return AllocationEvolvedSample_Native{
                builder_.asReader().getA(),
                builder_.asReader().getB(),
                builder_.asReader().getC(),
                builder_.asReader().getD(),
                builder_.asReader().getE(),
                builder_.asReader().getF(),
                builder_.asReader().getName(),
                std::move(values_vec)
            };
        }

        AllocationEvolvedSample::Const as_const() const {
            return AllocationEvolvedSample::Const(builder_.asReader());
        }

};

inline AllocationEvolvedSample::Const::Const(const AllocationEvolvedSample& main_wrapper)
    : reader_(const_cast<schema::rpp_testing::AllocationEvolvedSample::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_testing
