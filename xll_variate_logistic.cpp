// xll_variate_	.cpp - Excel add-in for logistic variates
#include "fms_variate/fms_variate_logistic.h"
#include "xll_variate.h"

using namespace fms::variate;
using namespace xll;

// int breakme = [&]() { return _crtBreakAlloc = 620; }();

AddIn xai_variate_logistic(
	Function(XLL_HANDLE, "xll_variate_logistic", "VARIATE.LOGISTIC")
	.Args({
		Arg(XLL_DOUBLE, "mu", "is the mean. Default is 0."),
		Arg(XLL_DOUBLE, "sigma", "is the standard deviation. Default is 1.")
		})
	.Uncalced()
	.FunctionHelp("Return handle to logistic variate.")
	.Category(XLL_CATEGORY)
	.Documentation(R"xyzyx(
The logistic cumulative distribution function is <i>F</i>(<i>x</i>) 
= 1/(1 + <i>e<sup>-x</sup></i>), -&infin; &lt; <i>x</i> &lt; &infin;.
)xyzyx")
);
HANDLEX WINAPI xll_variate_logistic(double mu, double sigma)
{
#pragma XLLEXPORT
	static double LOGISTIC_STD = sqrt(logistic<>::cumulant(0, 2));
	HANDLEX h = INVALID_HANDLEX;

	try {
		if (sigma == 0) {
			sigma = 1;
		}

		handle<variate_base<>> v(new variate_handle(affine(logistic<>{}, mu, sigma / LOGISTIC_STD)));
		h = v.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

