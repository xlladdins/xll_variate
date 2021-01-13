// xll_sf_hypergeometric.cpp = Hypergeometric functions
#include "fms_variate/fms_sf_hypergeometric.h"
#include "xll/xll/xll.h"

using namespace xll;
using namespace fms::sf;
using fms::sf::list;

AddIn xai_hypergeometric(
	Function(XLL_FP, "xll_hypergeometric", "HYPERGEOMETRIC")
	.Args({
		{XLL_FP, "a", "is an array of p numbers.", "={1}"},
		{XLL_FP, "b", "is an array of q numbers.", "={1}" },
		{XLL_DOUBLE, "x", "is the value at which to evaluate the function.", "=1"},
		{XLL_BOOL, "regularized?", "return regularized value. Default is FALSE.", "=FALSE"},
	})
	.FunctionHelp("Return hypergeometric pFq(x) value.")
	.Category("XLL")
	.Documentation(R"xyzyx(
The generalized hypergeometric function is
\[
\;_pF_q(a_1,\ldots, a_p; b_1,\ldots, b_q; x)
	= \sum_{n=0}^\infty \frac{\Pi_{j=1}^p (a_j)_n}}{\Pi_{k=1}^q (b_k)_n} \frac{x^n}{n!}
\]
where \((a)_n} = \Gamma(a + n)/\Gamma(a) = a (a + 1) \cdots (a + n - 1)\) is the rising Pochhammer symbol.
)xyzyx")
);
_FPX* WINAPI xll_hypergeometric(_FPX* pa, _FPX* pb, double x, BOOL regularized)
{
#pragma XLLEXPORT
	static FPX result(4,1);

	try {
		auto a = list<double>(begin(*pa), end(*pa));
		auto b = list<double>(begin(*pb), end(*pb));
		Hypergeometric<double> pFq(a, b);

		std::tie(result[0], result[1], result[2], result[3]) = pFq.value(x);

		if (regularized) {
			result[0] = pFq.regularized();
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return &result;
}