// xll_variate_normal.cpp - Excel add-in for normal variates
#include "fms_variate/fms_variate_normal.h"
#include "xll_variate.h"

using namespace fms::variate;
using namespace xll;

// int breakme = [&]() { return _crtBreakAlloc = 620; }();

AddIn xai_variate_normal(
	Function(XLL_HANDLE, "xll_variate_normal", "VARIATE_NORMAL")
	.Args({
		Arg(XLL_DOUBLE, "mu", "is the mean. Defalt is 0.", "0"),
		Arg(XLL_DOUBLE, "sigma", "is the standard deviation. Default is 1.", "1")
		})
	.Uncalced()
	.FunctionHelp("Return handle to normal variate.")
	.Category(XLL_CATEGORY)
	.Documentation(R"xyzyx(
The normal distribution has density function \(f(x) = \exp(-x^2/2)/\sqrt{2\pi}\), 
\(-\infty < x < \infty\).
)xyzyx")
);
HANDLEX WINAPI xll_variate_normal(double mu, double sigma)
{
#pragma XLLEXPORT
	HANDLEX h = INVALID_HANDLEX;

	try {
		handle<variate_base<>> v(new variate_handle(affine(standard_normal<>{}, mu, sigma)));
		h = v.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

