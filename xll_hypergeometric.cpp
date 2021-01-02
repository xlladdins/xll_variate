// xll_hypergeometric.cpp = Hypergeometric functions
#include "fms_variate/fms_hypergeometric.h"
#include "xll/xll/xll.h"

using namespace xll;
using namespace fms;

AddIn xai_hypergeometric(
	Function(XLL_FP, "xll_hypergeometric", "pFq")
	.Args({
		{XLL_FP, "a", "is an array of p numbers.", "={1}"},
		{XLL_FP, "b", "is an array of q numbers.", "={1}" },
		{XLL_DOUBLE, "x", "is the value at which to evaluate the function.", "=1"},
		{XLL_BOOL, "[regularized]", "return regularized value. Default is FALSE."},
	})
	.FunctionHelp("Return hypergeometric pFq value.")
	.Category("XLL")
);
_FPX* WINAPI xll_hypergeometric(_FPX* pa, _FPX* pb, double x, BOOL regularized)
{
#pragma XLLEXPORT
	static FPX result(4,1);

	try {
		auto a = list<double>(begin(*pa), end(*pa));
		auto b = list<double>(begin(*pb), end(*pb));
		fms::Hypergeometric<double> pFq(a, b);

		auto value = pFq.value(x);

		result[0] = std::get<0>(value);
		result[1] = std::get<1>(value);
		result[2] = std::get<2>(value);
		result[3] = std::get<3>(value);

		if (regularized) {
			result[0] = pFq.regularized();
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return &result;
}