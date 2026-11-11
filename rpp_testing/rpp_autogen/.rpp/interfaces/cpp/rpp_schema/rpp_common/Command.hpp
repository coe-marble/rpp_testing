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


struct Command_Native {

    std::vector<double> data;
};


class Command {
public:


    class Const {

        private:
            schema::rpp_common::Command::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
        public:
            Const(schema::rpp_common::Command::Reader reader)
            : reader_(reader) {}
            virtual ~Const() = default;
            Const(const Command& main_wrapper);
            Const(Command&& main_wrapper)
            : reader_(main_wrapper.builder_.asReader()),
              orphaned_msg_builder_(std::move(main_wrapper.msg_builder_)) {}

            Const(Const&& other) noexcept
            : reader_(other.reader_),
              orphaned_msg_builder_(std::move(other.orphaned_msg_builder_)) {}

            Const& operator=(Const&& other) noexcept {
                if (this != &other) {
                    reader_ = other.reader_;
                    orphaned_msg_builder_ = std::move(other.orphaned_msg_builder_);
                }
                return *this;
            }

            Const(const Const& other) = delete;
            Const& operator=(const Const& other) = delete;

            operator schema::rpp_common::Command::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_);
            }
            static Const from_wire(schema::rpp_common::Command::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Command::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Command>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Command>;

            inline rpp::ListConst<double> data() const { return rpp::ListConst<double>{reader_.getData()}; }


            Command_Native as_struct() const {

                std::vector<double> data_vec;
                auto capnp_data = reader_.getData();
                data_vec.reserve(capnp_data.size());
                for (size_t i = 0; i < capnp_data.size(); ++i) {
                    data_vec.push_back(capnp_data[i]);
                }


                return Command_Native{
                    std::move(data_vec)
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Command::Builder builder_;

    public:
        using List = rpp::List<Command>;

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Command;
        Command()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Command>()) {}
        Command(schema::rpp_common::Command::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Command() = default;

        // Move constructor and move assignment operator
        Command(Command&&) = default;
        Command& operator=(Command&&) = default;
        // Delete copy constructor and copy assignment operator
        Command(const Command&) = delete;
        Command& operator=(const Command&) = delete;

        rpp::List<double> data() { return rpp::List<double>{builder_.getData(),
                [this](size_t new_size) {
                    return builder_.initData(new_size);
                }
            };
        }
        rpp::ListConst<double> data() const { return rpp::ListConst<double>{builder_.asReader().getData()}; }

        Command_Native as_struct() const {

            std::vector<double> data_vec;
            auto capnp_data = builder_.asReader().getData();
            data_vec.reserve(capnp_data.size());
            for (size_t i = 0; i < capnp_data.size(); ++i) {
                data_vec.push_back(capnp_data[i]);
            }


            return Command_Native{
                std::move(data_vec)
            };
        }

        Command::Const as_const() const {
            return Command::Const(builder_.asReader());
        }

};

inline Command::Const::Const(const Command& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Command::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
