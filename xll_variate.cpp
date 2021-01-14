// xll_variate.cpp - random variates
#include "xll_variate.h"

using namespace fms::variate;
using namespace xll;

static AddIn xai_variate_affine(
	Function(XLL_HANDLE, "xll_variate_affine", "VARIATE_AFFINE")
	.Args({
		Arg(XLL_HANDLE, "h", "is a handle to a variate."),
		Arg(XLL_DOUBLE, "mu", "is the location parameter.", "0"),
		Arg(XLL_DOUBLE, "sigma", "is the scale parameter. Default is 1.", "1"),
		})
	.Uncalced()
	.FunctionHelp("Return a handle to the variate mu + sigma X.")
	.Category(XLL_CATEGORY)
	.Documentation(R"xyzyx(
Given a handle to a random variate \(X\) return a new handle to
the random variate \(\mu + \sigma X\).
)xyzyx")
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

static AddIn xai_variate_cdf(
	Function(XLL_DOUBLE, "xll_variate_cdf", "VARIATE.CDF")
	.Args({
		Arg(XLL_HANDLE, "m", "is a handle to the variate"),
		Arg(XLL_DOUBLE, "x", "is the value"),
		Arg(XLL_DOUBLE, "s", "is the Esscher transform parameter. Default is 0."),
		Arg(XLL_WORD, "n", "is the derivative. Default is 0.")
		})
	.FunctionHelp("Return the n-th derivative of the transformed cumulative distribution function at x.")
	.Category(XLL_CATEGORY)
	.Documentation(R"xyzyx(
The <em>Esscher transform</em> of the density function \(f\) of a random variable \(X\) is 
\(f_s(x) = f(x)e^{sX - κ(s)}\) whenever the <a href="VARIATE.CUMULANT.html">cumulant</a> \(κ(s)\) exists.
	)xyzyx")
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
	.Args({
		Arg(XLL_HANDLE, "m", "is a handle to the variate."),
		Arg(XLL_DOUBLE, "x", "is the value."),
		Arg(XLL_DOUBLE, "s", "is the Esscher transform parameter. Default is 0."),
		})
		.FunctionHelp("Return s transformed probability density at x.")
	.Category(XLL_CATEGORY)
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
	.Args({
		Arg(XLL_HANDLE, "m", "is a handle to the variate."),
		Arg(XLL_DOUBLE, "s", "is the value."),
		Arg(XLL_WORD, "n", "is the derivative. Default is 0.")
		})
	.FunctionHelp("Return n-th derivative of cumulant at s.")
	.Category(XLL_CATEGORY)
	.Documentation(R"(
The <em>cumulant</em> of a random variable \(X\) is \(κ(s) = \log(E[e^{sX}])\).
	)")
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
	.Args({
		Arg(XLL_HANDLE, "m", "is a handle to the variate."),
		Arg(XLL_DOUBLE, "x", "is the value."),
		Arg(XLL_DOUBLE, "s", "is the Esscher transform parameter. Default is 0."),
		})
	.FunctionHelp("Return the Esscher distribution at x.")
	.Category(XLL_CATEGORY)
	.Documentation(R"(
The <em>Esscher distribution function</em> is the derivative with respect to <i>s</i>of the Esscher
transform of the cumulative distribution.
)")
);
double WINAPI xll_variate_edf(HANDLEX m, double x, double s)
{
#pragma XLLEXPORT
	double result = XLL_NAN;

	try {
		handle<variate_base<>> m_(m);
		ensure(m_);
		result = m_->edf(x, s);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}
