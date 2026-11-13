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


struct FloatMatrix_Native {

    uint32_t rows;
    uint32_t columns;
    std::vector<double> values;
};


class FloatMatrix {
public:


    class Const {

        private:
            schema::rpp_common::FloatMatrix::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
            std::shared_ptr<void> message_lifetime_;
        public:
            Const(schema::rpp_common::FloatMatrix::Reader reader,
                  std::shared_ptr<void> lifetime = nullptr)
            : reader_(reader), message_lifetime_(std::move(lifetime)) {}
            virtual ~Const() = default;
            Const(const FloatMatrix& main_wrapper);
            Const(FloatMatrix&& main_wrapper)
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

            operator schema::rpp_common::FloatMatrix::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_, this->message_lifetime_);
            }
            static Const from_wire(schema::rpp_common::FloatMatrix::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::FloatMatrix::Reader copied_reader =
                    message->getRoot<schema::rpp_common::FloatMatrix>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<FloatMatrix>;

            inline uint32_t rows() const { return reader_.getRows(); }


            inline uint32_t columns() const { return reader_.getColumns(); }


            inline rpp::ListConst<double> values() const { return rpp::ListConst<double>{reader_.getValues(), message_lifetime_}; }


            FloatMatrix_Native as_struct() const {

                std::vector<double> values_vec;
                auto capnp_values = reader_.getValues();
                values_vec.reserve(capnp_values.size());
                for (size_t i = 0; i < capnp_values.size(); ++i) {
                    values_vec.push_back(capnp_values[i]);
                }


                return FloatMatrix_Native{
                    reader_.getRows(),
                    reader_.getColumns(),
                    std::move(values_vec)
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::FloatMatrix::Builder builder_;

    public:
        using List = rpp::List<FloatMatrix>;

        struct rows_Proxy {
            private:
                schema::rpp_common::FloatMatrix::Builder& builder_;
            public:
                rows_Proxy(schema::rpp_common::FloatMatrix::Builder& builder) : builder_(builder) {}
                operator uint32_t() const { return builder_.getRows(); }
                rows_Proxy& operator=(uint32_t value) {
                    builder_.setRows(value);
                    return *this;
                }
        };

        struct columns_Proxy {
            private:
                schema::rpp_common::FloatMatrix::Builder& builder_;
            public:
                columns_Proxy(schema::rpp_common::FloatMatrix::Builder& builder) : builder_(builder) {}
                operator uint32_t() const { return builder_.getColumns(); }
                columns_Proxy& operator=(uint32_t value) {
                    builder_.setColumns(value);
                    return *this;
                }
        };

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::FloatMatrix;
        FloatMatrix()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::FloatMatrix>()) {}
        FloatMatrix(schema::rpp_common::FloatMatrix::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~FloatMatrix() = default;

        // Move constructor and move assignment operator
        FloatMatrix(FloatMatrix&&) = default;
        FloatMatrix& operator=(FloatMatrix&&) = default;
        // Delete copy constructor and copy assignment operator
        FloatMatrix(const FloatMatrix&) = delete;
        FloatMatrix& operator=(const FloatMatrix&) = delete;

        rows_Proxy rows() { return rows_Proxy{builder_}; }
        uint32_t rows() const { return builder_.asReader().getRows(); }

        columns_Proxy columns() { return columns_Proxy{builder_}; }
        uint32_t columns() const { return builder_.asReader().getColumns(); }

        rpp::List<double> values() { return rpp::List<double>{builder_.getValues(),
                [builder = builder_](size_t new_size) mutable {
                    return builder.initValues(new_size);
                }
            };
        }
        rpp::ListConst<double> values() const { return rpp::ListConst<double>{builder_.asReader().getValues()}; }

        FloatMatrix_Native as_struct() const {

            std::vector<double> values_vec;
            auto capnp_values = builder_.asReader().getValues();
            values_vec.reserve(capnp_values.size());
            for (size_t i = 0; i < capnp_values.size(); ++i) {
                values_vec.push_back(capnp_values[i]);
            }


            return FloatMatrix_Native{
                builder_.asReader().getRows(),
                builder_.asReader().getColumns(),
                std::move(values_vec)
            };
        }

        FloatMatrix::Const as_const() const {
            return FloatMatrix::Const(builder_.asReader());
        }

};

inline FloatMatrix::Const::Const(const FloatMatrix& main_wrapper)
    : reader_(const_cast<schema::rpp_common::FloatMatrix::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
