// xll_variate_discrete.cpp - Excel add-in for discrete variates
#include "xll/xll/xll.h"
#include "fms_option/fms_variate_discrete.h"
#include "fms_option/fms_variate_handle.h"

using namespace fms;
using namespace xll;

AddIn xai_variate_discrete(
	Function(XLL_HANDLE, "xll_variate_discrete", "VARIATE.DISCRETE")
	.Arguments({
		Arg(XLL_FP, "x", "are the values of the discrete random variable."),
		Arg(XLL_FP, "p", "are the probabilities of the values")
	})
	.Uncalced()
	.FunctionHelp("Return handle to the discrete variate.")
	.Category("Variate")
);
HANDLEX WINAPI xll_variate_discrete(const _FPX* px, const _FPX* pp)
{
#pragma XLLEXPORT
	try {
		ensure(size(*px) == size(*pp));
		handle<variate_base<>> m(new variate_handle(variate::discrete(size(*px), px->array, pp->array)));

		if (m) {
			return m.get();
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return INVALID_HANDLEX;
}

