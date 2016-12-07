#include "mex.h"

#define FUNC_NAME conv_mat

#include "mex_aux.hpp"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    if (nlhs > 1) {
	    mexErrMsgIdAndTxt(
            "MATLAB:conv_mat:maxlhs",
            "Too many output arguments."
        );
    }

    auto x = mex_aux::to_interval_matrix(prhs[0]);

    plhs[0] = mex_aux::to_intval(x);
}
