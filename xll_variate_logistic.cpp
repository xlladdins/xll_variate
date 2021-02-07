// xll_variate_	.cpp - Excel add-in for logistic variates
#include "fms_variate/fms_variate_logistic.h"
#include "xll_variate.h"

using namespace fms::variate;
using namespace xll;

// int breakme = [&]() { return _crtBreakAlloc = 620; }();

AddIn xai_variate_logistic(
	Function(XLL_HANDLE, "xll_variate_logistic", "\\VARIATE.LOGISTIC")
	.Arguments({
		Arg(XLL_DOUBLE, "a", "is alpha parameter. Default is 1.", "1"),
		Arg(XLL_DOUBLE, "b", "is the beta parameter. Default is 1.", "1")
		})
	.Uncalced()
	.FunctionHelp("Return handle to generalized logistic variate.")
	.Category(XLL_CATEGORY)
	.Documentation(fms::variate::logistic_doc)
);
HANDLEX WINAPI xll_variate_logistic(double a, double b)
{
#pragma XLLEXPORT
	HANDLEX h = INVALID_HANDLEX;

	try {
		if (a == 0) {
			a = 1;
		}
		if (b == 0) {
			b = 1;
		}

		//handle<variate_base<>> v(new variate_handle(affine(logistic<>{}, mu, sigma / LOGISTIC_STD)));
		handle<variate_base<>> v(new variate_handle(logistic<>(a,b)));
		h = v.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

