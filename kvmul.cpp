#include <cstring>

#include <kv/interval.hpp>

#include "mex.h"

#define FUNC_NAME kvmul

#include "mex_aux.hpp"

namespace {
    kv::interval<double> to_interval(const mxArray *v)
    {
        kv::interval<double> r;

        if (mxIsStruct(v) && std::strcmp(mxGetClassName(v), "intval") == 0) {
            auto inf = mxGetField(v, 0, "inf");
            auto sup = mxGetField(v, 0, "sup");

            // if (!mxIsDouble(inf) || !mxIsDouble(sup)) {
            // }

            r.lower() = mxGetPr(inf)[0];
            r.upper() = mxGetPr(sup)[0];
        } else if (mxIsDouble(v)) {
            auto pt = mxGetPr(v)[0];
            r.lower() = pt;
            r.upper() = pt;
        } else {
            mexErrMsgIdAndTxt(
                "MATLAB:kvmul:invalidArgument",
                "Arguments must be intval or double."
            );
        }

        return r;
    }

    mxArray *to_intval(const kv::interval<double> &v)
    {
        mxArray *lhs[1], *rhs[2];

        rhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
        rhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);

        mxGetPr(rhs[0])[0] = v.lower();
        mxGetPr(rhs[1])[0] = v.upper();

        mexCallMATLAB(1, lhs, 2, rhs, "infsup");

        return lhs[0];
    }
}

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    if (nrhs != 2) {
        mexErrMsgIdAndTxt(
            "MATLAB:kvmul:invalidNumInputs",
            "Two input arguments required."
        );
    } else if (nlhs > 1) {
	    mexErrMsgIdAndTxt(
            "MATLAB:kvmul:maxlhs",
            "Too many output arguments."
        );
    }

    auto x = mex_aux::to_interval_scalar(prhs[0]);
    auto y = mex_aux::to_interval_scalar(prhs[1]);

    auto z = x * y;

    plhs[0] = to_intval(z);
}
