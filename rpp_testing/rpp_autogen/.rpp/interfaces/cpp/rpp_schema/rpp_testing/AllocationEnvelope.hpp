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

#include "rpp_schema/rpp_testing/AllocationFixedSample.hpp"

namespace rpp_schema::rpp_testing{


struct AllocationEnvelope_Native {

    std::string name;
    std::vector<uint8_t> payload;
    std::vector<double> values;
    ::rpp_schema::rpp_testing::AllocationFixedSample_Native child;
    std::vector<::rpp_schema::rpp_testing::AllocationFixedSample_Native> history;

    static constexpr const char* struct_name() noexcept { return "AllocationEnvelope"; }
    template<typename Visitor>
    void reflect(Visitor&& visitor) {
        visitor("name", name);
        visitor("payload", payload);
        visitor("values", values);
        visitor("child", child);
        visitor("history", history);
    }
};


class AllocationEnvelope {
public:


    class Const {

        private:
            schema::rpp_testing::AllocationEnvelope::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_testing::AllocationEnvelope::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const AllocationEnvelope& main_wrapper);
            Const(AllocationEnvelope&& main_wrapper)
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

            operator schema::rpp_testing::AllocationEnvelope::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_testing::AllocationEnvelope::Reader reader) {
                // The reader can include child data and fields from newer schemas.
                const auto words = rpp::message_segment_words(reader.totalSize().wordCount);
                auto message = std::make_unique<capnp::MallocMessageBuilder>(words);
                message->setRoot(reader);
                schema::rpp_testing::AllocationEnvelope::Reader copied_reader =
                    message->getRoot<schema::rpp_testing::AllocationEnvelope>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<AllocationEnvelope>;

            inline std::string name() const { return reader_.getName().cStr(); }


            inline rpp::DataConst payload() const {
                return rpp::DataConst(reader_.getPayload(), message_lifetime_);
            }


            inline rpp::ListConst<double> values() const { return rpp::ListConst<double>{reader_.getValues(), message_lifetime_}; }


            inline ::rpp_schema::rpp_testing::AllocationFixedSample::Const child() const { return ::rpp_schema::rpp_testing::AllocationFixedSample::Const(reader_.getChild(), message_lifetime_); }


            inline ::rpp_schema::rpp_testing::AllocationFixedSample::Const::List history() const { return ::rpp_schema::rpp_testing::AllocationFixedSample::Const::List{reader_.getHistory(), message_lifetime_}; }


            AllocationEnvelope_Native as_struct() const {

                std::vector<double> values_vec;
                auto capnp_values = reader_.getValues();
                values_vec.reserve(capnp_values.size());
                for (size_t i = 0; i < capnp_values.size(); ++i) {
                    values_vec.push_back(capnp_values[i]);
                }


                std::vector<::rpp_schema::rpp_testing::AllocationFixedSample_Native> history_vec;
                auto capnp_history = reader_.getHistory();
                history_vec.reserve(capnp_history.size());
                for (size_t i = 0; i < capnp_history.size(); ++i) {
                    history_vec.push_back(::rpp_schema::rpp_testing::AllocationFixedSample::Const(capnp_history[i]).as_struct());
                }


                return AllocationEnvelope_Native{
                    reader_.getName(),

                    std::vector<uint8_t>(reader_.getPayload().begin(), reader_.getPayload().end()),

                                    std::move(values_vec),
                    ::rpp_schema::rpp_testing::AllocationFixedSample::Const(reader_.getChild()).as_struct(),
                    std::move(history_vec)
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_testing::AllocationEnvelope::Builder builder_;

    public:
        using List = rpp::List<AllocationEnvelope>;

        struct name_Proxy {
            private:
                schema::rpp_testing::AllocationEnvelope::Builder& builder_;
            public:
                name_Proxy(schema::rpp_testing::AllocationEnvelope::Builder& builder) : builder_(builder) {}
                operator std::string() const { return builder_.getName().cStr(); }
                name_Proxy& operator=(std::string value) {
                    builder_.setName(value);
                    return *this;
                }
        };

        struct payload_Proxy {
            private:
                schema::rpp_testing::AllocationEnvelope::Builder& builder_;
            public:
                payload_Proxy(schema::rpp_testing::AllocationEnvelope::Builder& builder) : builder_(builder) {}
                operator rpp::Data() const { return builder_.getPayload(); }
                payload_Proxy& operator=(rpp::Data value) {
                    builder_.setPayload(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_testing::AllocationEnvelope;
        AllocationEnvelope() : AllocationEnvelope(0) {}
        // The hint includes the root pointer and any anticipated child storage.
        explicit AllocationEnvelope(std::uint64_t initial_segment_words)
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>(
                  rpp::message_segment_words(
                      default_content_words(), initial_segment_words))),
              builder_(msg_builder_->initRoot<schema::rpp_testing::AllocationEnvelope>()) {}
        AllocationEnvelope(schema::rpp_testing::AllocationEnvelope::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~AllocationEnvelope() = default;

        // Move constructor and move assignment operator
        AllocationEnvelope(AllocationEnvelope&&) = default;
        AllocationEnvelope& operator=(AllocationEnvelope&&) = default;
        // Delete copy constructor and copy assignment operator
        AllocationEnvelope(const AllocationEnvelope&) = delete;
        AllocationEnvelope& operator=(const AllocationEnvelope&) = delete;

    private:
        static std::uint64_t default_content_words() {
            return std::uint64_t{capnp::sizeInWords<CapnpType>()};
        }
    public:

        name_Proxy name() { return name_Proxy{builder_}; }
        std::string name() const { return builder_.asReader().getName(); }

        rpp::Data payload() {
            return rpp::Data{builder_.getPayload(),
                [builder = builder_](size_t new_size) mutable {
                    return builder.initPayload(new_size);
                }
            };
        }
        rpp::DataConst payload() const { return rpp::DataConst{builder_.asReader().getPayload()}; }

        rpp::List<double> values() { return rpp::List<double>{builder_.getValues(),
                [builder = builder_](size_t new_size) mutable {
                    return builder.initValues(new_size);
                }
            };
        }
        rpp::ListConst<double> values() const { return rpp::ListConst<double>{builder_.asReader().getValues()}; }

        ::rpp_schema::rpp_testing::AllocationFixedSample child() { return ::rpp_schema::rpp_testing::AllocationFixedSample(builder_.getChild()); }
        ::rpp_schema::rpp_testing::AllocationFixedSample::Const child() const { return ::rpp_schema::rpp_testing::AllocationFixedSample::Const(builder_.asReader().getChild()); }

        ::rpp_schema::rpp_testing::AllocationFixedSample::List history() { return ::rpp_schema::rpp_testing::AllocationFixedSample::List{builder_.getHistory(),
                [builder = builder_](size_t new_size) mutable {
                    return builder.initHistory(new_size);
                }
            };
        }
        ::rpp_schema::rpp_testing::AllocationFixedSample::Const::List history() const { return ::rpp_schema::rpp_testing::AllocationFixedSample::Const::List{builder_.asReader().getHistory()}; }

        AllocationEnvelope_Native as_struct() const {

            std::vector<double> values_vec;
            auto capnp_values = builder_.asReader().getValues();
            values_vec.reserve(capnp_values.size());
            for (size_t i = 0; i < capnp_values.size(); ++i) {
                values_vec.push_back(capnp_values[i]);
            }


            std::vector<::rpp_schema::rpp_testing::AllocationFixedSample_Native> history_vec;
            auto capnp_history = builder_.asReader().getHistory();
            history_vec.reserve(capnp_history.size());
            for (size_t i = 0; i < capnp_history.size(); ++i) {
                history_vec.push_back(::rpp_schema::rpp_testing::AllocationFixedSample::Const(capnp_history[i]).as_struct());
            }


            return AllocationEnvelope_Native{
                builder_.asReader().getName(),

                std::vector<uint8_t>(builder_.asReader().getPayload().begin(), builder_.asReader().getPayload().end()),

                                std::move(values_vec),
                ::rpp_schema::rpp_testing::AllocationFixedSample::Const(builder_.asReader().getChild()).as_struct(),
                std::move(history_vec)
            };
        }

        AllocationEnvelope::Const as_const() const {
            return AllocationEnvelope::Const(builder_.asReader());
        }

};

inline AllocationEnvelope::Const::Const(const AllocationEnvelope& main_wrapper)
    : reader_(const_cast<schema::rpp_testing::AllocationEnvelope::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_testing
