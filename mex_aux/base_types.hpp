#pragma once

#include <stdexcept>
#include <string>
#include <utility>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <kv/interval.hpp>

namespace mex_aux {
    using interval_t = kv::interval<double>;

    template <typename T>
    using vector_t = boost::numeric::ublas::vector<T>;

    template <typename T>
    using matrix_t = boost::numeric::ublas::matrix<T>;

    class exception : public std::exception {
        std::string id_;
        std::string message_;

    public:
        exception(std::string id, std::string message)
            : id_(std::move(id))
            , message_(std::move(message))
        {
        }

        const char *what() const noexcept override
        {
            return message_.c_str();
        }

        const char *id() const
        {
            return id_.c_str();
        }
    };

    class invalid_type_error : exception {
    public:
        using exception::exception;
    };

    class invalid_dimension_error : exception {
    public:
        using exception::exception;
    };
}
