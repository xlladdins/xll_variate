// xll_variate_normal.cpp - Excel add-in for normal variates
#include "fms_variate/fms_variate_normal.h"
#include "xll_variate.h"
#include "xll/xll/xll.h"

using namespace fms::variate;
using namespace xll;

// int breakme = [&]() { return _crtBreakAlloc = 620; }();

AddIn xai_variate_normal(
	Function(XLL_HANDLE, "xll_variate_normal", "VARIATE.NORMAL")
	.Args({
		Arg(XLL_DOUBLE, "mu", "is the mean. Default is 0."),
		Arg(XLL_DOUBLE, "sigma", "is the standard deviation. Default is 1.")
		})
	.Uncalced()
	.FunctionHelp("Return handle to normal variate.")
	.Category(XLL_CATEGORY)
	.Documentation(R"xyzyx(
The normal distribution function has density <i>f</i>(<i>x</i>) 
= exp(-<i>x</i><sup>2</sup>/2)/&radic;<span style="text-decoration:overline">2&pi;</span>
)xyzyx")
);
HANDLEX WINAPI xll_variate_normal(double mu, double sigma)
{
#pragma XLLEXPORT
	handle<variate_base<>> m(new variate_handle(affine(standard_normal<>{}, mu, sigma)));

	return m.get();
}

