// xll_variate.cpp - random variates
#include "xll/xll/xll.h"
#include "xll_variate.h"

using namespace fms::variate;
using namespace xll;

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
	.Documentation(R"(
If \(f\) is the density function of a random variable \(X\) then \(f_s(x) = f(x)\exp(s X - \kappa(s))\) is
its <em>Esscher transform</em>.
	)")
);
double WINAPI xll_variate_cdf(HANDLEX m, double x, double s, WORD n)
{
#pragma XLLEXPORT
	handle<variate_base<>> m_(m);

	try {
		if (m_) {
			return m_->cdf(x, s, n);
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return XLL_NAN;
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
	handle<variate_base<>> m_(m);

	try {
		if (m_) {
			return m_->cdf(x, s, 1);
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return XLL_NAN;
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
The <em>cumulant</em> of a random variable <math>X</math> is
<math>κ(s) = log(E[e<sup>s X</sup>)])</math>.
	)")
);
double WINAPI xll_variate_cumulant(HANDLEX m, double s, WORD n)
{
#pragma XLLEXPORT
	handle<variate_base<>> m_(m);

	try {
		if (m_) {
			return m_->cumulant(s, n);
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return XLL_NAN;
}

static AddIn xai_variate_edf(
	Function(XLL_DOUBLE, "xll_variate_edf", "VARIATE.EDF")
	.Args({
		Arg(XLL_HANDLE, "m", "is a handle to the variate."),
		Arg(XLL_DOUBLE, "x", "is the value."),
		Arg(XLL_DOUBLE, "s", "is the Esscher transform parameter. Default is 0."),
		})
		.FunctionHelp("Return s transformed probability density at x.")
	.Category(XLL_CATEGORY)
);
double WINAPI xll_variate_edf(HANDLEX m, double x, double s)
{
#pragma XLLEXPORT
	handle<variate_base<>> m_(m);

	try {
		if (m_) {
			return m_->edf(x, s);
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return XLL_NAN;
}
