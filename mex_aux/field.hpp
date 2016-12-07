#pragma once

#include "mex.h"

namespace mex_aux {
    inline void set_field(
        mxArray *pm,
        mwIndex index,
        int field,
        mxArray *pvalue
    )
    {
        mxDestroyArray(mxGetFieldByNumber(pm, index, field));
        mxSetFieldByNumber(pm, index, field, pvalue);
    }

    inline void set_field(
        mxArray *pm,
        mwIndex index,
        const char *field,
        mxArray *pvalue
    )
    {
        auto n = mxGetFieldNumber(pm, field);
        set_field(pm, index, n, pvalue);
    }
}
