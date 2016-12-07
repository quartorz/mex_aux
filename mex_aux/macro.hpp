#pragma once

#if !defined(FUNC_NAME)
#  define FUNC_NAME mex-function
#endif

#define MEX_AUX_TO_STRING(x) MEX_AUX_TO_STRING_I(x)
#define MEX_AUX_TO_STRING_I(x) # x

#define MEX_AUX_FUNC_NAME MEX_AUX_TO_STRING(FUNC_NAME)

#define MEX_AUX_ERROR_MSG_II(msg, line) __FUNCTION__, __FILE__, # line, msg
#define MEX_AUX_ERROR_MSG_I(msg, line) MEX_AUX_ERROR_MSG_II(msg, line)
#define MEX_AUX_ERROR_MSG(msg) MEX_AUX_ERROR_MSG_I(msg, __LINE__)

#if defined(_MSC_VER)
#  define MEX_AUX_UNREACHABLE() __assume(0)
#else
#  define MEX_AUX_UNREACHABLE() __builtin_unreachable()
#endif
