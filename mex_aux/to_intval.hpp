#pragma once

#include <type_traits>

#include "mex.h"

#include "base_types.hpp"

namespace mex_aux {
    inline mxArray *to_intval(const interval_t &v)
    {
        mxArray *lhs[1], *rhs[2];

        rhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
        rhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);

        mxGetPr(rhs[0])[0] = v.lower();
        mxGetPr(rhs[1])[0] = v.upper();

        mexCallMATLAB(1, lhs, 2, rhs, "infsup");

        return lhs[0];
    }

    template <typename E>
    inline mxArray *to_intval(
        const boost::numeric::ublas::vector_expression<E> &v
    )
    {
        using value_type = typename E::value_type;

        static_assert(
            std::is_same<std::decay_t<value_type>, interval_t>::value,
            "v must be an interval vector"
        );

        auto e = v();
        auto size = e.size();

        mxArray *lhs[1], *rhs[2];

        rhs[0] = mxCreateDoubleMatrix(size, 1, mxREAL);
        rhs[1] = mxCreateDoubleMatrix(size, 1, mxREAL);

        for (unsigned i = 0; i < size; ++i) {
            auto x = e(i);
            mxGetPr(rhs[0])[i] = x.lower();
            mxGetPr(rhs[1])[i] = x.upper();
        }

        mexCallMATLAB(1, lhs, 2, rhs, "infsup");

        return lhs[0];
    }

    template <typename E>
    inline mxArray *to_intval(
        const boost::numeric::ublas::matrix_expression<E> &v
    )
    {
        using value_type = typename E::value_type;

        static_assert(
            std::is_same<std::decay_t<value_type>, interval_t>::value,
            "v must be an interval matrix"
        );

        auto e = v();

        mxArray *lhs[1], *rhs[2];

        auto nrows = e.size1();
        auto ncols = e.size2();

        rhs[0] = mxCreateDoubleMatrix(nrows, ncols, mxREAL);
        rhs[1] = mxCreateDoubleMatrix(nrows, ncols, mxREAL);

        for (unsigned i = 0; i < nrows; ++i) {
            for (unsigned j = 0; j < ncols; ++j) {
                auto x = e(i, j);
                mxGetPr(rhs[0])[i + j * nrows] = x.lower();
                mxGetPr(rhs[1])[i + j * nrows] = x.upper();
            }
        }

        mexCallMATLAB(1, lhs, 2, rhs, "infsup");

        return lhs[0];
    }
}
