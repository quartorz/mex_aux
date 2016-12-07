#pragma once

#include <cstdint>

#include "mex.h"

#include "base_types.hpp"
#include "macro.hpp"
#include "on_error.hpp"

namespace mex_aux {
    inline double to_double_scalar(
        const mxArray *v,
        bool strict = false,
        bool throw_if_error = false
    )
    {
        if (strict) {
            if (!mxIsNumeric(v) || mxIsComplex(v) || !mxIsScalar(v)) {
                on_error<invalid_type_error>(
                    throw_if_error,
                    "MATLAB:" MEX_AUX_FUNC_NAME ":to_double_scalar:invalidArgument",
                    MEX_AUX_ERROR_MSG("Input must be real and scalar.")
                );
            }
        }

        return mxGetScalar(v);
    }

    inline vector_t<double> to_double_vector(
        const mxArray *v,
        bool strict = false,
        bool throw_if_error = false
    )
    {
        auto nrows = mxGetM(v);
        auto ncols = mxGetN(v);

        if (strict) {
            if (!mxIsNumeric(v) || mxIsComplex(v) || (nrows != 1 && ncols != 1)) {
                on_error<invalid_type_error>(
                    throw_if_error,
                    "MATLAB:" MEX_AUX_FUNC_NAME ":to_double_scalar:invalidArgument",
                    MEX_AUX_ERROR_MSG("Input must be real vector.")
                );
            }
        }

        auto dim = std::max(nrows, ncols);
        auto type = mxGetClassID(v);
        auto data = mxGetData(v);

        if (!strict && nrows != 1 && ncols != 1) {
            dim = nrows;
        }

        vector_t<double> r(dim);

        switch (type) {
        case mxDOUBLE_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = reinterpret_cast<double*>(data)[i];
            }
            break;
        case mxSINGLE_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<float*>(data)[i]);
            }
            break;
        case mxINT8_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<std::int8_t*>(data)[i]);
            }
            break;
        case mxUINT8_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<std::uint8_t*>(data)[i]);
            }
            break;
        case mxINT16_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<std::int16_t*>(data)[i]);
            }
            break;
        case mxUINT16_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<std::uint16_t*>(data)[i]);
            }
            break;
        case mxINT32_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<std::int32_t*>(data)[i]);
            }
            break;
        case mxUINT32_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<std::uint32_t*>(data)[i]);
            }
            break;
        case mxINT64_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<std::int64_t*>(data)[i]);
            }
            break;
        case mxUINT64_CLASS:
            for (unsigned i = 0; i < dim; ++i) {
                r(i) = double(reinterpret_cast<std::uint64_t*>(data)[i]);
            }
            break;
        default:
            MEX_AUX_UNREACHABLE();
        }

        return r;
    }

    inline matrix_t<double> to_double_matrix(
        const mxArray *v
    )
    {
        auto nrows = mxGetM(v);
        auto ncols = mxGetN(v);
        auto type = mxGetClassID(v);
        auto data = mxGetData(v);

        matrix_t<double> r(nrows, ncols);

        switch (type) {
        case mxDOUBLE_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<double*>(data)[i + j * nrows];
                }
            }
            break;
        case mxSINGLE_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<float*>(data)[i + j * nrows];
                }
            }
            break;
        case mxINT8_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<std::int8_t*>(data)[i + j * nrows];
                }
            }
            break;
        case mxUINT8_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<std::uint8_t*>(data)[i + j * nrows];
                }
            }
            break;
        case mxINT16_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<std::int16_t*>(data)[i + j * nrows];
                }
            }
            break;
        case mxUINT16_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<std::uint16_t*>(data)[i + j * nrows];
                }
            }
            break;
        case mxINT32_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<std::int32_t*>(data)[i + j * nrows];
                }
            }
            break;
        case mxUINT32_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<std::uint32_t*>(data)[i + j * nrows];
                }
            }
            break;
        case mxINT64_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<std::int64_t*>(data)[i + j * nrows];
                }
            }
            break;
        case mxUINT64_CLASS:
            for (unsigned i = 0; i < nrows; ++i) {
                for (unsigned j = 0; j < ncols; ++j) {
                    r(i, j) = reinterpret_cast<std::uint64_t*>(data)[i + j * nrows];
                }
            }
            break;
        default:
            MEX_AUX_UNREACHABLE();
        }

        return r;
    }
}
