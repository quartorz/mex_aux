#pragma once

#include <stdexcept>

#include "mex.h"

#include "base_types.hpp"
#include "macro.hpp"
#include "on_error.hpp"
#include "to_double.hpp"

namespace mex_aux {
    inline interval_t to_interval(double v)
    {
        return interval_t(v, v);
    }

    inline vector_t<interval_t> to_interval(const vector_t<double> &v)
    {
        vector_t<interval_t> r(v.size());

        for (unsigned i = 0; i < v.size(); ++i) {
            r(i).lower() = v(i);
            r(i).upper() = v(i);
        }

        return r;
    }

    inline matrix_t<interval_t> to_interval(const matrix_t<double> &v)
    {
        matrix_t<interval_t> r(v.size1(), v.size2());

        for (unsigned i = 0; i < v.size1(); ++i) {
            for (unsigned j = 0; j < v.size2(); ++j) {
                r(i, j).lower() = v(i, j);
                r(i, j).upper() = v(i, j);
            }
        }

        return r;
    }

    inline interval_t to_interval(
        const mxArray *v,
        bool throw_if_error = false,
        bool strict = true
    )
    {
        if (mxIsStruct(v) && std::strcmp(mxGetClassName(v), "intval") == 0) {
            // inf と sup は実行列
            auto inf = mxGetField(v, 0, "inf");
            auto sup = mxGetField(v, 0, "sup");

            if (strict) {
                // v がスカラーかどうかをチェックする
                if (!mxIsScalar(inf)) {
                    on_error<invalid_dimension_error>(
                        throw_if_error,
                        "MATLAB:" MEX_AUX_FUNC_NAME ":to_interval_scalar:invalidArgument",
                        MEX_AUX_ERROR_MSG("Input must be scalar.")
                    );
                }
            }

            return interval_t(mxGetScalar(inf), mxGetScalar(sup));
        } else if (mxIsNumeric(v) && !mxIsComplex(v)) {
            if (strict) {
                // v がスカラーかどうかをチェックする
                if (!mxIsScalar(v)) {
                    on_error<invalid_dimension_error>(
                        throw_if_error,
                        "MATLAB:" MEX_AUX_FUNC_NAME ":to_interval_scalar:invalidArgument",
                        MEX_AUX_ERROR_MSG("Input must be scalar.")
                    );
                }
            }

            return interval_t(mxGetScalar(v));
        }

        // v が区間でも数値でもなかったらエラー
        on_error<invalid_type_error>(
            throw_if_error,
            "MATLAB:" MEX_AUX_FUNC_NAME ":to_interval_scalar:invalidArgument",
            MEX_AUX_ERROR_MSG("Input must be intval or real number.")
        );

        MEX_AUX_UNREACHABLE();
    }

    inline vector_t<interval_t> to_interval_vector(
        const mxArray *v,
        bool throw_if_error = false,
        bool strict = true
    )
    {
        if (mxIsStruct(v) && std::strcmp(mxGetClassName(v), "intval") == 0) {
            // inf と sup は実行列
            auto inf_mat = mxGetField(v, 0, "inf");
            auto sup_mat = mxGetField(v, 0, "sup");

            if (strict) {
                auto nrows = mxGetM(inf_mat);
                auto ncols = mxGetN(inf_mat);

                if (nrows != 1 && ncols != 1) {
                    on_error<invalid_dimension_error>(
                        throw_if_error,
                        "MATLAB:" MEX_AUX_FUNC_NAME ":to_interval_vector:invalidArgument",
                        MEX_AUX_ERROR_MSG("Input must be vector.")
                    );
                }
            }

            auto inf_cpp = to_double_vector(inf_mat, throw_if_error, strict);
            auto sup_cpp = to_double_vector(sup_mat, throw_if_error, strict);

            vector_t<interval_t> r(inf_cpp.size());

            for (unsigned i = 0; i < inf_cpp.size(); ++i) {
                r(i).lower() = inf_cpp[i];
                r(i).upper() = sup_cpp[i];
            }

            return r;
        } else if (mxIsNumeric(v) && !mxIsComplex(v)) {
            if (strict) {
                auto nrows = mxGetM(v);
                auto ncols = mxGetN(v);

                if (nrows != 1 && ncols != 1) {
                    on_error<invalid_dimension_error>(
                        throw_if_error,
                        "MATLAB:" MEX_AUX_FUNC_NAME ":to_interval_vector:invalidArgument",
                        MEX_AUX_ERROR_MSG("Input must be vector.")
                    );
                }
            }

            auto val = to_double_vector(v, throw_if_error, strict);

            return to_interval(val);
        } 

        // v が区間でも数値でもなかったらエラー
        on_error<invalid_type_error>(
            throw_if_error,
            "MATLAB:" MEX_AUX_FUNC_NAME ":to_interval_vector:invalidArgument",
            MEX_AUX_ERROR_MSG("Input must be intval vector or real vector.")
        );

        MEX_AUX_UNREACHABLE();
    }

    inline matrix_t<interval_t> to_interval_matrix(
        const mxArray *v,
        bool throw_if_error = false
    )
    {
        if (mxIsStruct(v) && std::strcmp(mxGetClassName(v), "intval") == 0) {
            auto inf_mat = mxGetField(v, 0, "inf");
            auto sup_mat = mxGetField(v, 0, "sup");

            auto nrows = mxGetM(inf_mat);
            auto ncols = mxGetN(inf_mat);

            matrix_t<interval_t> r(nrows, ncols);

            auto inf_cpp = to_double_matrix(inf_mat);
            auto sup_cpp = to_double_matrix(sup_mat);

            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j).lower() = inf_cpp(i, j);
                    r(i, j).upper() = sup_cpp(i, j);
                }
            }

            return r;
        } else if (mxIsNumeric(v) && !mxIsComplex(v)) {
            auto val = to_double_matrix(v);
            
            return to_interval(val);
        }

        // v が区間でも数値でもなかったらエラー
        on_error<invalid_type_error>(
            throw_if_error,
            "MATLAB:" MEX_AUX_FUNC_NAME ":to_interval_matrix:invalidArgument",
            MEX_AUX_ERROR_MSG("Input must be intval matrix or real matrix.")
        );

        MEX_AUX_UNREACHABLE();
    }
}
