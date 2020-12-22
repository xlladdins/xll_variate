// xll_variate.h - Interface class for random variates.
#pragma once
#include "fms_variate/fms_variate.h"

#ifndef XLL_CATEGORY
#define XLL_CATEGORY "XLL"
#endif 

namespace fms::variate {

	// NVI base class for variates
	template<class X = double, class S = X>
	struct variate_base {
		typedef typename X xtype;
		typedef typename S stype;

		variate_base()
		{ }
		variate_base(const variate_base&) = delete;
		variate_base& operator=(const variate_base&) = delete;
		virtual ~variate_base()
		{ }

		// transformed cumulative distribution function and derivatives
		X cdf(X x, S s = 0, size_t n = 0) const
		{
			return cdf_(x, s, n);
		}
		// (d/ds)^n log E[exp(sX)]
		S cumulant(S s, size_t n = 0) const
		{
			return cumulant_(s, n);
		}
		X edf(X x, S s = 0) const
		{
			return edf_(x, s);
		}
	private:
		virtual X cdf_(X x, S s, size_t n) const = 0;
		virtual S cumulant_(S s, size_t n) const = 0;
		virtual X edf_(X x, S s) const = 0;
	};

	// implement for a specific variate model
	template<class M, class X = M::xtype, class S = M::stype>
		requires fms::variate_concept<M>
	class variate_handle : public variate_base<X, S>
	{
		M m;
	public:
		variate_handle(const M& m)
			: m(m)
		{ }
		variate_handle(const variate_handle&) = default;
		variate_handle& operator=(const variate_handle&) = default;
		~variate_handle()
		{ }

		X cdf_(X x, S s = 0, size_t n = 0) const override
		{
			return m.cdf(x, s, n);
		}
		S cumulant_(S s, size_t n = 0) const override
		{
			return m.cumulant(s, n);
		}
		X edf_(X x, S s = 0) const override
		{
			return m.edf(x, s);
		}
	};

}
