#pragma once

#include <sstream>

#include "mex.h"

#include "base_types.hpp"

namespace mex_aux {
    template <typename ErrorClass = exception>
    inline void on_error(
        bool throw_,
        const char *id,
        const char *func,
        const char *file,
        const char *line,
        const char *msg
    )
    {
        std::ostringstream ss;

        ss << func << "(file:\"" << file << "\", line:" << line << "): " << msg;

        if (throw_) {
            throw exception(id, ss.str());
        } else {
            mexErrMsgIdAndTxt(id, ss.str().c_str());
        }
    }
}
