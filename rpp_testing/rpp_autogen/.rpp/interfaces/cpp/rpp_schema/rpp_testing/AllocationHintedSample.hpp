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


struct AllocationHintedSample_Native {

    std::vector<double> values;
    std::string name;
    std::vector<uint8_t> payload;
    std::vector<bool> flags;
    std::vector<::rpp_schema::rpp_testing::AllocationFixedSample_Native> history;

    static constexpr const char* struct_name() noexcept { return "AllocationHintedSample"; }
    template<typename Visitor>
    void reflect(Visitor&& visitor) {
        visitor("values", values);
        visitor("name", name);
        visitor("payload", payload);
        visitor("flags", flags);
        visitor("history", history);
    }
};


class AllocationHintedSample {
public:


    class Const {

        private:
            schema::rpp_testing::AllocationHintedSample::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_testing::AllocationHintedSample::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const AllocationHintedSample& main_wrapper);
            Const(AllocationHintedSample&& main_wrapper)
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

            operator schema::rpp_testing::AllocationHintedSample::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_testing::AllocationHintedSample::Reader reader) {
                // The reader can include child data and fields from newer schemas.
                const auto words = rpp::message_segment_words(reader.totalSize().wordCount);
                auto message = std::make_unique<capnp::MallocMessageBuilder>(words);
                message->setRoot(reader);
                schema::rpp_testing::AllocationHintedSample::Reader copied_reader =
                    message->getRoot<schema::rpp_testing::AllocationHintedSample>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<AllocationHintedSample>;

            inline rpp::ListConst<double> values() const { return rpp::ListConst<double>{reader_.getValues(), message_lifetime_}; }


            inline std::string name() const { return reader_.getName().cStr(); }


            inline rpp::DataConst payload() const {
                return rpp::DataConst(reader_.getPayload(), message_lifetime_);
            }


            inline rpp::ListConst<bool> flags() const { return rpp::ListConst<bool>{reader_.getFlags(), message_lifetime_}; }


            inline ::rpp_schema::rpp_testing::AllocationFixedSample::Const::List history() const { return ::rpp_schema::rpp_testing::AllocationFixedSample::Const::List{reader_.getHistory(), message_lifetime_}; }


            AllocationHintedSample_Native as_struct() const {

                std::vector<double> values_vec;
                auto capnp_values = reader_.getValues();
                values_vec.reserve(capnp_values.size());
                for (size_t i = 0; i < capnp_values.size(); ++i) {
                    values_vec.push_back(capnp_values[i]);
                }


                std::vector<bool> flags_vec;
                auto capnp_flags = reader_.getFlags();
                flags_vec.reserve(capnp_flags.size());
                for (size_t i = 0; i < capnp_flags.size(); ++i) {
                    flags_vec.push_back(capnp_flags[i]);
                }


                std::vector<::rpp_schema::rpp_testing::AllocationFixedSample_Native> history_vec;
                auto capnp_history = reader_.getHistory();
                history_vec.reserve(capnp_history.size());
                for (size_t i = 0; i < capnp_history.size(); ++i) {
                    history_vec.push_back(::rpp_schema::rpp_testing::AllocationFixedSample::Const(capnp_history[i]).as_struct());
                }


                return AllocationHintedSample_Native{
                    std::move(values_vec),
                    reader_.getName(),

                    std::vector<uint8_t>(reader_.getPayload().begin(), reader_.getPayload().end()),

                                    std::move(flags_vec),
                    std::move(history_vec)
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_testing::AllocationHintedSample::Builder builder_;

    public:
        using List = rpp::List<AllocationHintedSample>;

        struct name_Proxy {
            private:
                schema::rpp_testing::AllocationHintedSample::Builder& builder_;
            public:
                name_Proxy(schema::rpp_testing::AllocationHintedSample::Builder& builder) : builder_(builder) {}
                operator std::string() const { return builder_.getName().cStr(); }
                name_Proxy& operator=(std::string value) {
                    builder_.setName(value);
                    return *this;
                }
        };

        struct payload_Proxy {
            private:
                schema::rpp_testing::AllocationHintedSample::Builder& builder_;
            public:
                payload_Proxy(schema::rpp_testing::AllocationHintedSample::Builder& builder) : builder_(builder) {}
                operator rpp::Data() const { return builder_.getPayload(); }
                payload_Proxy& operator=(rpp::Data value) {
                    builder_.setPayload(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_testing::AllocationHintedSample;
        AllocationHintedSample() : AllocationHintedSample(0) {}
        // The hint includes the root pointer and any anticipated child storage.
        explicit AllocationHintedSample(std::uint64_t initial_segment_words)
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>(
                  rpp::message_segment_words(
                      default_content_words(), initial_segment_words))),
              builder_(msg_builder_->initRoot<schema::rpp_testing::AllocationHintedSample>()) {}
        AllocationHintedSample(schema::rpp_testing::AllocationHintedSample::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~AllocationHintedSample() = default;

        // Move constructor and move assignment operator
        AllocationHintedSample(AllocationHintedSample&&) = default;
        AllocationHintedSample& operator=(AllocationHintedSample&&) = default;
        // Delete copy constructor and copy assignment operator
        AllocationHintedSample(const AllocationHintedSample&) = delete;
        AllocationHintedSample& operator=(const AllocationHintedSample&) = delete;

    private:
        static std::uint64_t default_content_words() {
            return std::uint64_t{capnp::sizeInWords<CapnpType>()} + (rpp::list_message_segment_words<double>(6) - 1) + (rpp::list_message_segment_words<std::uint8_t>(16) - 1) + (rpp::list_message_segment_words<std::uint8_t>(9) - 1) + (rpp::list_message_segment_words<bool>(65) - 1) + (rpp::list_message_segment_words<::rpp_schema::rpp_testing::AllocationFixedSample::CapnpType>(2) - 1);
        }
    public:

        rpp::List<double> values() { return rpp::List<double>{builder_.getValues(),
                [builder = builder_](size_t new_size) mutable {
                    return builder.initValues(new_size);
                }
            };
        }
        rpp::ListConst<double> values() const { return rpp::ListConst<double>{builder_.asReader().getValues()}; }

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

        rpp::List<bool> flags() { return rpp::List<bool>{builder_.getFlags(),
                [builder = builder_](size_t new_size) mutable {
                    return builder.initFlags(new_size);
                }
            };
        }
        rpp::ListConst<bool> flags() const { return rpp::ListConst<bool>{builder_.asReader().getFlags()}; }

        ::rpp_schema::rpp_testing::AllocationFixedSample::List history() { return ::rpp_schema::rpp_testing::AllocationFixedSample::List{builder_.getHistory(),
                [builder = builder_](size_t new_size) mutable {
                    return builder.initHistory(new_size);
                }
            };
        }
        ::rpp_schema::rpp_testing::AllocationFixedSample::Const::List history() const { return ::rpp_schema::rpp_testing::AllocationFixedSample::Const::List{builder_.asReader().getHistory()}; }

        AllocationHintedSample_Native as_struct() const {

            std::vector<double> values_vec;
            auto capnp_values = builder_.asReader().getValues();
            values_vec.reserve(capnp_values.size());
            for (size_t i = 0; i < capnp_values.size(); ++i) {
                values_vec.push_back(capnp_values[i]);
            }


            std::vector<bool> flags_vec;
            auto capnp_flags = builder_.asReader().getFlags();
            flags_vec.reserve(capnp_flags.size());
            for (size_t i = 0; i < capnp_flags.size(); ++i) {
                flags_vec.push_back(capnp_flags[i]);
            }


            std::vector<::rpp_schema::rpp_testing::AllocationFixedSample_Native> history_vec;
            auto capnp_history = builder_.asReader().getHistory();
            history_vec.reserve(capnp_history.size());
            for (size_t i = 0; i < capnp_history.size(); ++i) {
                history_vec.push_back(::rpp_schema::rpp_testing::AllocationFixedSample::Const(capnp_history[i]).as_struct());
            }


            return AllocationHintedSample_Native{
                std::move(values_vec),
                builder_.asReader().getName(),

                std::vector<uint8_t>(builder_.asReader().getPayload().begin(), builder_.asReader().getPayload().end()),

                                std::move(flags_vec),
                std::move(history_vec)
            };
        }

        AllocationHintedSample::Const as_const() const {
            return AllocationHintedSample::Const(builder_.asReader());
        }

};

inline AllocationHintedSample::Const::Const(const AllocationHintedSample& main_wrapper)
    : reader_(const_cast<schema::rpp_testing::AllocationHintedSample::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_testing
