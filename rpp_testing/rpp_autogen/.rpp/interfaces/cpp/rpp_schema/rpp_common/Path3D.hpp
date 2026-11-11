#pragma once
#include <string>
#include <vector>
#include <map>
#include "capnp_gen/rpp_common/msgs.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <memory>
#include <utility>

#include "rpp_schema/rpp_common/Point3D.hpp"

namespace rpp_schema::rpp_common{


struct Path3D_Native {

    std::vector<Point3D_Native> points;
};


class Path3D {
public:


    class Const {

        private:
            schema::rpp_common::Path3D::Reader reader_;
            std::unique_ptr<capnp::MallocMessageBuilder> orphaned_msg_builder_;
        public:
            Const(schema::rpp_common::Path3D::Reader reader)
            : reader_(reader) {}
            virtual ~Const() = default;
            Const(const Path3D& main_wrapper);
            Const(Path3D&& main_wrapper)
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

            operator schema::rpp_common::Path3D::Reader() const { return reader_; }
            Const shallow_copy() const {
                return Const(this->reader_);
            }
            static Const from_wire(schema::rpp_common::Path3D::Reader reader) {
                auto message = std::make_unique<capnp::MallocMessageBuilder>();
                message->setRoot(reader);
                schema::rpp_common::Path3D::Reader copied_reader =
                    message->getRoot<schema::rpp_common::Path3D>();
                Const result(copied_reader);
                result.orphaned_msg_builder_ = std::move(message);
                return result;
            }
        using List = rpp::ListConst<Path3D>;

            inline Point3D::Const::List points() const { return Point3D::Const::List{reader_.getPoints()}; }


            Path3D_Native as_struct() const {

                std::vector<Point3D_Native> points_vec;
                auto capnp_points = reader_.getPoints();
                points_vec.reserve(capnp_points.size());
                for (size_t i = 0; i < capnp_points.size(); ++i) {
                    points_vec.push_back(Point3D::Const(capnp_points[i]).as_struct());
                }


                return Path3D_Native{
                    std::move(points_vec)
                };
            }
    };


    private:
        friend class Const;
        std::unique_ptr<capnp::MallocMessageBuilder> msg_builder_;
        schema::rpp_common::Path3D::Builder builder_;

    public:
        using List = rpp::List<Path3D>;

    public:
        using IsRppStruct = void;
        using CapnpType = schema::rpp_common::Path3D;
        Path3D()
            : msg_builder_(std::make_unique<capnp::MallocMessageBuilder>()),
              builder_(msg_builder_->initRoot<schema::rpp_common::Path3D>()) {}
        Path3D(schema::rpp_common::Path3D::Builder builder)
            : msg_builder_(nullptr), builder_(builder) {}

        virtual ~Path3D() = default;

        // Move constructor and move assignment operator
        Path3D(Path3D&&) = default;
        Path3D& operator=(Path3D&&) = default;
        // Delete copy constructor and copy assignment operator
        Path3D(const Path3D&) = delete;
        Path3D& operator=(const Path3D&) = delete;

        Point3D::List points() { return Point3D::List{builder_.getPoints(),
                [this](size_t new_size) {
                    return builder_.initPoints(new_size);
                }
            };
        }
        Point3D::Const::List points() const { return Point3D::Const::List{builder_.asReader().getPoints()}; }

        Path3D_Native as_struct() const {

            std::vector<Point3D_Native> points_vec;
            auto capnp_points = builder_.asReader().getPoints();
            points_vec.reserve(capnp_points.size());
            for (size_t i = 0; i < capnp_points.size(); ++i) {
                points_vec.push_back(Point3D::Const(capnp_points[i]).as_struct());
            }


            return Path3D_Native{
                std::move(points_vec)
            };
        }

        Path3D::Const as_const() const {
            return Path3D::Const(builder_.asReader());
        }

};

inline Path3D::Const::Const(const Path3D& main_wrapper)
    : reader_(const_cast<schema::rpp_common::Path3D::Builder&>(main_wrapper.builder_).asReader()) {}

}  // namespace rpp_common
