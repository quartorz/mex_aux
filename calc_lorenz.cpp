#include "mex.h"

#include "mex_aux.hpp"

#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <kv/ode-maffine.hpp>

struct lorenz {
    template <typename T>
    vector_t<T> operator()(const vector_t<T> &x, const T & t) const
    {
        vector_t<T> y(3);

        y(0) = -6.0 * x(0) + 6.0 * x(1);
        y(1) = -x(0) * x(2) + 28.0 * x(0) - x(1);
        y(2) = x(0) * x(1) - interval_t(8.0) / 3.0 * x(2);

        return y;
    }
};

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    if (nlhs > 1) {
	    mexErrMsgIdAndTxt(
            "MATLAB:calc_lorenz:maxlhs",
            "Too many output arguments."
        );
    } else if (nrhs != 4) {
	    mexErrMsgIdAndTxt(
            "MATLAB:calc_lorenz:invalidArgument",
            "nrhs != 4"
        );
    }

    // 入力引数を変換する
    vector_t<affine_t> x = mex_aux::to_interval_vector(prhs[0]);
    auto t_start = mex_aux::to_interval(prhs[1]);
    auto t_end = mex_aux::to_interval(prhs[2]);
    auto n_int = static_cast<int>(mxGetScalar(prhs[3]));
    unsigned n(n_int);

    if (x.size() != 3) {
        mex_aux::on_error(
            false,
            "MATLAB:calc_lorenz:invalidArgument",
            MEX_AUX_ERROR_MSG("length(x) != 3")
        );
    }

    if (n_int <= 0) {
        mex_aux::on_error(
            false,
            "MATLAB:calc_lorenz:invalidArgument",
            MEX_AUX_ERROR_MSG("n must be positive")
        );
    }

    // 計算結果はtsとxsに保存する
    vector_t<interval_t> ts(n + 1);
    matrix_t<interval_t> xs(3, n + 1);
    unsigned niter = 0;

    // 初期値を保存する
    ts(0) = t_start;
    column(xs, 0) = to_interval(x);

    lorenz func;

    while (niter < n) {
        ++niter;

        ts(niter) = t_start + (t_end - t_start) * niter / n;

        int r = kv::ode_maffine(func, x, ts(niter - 1), ts(niter));

        if (r == 0) {
            // 全く精度保証できなかった
            --niter;
            break;
        }

        column(xs, niter) = to_interval(x);

        if (r == 1) {
            // 途中までしか精度保証できなかった
            break;
        }
    }

    const char *result_fields[] = {"t", "x"};

    // 結果を出力に書き込む
    plhs[0] = mxCreateStructMatrix(1, 1, 2, result_fields);
    mex_aux::set_field(plhs[0], 0, 0, mex_aux::to_intval(subrange(ts, 0, niter + 1)));
    mex_aux::set_field(plhs[0], 0, 1, mex_aux::to_intval(subrange(xs, 0, 3, 0, niter + 1)));
}
