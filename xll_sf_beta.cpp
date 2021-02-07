// xll_sf_beta.cpp = Hypergeometric functions
#include "fms_variate/fms_variate_logistic.h"
#include "xll/xll/xll.h"

#define XLL_CATEGORY "XLL"

using namespace xll;
using namespace fms::variate;

static AddIn xai_variate_beta(
	Function(XLL_DOUBLE, "xll_variate_beta", "VARIATE.BETA")
	.Arguments({
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
		ensure(a > 0);
		ensure(b > 0);
		ensure(0 <= u and u <= 1);

		if (u == 1) {
			if (n == 0) {
				return logistic<double>::beta(a, b);
			}
			else {
				return logistic<double>::beta_1(a, b);
			}
		}
		else {
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
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return XLL_NAN;
}
