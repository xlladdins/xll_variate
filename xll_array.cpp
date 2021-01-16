// xll_array.cpp - Arrays of doubles
#include "xll/xll/xll.h"

using namespace xll;

#define CATEGORY "ARRAY"

AddIn xai_resize(
	Function(XLL_FP, "xll_resize", "ARRAY.RESIZE")
	.Args({
		Arg({XLL_FP, "array", "is an array."}),
		Arg({XLL_WORD, "rows", "is the number of rows. Default is 1."}),
		Arg({XLL_WORD, "columns", "is the number of columns. Default is 1."}),
	})
	.Category(CATEGORY)
	.FunctionHelp("Return new array with the specified rows and columns.")
);
_FPX* WINAPI xll_resize(_FPX* pa, WORD r, WORD c)
{
#pragma XLLEXPORT
	static FPX a;

	if (r == 0) {
		r = 1;
	}
	if (c == 0) {
		c = 1;
	}

	a.resize(r, c);
	memcpy(a.begin(), pa->array, a.size() * sizeof(double));


	return &a;
}

AddIn xai_apply(
	Function(XLL_FP, "xll_apply", "ARRAY.APPLY")
	.Args({
		Arg({XLL_LPOPER, "function", "is a function to apply to the array."}),
		Arg({XLL_FP, "array", "is an array."}),
	})
	.Category(CATEGORY)
	.FunctionHelp("Return new array after applying function.")
);
_FPX* WINAPI xll_apply(LPOPER pf, _FPX* pa)
{
#pragma XLLEXPORT

	try {
		for (int i = 0; i < size(*pa); ++i) {
			OPER result = Excel(xlUDF, *pf, OPER(pa->array[i]));
			ensure(result.xltype == xltypeNum);

			pa->array[i] = result.val.num;
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return pa;
}

AddIn xai_iota(
	Function(XLL_FP, "xll_iota", "ARRAY.IOTA")
	.Args({
		Arg({XLL_DOUBLE, "x", "is the number of rows or the increment."}),
	})
	.Category(CATEGORY)
	.FunctionHelp("Return {0, 1, ..., x - 1}, x >= 1 or {0, x, ..., 1}, x < 1. Negative values reverse the order.")
);
_FPX* WINAPI xll_iota(double x)
{
#pragma XLLEXPORT
	static FPX a;

	if (x == 0) {
		a.resize(1, 1);
		a[0] = XLL_NAN;
	}
	else if (x >= 1) {
		a.resize(static_cast<int>(x), 1);
		for (int i = 0; i < a.size(); ++i) {
			a[i] = i;
		}
	}
	else if (x > 0) {
		a.resize(static_cast<int>(1 / x + 1), 1);
		for (int i = 0; i < a.size(); ++i) {
			a[i] = i * x;
		}
	}
	else if (x > -1) {
		a.resize(static_cast<int>(-1 / x + 1), 1);
		for (int i = 0; i < a.size(); ++i) {
			a[i] = 1 + i * x;
		}
	}
	else {
		a.resize(static_cast<int>(-x), 1);
		for (int i = 0; i < a.size(); ++i) {
			a[i] = -x - i;
		}
	}

	return &a;
}

AddIn xai_array(
	Function(XLL_FP, "xll_sequence", "ARRAY.SEQUENCE")
	.Args({
		Arg({XLL_DOUBLE, "start", "is the first element of the sequence."}),
		Arg({XLL_LONG, "count", "is the number of elements."}),
		Arg({XLL_DOUBLE, "_incr", "is the increment. Default is 1."}),
	})
	.Category(CATEGORY)
	.FunctionHelp("Return {start, start + incr, ..., start + (count-1)*incr}.")
);
_FPX* WINAPI xll_sequence(double start, LONG count, double incr)
{
#pragma XLLEXPORT
	static FPX a;

	if (count == 0) {
		count = 1;
	}
	if (incr == 0) {
		incr = 1;
	}

	a.resize(count, 1);
	for (int i = 0; i < a.size(); ++i) {
		a[i] = start + i * incr;
	}

	return &a;
}

AddIn xai_interval(
	Function(XLL_FP, "xll_interval", "ARRAY.INTERVAL")
	.Args({
		Arg({XLL_DOUBLE, "start", "is the first element of the interval."}),
		Arg({XLL_DOUBLE, "stop", "is the last element of the interval."}),
		Arg({XLL_DOUBLE, "_incr", "is the increment (<=1) or number of rows (> 1). Default is 1."}),
		})
	.Category(CATEGORY)
	.FunctionHelp("Return {start, start + incr, ..., stop}.")
);
_FPX* WINAPI xll_interval(double start, double stop, double incr)
{
#pragma XLLEXPORT
	static FPX a;

	if (incr <= 0) {
		incr = 1;
	}
	
	if (incr <= 1) {
		a.resize(1 + static_cast<int>(abs((stop - start) / incr)), 1);
		for (int i = 0; i < a.size(); ++i) {
			a[i] = start + i * incr;
		}
	}
	else {
		a.resize(static_cast<unsigned>(incr) + 1, 1);
		for (int i = 0; i < a.size(); ++i) {
			a[i] = start + (stop - start) * i / incr;
		}
	}

	return &a;
}



