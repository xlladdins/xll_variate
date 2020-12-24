#include "xll/xll/xll.h"

using namespace xll;

AddIn xai_iota(
	Function(XLL_FP, "xll_iota", "IOTA")
	.Args({
		{XLL_DOUBLE, "n", "is then number of rows."}
		})
	.Category("XLL")
	.FunctionHelp("Return {0, 1, ..., n - 1}.")
);
_FPX* WINAPI xll_iota(double n)
{
#pragma XLLEXPORT
	static xll::FPX a;

	if (n >= 1) {
		a.resize(static_cast<int>(n), 1);
		for (int i = 0; i < n; ++i) {
			a[i] = i;
		}
	}
	else if (n > 0) {
		a.resize(static_cast<int>(1 / n + 1), 1);
		for (int i = 0; i <= a.size(); ++i) {
			a[i] = i * n;
		}
	}
	else if (n > -1) {
		a.resize(static_cast<int>(-1 / n + 1), 1);
		for (int i = 0; i <= a.size(); ++i) {
			a[i] = 1 + i * n;
		}
	}
	else {
		a.resize(static_cast<int>(-n), 1);
		for (int i = 0; i < n; ++i) {
			a[i] = -n - i;
		}
	}

	return a.get();
}

