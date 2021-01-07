// xll_variate_	.cpp - Excel add-in for logistic variates
#include "fms_variate/fms_variate_logistic.h"
#include "xll_variate.h"

using namespace fms::variate;
using namespace xll;

// int breakme = [&]() { return _crtBreakAlloc = 620; }();

AddIn xai_variate_logistic(
	Function(XLL_HANDLE, "xll_variate_logistic", "VARIATE_LOGISTIC")
	.Args({
		Arg(XLL_DOUBLE, "mu", "is the mean. Default is 0."),
		Arg(XLL_DOUBLE, "sigma", "is the standard deviation. Default is 1.")
		})
	.Uncalced()
	.FunctionHelp("Return handle to logistic variate.")
	.Category(XLL_CATEGORY)
	.Documentation(R"xyzyx(
The generalized logistic cumulative distribution function is \(F(\alpha, \beta; x) 
= 1/B(\alpha, \beta) e^{-\beta x}/(1 + e^{-x}))^{\alpha + \beta}\), \(-\infty < x < \infty\).
)xyzyx")
);
HANDLEX WINAPI xll_variate_logistic(double mu, double sigma)
{
#pragma XLLEXPORT
	static double LOGISTIC_STD = sqrt(logistic<>::cumulant(0, 2));
	HANDLEX h = INVALID_HANDLEX;

	try {
		if (sigma == 0) {
			sigma = 1 + 0*mu;
		}

		//handle<variate_base<>> v(new variate_handle(affine(logistic<>{}, mu, sigma / LOGISTIC_STD)));
		handle<variate_base<>> v(new variate_handle(logistic<>{}));
		h = v.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddIn xai_variate_beta(
	Function(XLL_DOUBLE, "xll_variate_beta", "VARIATE.BETA")
	.Args({
		Arg(XLL_DOUBLE, "a", "is the a parameter."),
		Arg(XLL_DOUBLE, "b", "is the b parameter."),
		Arg(XLL_DOUBLE, "u", "is the value."),
		Arg(XLL_WORD, "n", "indicates which derivative."),
		})
		.FunctionHelp("Return the incomplete regulariazed beta distribution and partial derivatives.")
	.Category(XLL_CATEGORY)
	.Documentation(R"xyzyx(
Return incomplete regulaized beta distribution \(I_u(a,b)\), \(n = 0\), \((\partial/\partial a) I_u(a,b)\), \(n = 1\),
or \((\partial/\partial b) I_u(a,b)\), \(n = 2\).
)xyzyx")
);
double WINAPI xll_variate_beta(double a, double b, double u, WORD n)
{
#pragma XLLEXPORT
	try {
		if (n == 0) {
			return logistic<double>::beta_inc(a, b, u);
		}
		if (n == 1) {
			return logistic<double>::beta_inc_1(a, b, u);
		}
		if (n == 2) {
			return logistic<double>::beta_inc_2(a, b, u);
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return XLL_NAN;
}
