// xll_hypergeometric.cpp = Hypergeometric functions
#include "fms_variate/fms_hypergeometric.h"
#include "xll/xll/xll.h"

using namespace xll;
using namespace fms;

AddIn xai_hypergeometric(
	Function(XLL_DOUBLE, "xll_hypergeometric", "pFq")
	.Args({
		{XLL_FP, "a", "is an array of p numbers."},
		{XLL_FP, "b", "is an array of q numbers."},
		{XLL_DOUBLE, "x", "is the value at which to evaluate the function."},
		{XLL_BOOL, "[regulaized]", "return regularized value. Default is FALSE."},
	})
	.FunctionHelp("Return hypergeometric pFq value.")
	.Category("XLL")
);
double WINAPI xll_hypergeometric(_FPX* pa, _FPX* pb, double x, BOOL regularized)
{
#pragma XLLEXPORT
	double result = XLL_NAN;

	try {
		auto a = list<double>(begin(*pa), end(*pa));
		auto b = list<double>(begin(*pb), end(*pb));

		result = fms::HypergeometricPFQ(a, b, x, regularized);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}