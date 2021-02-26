// xll_variate.cpp - random variates
#include "xll_variate.h"

using namespace fms::variate;
using namespace xll;


#ifdef _DEBUG
Auto<OpenAfter> xaoa_variate_doc([]() {
	xll::Documentation("VARIATE", R"(
Random variates.
)");
	return TRUE;
});
#endif


static AddIn xai_variate_affine(
	Function(XLL_HANDLE, "xll_variate_affine", "\\VARIATE.AFFINE")
	.Arguments({
		Arg(XLL_HANDLE, "h", "is a handle to a variate.", "\"=\\VARIATE.LOGISTIC(1,1)\""),
		Arg(XLL_DOUBLE, "mu", "is the location parameter.", "0"),
		Arg(XLL_DOUBLE, "sigma", "is the scale parameter. Default is 1.", "1"),
		})
	.Uncalced()
	.FunctionHelp("Return a handle to the variate μ + σX.")
	.Category(XLL_CATEGORY)
	.Documentation(affine_doc)
);
HANDLEX WINAPI xll_variate_affine(HANDLEX h, double a, double b)
{
#pragma XLLEXPORT
	HANDLEX hab = INVALID_HANDLEX;

	try {
		handle<variate_base<>> h_(h);
		ensure(h_);
		handle<variate_base<>> v(new variate_handle(affine(*h_.ptr(), a, b)));
		hab = v.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return hab;
}

static AddIn xai_variate_normalize(
	Function(XLL_HANDLE, "xll_variate_normalize", "\\VARIATE.NORMALIZE")
	.Arguments({
		Arg(XLL_HANDLE, "h", "is a handle to a variate.", "\"=\\VARIATE.LOGISTIC(1,1)\""),
		})
	.Uncalced()
	.FunctionHelp("Return a handle to the variate normalized to mean 0 and variance 1.")
	.Category(XLL_CATEGORY)
	.Documentation(R"(Call <c>\\VARIATE.AFFINE</c> to return \((X - \mu)/\sigma\)
where \(\mu\) is the mean and \(\sigma\) is the standard deviation of \(X\).
)")
);
HANDLEX WINAPI xll_variate_normalize(HANDLEX h)
{
#pragma XLLEXPORT
	HANDLEX _h = INVALID_HANDLEX;

	try {
		handle<variate_base<>> h_(h);
		ensure(h_);
		double m = h_->cumulant(0, 1);  // mean
		double s = sqrt(h_->cumulant(0, 2)); // standard deviation
		handle<variate_base<>> v(new variate_handle(affine(*h_.ptr(), -m/s, 1/s)));
		_h = v.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return _h;
}

static AddIn xai_variate_cdf(
	Function(XLL_DOUBLE, "xll_variate_cdf", "VARIATE.CDF")
	.Arguments({
		Arg(XLL_HANDLE, "m", "is a handle to the variate", "\"=\\VARIATE.NORMAL(0,1)\""),
		Arg(XLL_DOUBLE, "x", "is the value", "0"),
		Arg(XLL_DOUBLE, "s", "is the Esscher transform parameter. Default is 0.", "0"),
		Arg(XLL_WORD, "n", "is the derivative. Default is 0.", "0")
		})
	.FunctionHelp("Return the n-th derivative of the transformed cumulative distribution function at x.")
	.Category(XLL_CATEGORY)
	.Documentation(cdf_doc)
);
double WINAPI xll_variate_cdf(HANDLEX m, double x, double s, WORD n)
{
#pragma XLLEXPORT
	double result = XLL_NAN;

	try {
		handle<variate_base<>> m_(m);
		ensure(m_);
		result = m_->cdf(x, s, n);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

static AddIn xai_variate_pdf(
	Function(XLL_DOUBLE, "xll_variate_pdf", "VARIATE.PDF")
	.Arguments({
		Arg(XLL_HANDLE, "m", "is a handle to the variate.", "\"=\\VARIATE.NORMAL(0,1)\""),
		Arg(XLL_DOUBLE, "x", "is the value.", "0"),
		Arg(XLL_DOUBLE, "s", "is the Esscher transform parameter. Default is 0.", "0"),
		})
	.FunctionHelp("Return the transformed probability density at x.")
	.Category(XLL_CATEGORY)
	.Documentation(R"(
The probability density function is the derivative of the
cumulative distribution function.
)")
);
double WINAPI xll_variate_pdf(HANDLEX m, double x, double s)
{
#pragma XLLEXPORT
	double result = XLL_NAN;

	try {
		handle<variate_base<>> m_(m);
		ensure(m_);
		result = m_->cdf(x, s, 1);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

static AddIn xai_variate_cumulant(
	Function(XLL_DOUBLE, "xll_variate_cumulant", "VARIATE.CUMULANT")
	.Arguments({
		Arg(XLL_HANDLE, "m", "is a handle to the variate.", "\"=\\VARIATE.NORMAL(0,1)\""),
		Arg(XLL_DOUBLE, "s", "is the value.", "0"),
		Arg(XLL_WORD, "n", "is the derivative. Default is 0.", "0")
		})
	.FunctionHelp("Return n-th derivative of cumulant at s.")
	.Category(XLL_CATEGORY)
	.Documentation(cumulant_doc)
);
double WINAPI xll_variate_cumulant(HANDLEX m, double s, WORD n)
{
#pragma XLLEXPORT
	double result = XLL_NAN;

	try {
		handle<variate_base<>> m_(m);
		ensure(m_);
		result = m_->cumulant(s, n);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

static AddIn xai_variate_edf(
	Function(XLL_DOUBLE, "xll_variate_edf", "VARIATE.EDF")
	.Arguments({
		Arg(XLL_HANDLE, "m", "is a handle to the variate.", "\"=\\VARIATE.NORMAL(0,1)\""),
		Arg(XLL_DOUBLE, "s", "is the Esscher transform parameter. Default is 0.", "0"),
		Arg(XLL_DOUBLE, "x", "is the value.", "0"),
		})
	.FunctionHelp("Return the derivative of the transformed distribution with respect to s.")
	.Category(XLL_CATEGORY)
	.Documentation(edf_doc)
);
double WINAPI xll_variate_edf(HANDLEX m, double s, double x)
{
#pragma XLLEXPORT
	double result = XLL_NAN;

	try {
		handle<variate_base<>> m_(m);
		ensure(m_);
		result = m_->edf(s, x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}
