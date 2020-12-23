// xll_variate.cpp - random variates
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
	.Documentation(R"xyzyx(
The <em>Esscher transform</em> of the density function <i>f</i> of a random variable <i>X</i> is 
<i>f<sub>s</sub>(<i>x<i>) = <i>f</i>(<i>x</i>)<i>e<i><sup><i> sX</i> - κ(<i>s</i>)</sup>
whenever the <a href="VARIATE.CUMULANT.html">cumulant</a> κ(<i>s</i>) exists.
	)xyzyx")
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
The <em>cumulant</em> of a random variable <i>X</i> is
κ(<i>s</i>) = log(E[<i>e<sup> sX</sup></i>]).
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
