#pragma once

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

    inline mxArray *to_intval(const vector_t<interval_t> &v)
    {
        mxArray *lhs[1], *rhs[2];

        rhs[0] = mxCreateDoubleMatrix(v.size(), 1, mxREAL);
        rhs[1] = mxCreateDoubleMatrix(v.size(), 1, mxREAL);

        for (unsigned i = 0; i < v.size(); ++i) {
            mxGetPr(rhs[0])[i] = v(i).lower();
            mxGetPr(rhs[1])[i] = v(i).upper();
        }

        mexCallMATLAB(1, lhs, 2, rhs, "infsup");

        return lhs[0];
    }

    inline mxArray *to_intval(const matrix_t<interval_t> &v)
    {
        mxArray *lhs[1], *rhs[2];

        auto nrows = v.size1();
        auto ncols = v.size2();

        rhs[0] = mxCreateDoubleMatrix(nrows, ncols, mxREAL);
        rhs[1] = mxCreateDoubleMatrix(nrows, ncols, mxREAL);

        for (unsigned i = 0; i < nrows; ++i) {
            for (unsigned j = 0; j < ncols; ++j) {
                mxGetPr(rhs[0])[i + j * nrows] = v(i, j).lower();
                mxGetPr(rhs[1])[i + j * nrows] = v(i, j).upper();
            }
        }

        mexCallMATLAB(1, lhs, 2, rhs, "infsup");

        return lhs[0];
    }
}
