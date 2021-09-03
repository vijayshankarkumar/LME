#include "Math/EasingFunctions.h"

namespace laal
{
	double EaseSmooth(double t)
	{
		return t;
	}

	double EaseInSine(double t)
	{
		return 1.0 - gmtl::Math::cos((t * gmtl::Math::PI) / 2.0);
	}

	double EaseOutSine(double t)
	{
		return gmtl::Math::sin((t * gmtl::Math::PI) / 2.0);
	}

	double EaseInOutSine(double t)
	{
		return -(gmtl::Math::cos(gmtl::Math::PI * t) - 1.0) / 2.0;
	}

	double EaseInQuad(double t)
	{
		return t * t;
	}

	double EaseOutQuad(double t)
	{
		return 1.0 - (1.0 - t) * (1.0 - t);
	}

	double EaseInOutQuad(double t)
	{
		return t < 0.5 ? 2.0 * t * t : 1.0 - gmtl::Math::pow(-2.0 * t + 2.0, 2) / 2.0;
	}

	double EaseInCubic(double t)
	{
		return t * t * t;
	}

	double EaseOutCubic(double t)
	{
		return 1.0 - gmtl::Math::pow(1.0 - t, 3);
	}

	double EaseInOutCubic(double t)
	{
		return t < 0.5 ? 4.0 * t * t * t : 1.0 - gmtl::Math::pow(-2.0 * t + 2.0, 3) / 2.0;
	}

	double EaseInQuart(double t)
	{
		return t * t * t * t;
	}

	double EaseOutQuart(double t)
	{
		return 1.0 - gmtl::Math::pow(1.0 - t, 4);
	}

	double EaseInOutQuart(double t)
	{
		return t < 0.5 ? 8.0 * t * t * t * t : 1.0 - gmtl::Math::pow(-2.0 * t + 2.0, 4) / 2.0;
	}

	double EaseInQuint(double t)
	{
		return t * t * t * t * t;
	}

	double EaseOutQuint(double t)
	{
		return gmtl::Math::pow(1.0 - t, 5);
	}

	double EaseInOutQuint(double t)
	{
		return t < 0.5 ? 16.0 * t * t * t * t * t : 1.0 - gmtl::Math::pow(-2.0 * t + 2.0, 5) / 2.0;
	}

	double EaseInExpo(double t)
	{
		return t == 0.0 ? 0.0 : gmtl::Math::pow(2.0, 10.0 * t - 10.0);
	}

	double EaseOutExpo(double t)
	{
		return t == 1.0 ? 1.0 : 1.0 - gmtl::Math::pow(2.0, -10.0 * t);
	}

	double EaseInOutExpo(double t)
	{
		return 
			t == 0.0
			? 0.0
			: t == 1
			? 1.0
			: t < 0.5 ? gmtl::Math::pow(2.0, 20.0 * t - 10.0) / 2.0
			: (2.0 - gmtl::Math::pow(2.0, -20.0 * t + 10.0)) / 2.0;
	}

	double EaseInCirc(double t)
	{
		return 1.0 - gmtl::Math::sqrt(1.0 - gmtl::Math::pow(t, 2));
	}

	double EaseOutCirc(double t)
	{
		return gmtl::Math::sqrt(1.0 - gmtl::Math::pow(t - 1.0, 2));
	}

	double EaseInOutCirc(double t)
	{
		return 
			t < 0.5
			? (1.0 - gmtl::Math::sqrt(1.0 - gmtl::Math::pow(2.0 * t, 2))) / 2.0
			: (gmtl::Math::sqrt(1.0 - gmtl::Math::pow(-2.0 * t + 2.0, 2)) + 1.0) / 2.0;
	}

	double EaseInBack(double t)
	{
		double c1 = 1.70158;
		double c3 = c1 + 1;

		return c3 * t * t * t - c1 * t * t;
	}

	double EaseOutBack(double t)
	{
		double c1 = 1.70158;
		double c3 = c1 + 1;

		return 1.0 + c3 * gmtl::Math::pow(t - 1.0, 3) + c1 * gmtl::Math::pow(t - 1.0, 2);
	}

	double EaseInOutBack(double t)
	{
		double c1 = 1.70158;
		double c2 = c1 * 1.525;

		return 
			t < 0.5
			? (pow(2.0 * t, 2) * ((c2 + 1.0) * 2.0 * t - c2)) / 2.0
			: (pow(2.0 * t - 2.0, 2) * ((c2 + 1.0) * (t * 2.0 - 2.0) + c2) + 2.0) / 2.0;
	}

	double EaseInElastic(double t)
	{
		double c4 = (2.0 * gmtl::Math::PI) / 3.0;

		return 
			t == 0.0
			? 0.0
			: t == 1.0
			? 1.0
			: -1.0 * gmtl::Math::pow(2.0, 10.0 * t - 10.0) * gmtl::Math::sin((t * 10.0 - 10.75) * c4);
	}

	double EaseOutElastic(double t)
	{
		double c4 = (2.0 * gmtl::Math::PI) / 3.0;

		return
			t == 0.0
			? 0.0
			: t == 1.0
			? 1.0
			: gmtl::Math::pow(2.0, -10.0 * t) * gmtl::Math::sin((t * 10.0 - 0.75) * c4) + 1.0;
	}

	double EaseInOutElastic(double t)
	{
		double c5 = (2.0 * gmtl::Math::PI) / 4.5;

		return 
			t == 0.0
			? 0.0
			: t == 1.0
			? 1.0
			: t < 0.5
			? -1.0 * (gmtl::Math::pow(2.0, 20.0 * t - 10.0) * gmtl::Math::sin((20.0 * t - 11.125) * c5)) / 2.0
			: (gmtl::Math::pow(2.0, -20 * t + 10.0) * gmtl::Math::sin((20.0 * t - 11.125) * c5)) / 2.0 + 1.0;
	}

	double EaseInBounce(double t)
	{
		return 1.0 - EaseOutBounce(1.0 - t);
	}

	double EaseOutBounce(double t)
	{
		double n1 = 7.5625;
		double d1 = 2.75;

		if (t < 1.0 / d1) 
		{
			return n1 * t * t;
		}
		else if (t < 2.0 / d1)
		{
			return n1 * (t -= 1.5 / d1) * t + 0.75;
		}
		else if (t < 2.5 / d1)
		{
			return n1 * (t -= 2.25 / d1) * t + 0.9375;
		}
		else 
		{
			return n1 * (t -= 2.625 / d1) * t + 0.984375;
		}
	}

	double EaseInOutBounce(double t)
	{
		return 
			t < 0.5
			? (1.0 - EaseOutBounce(1.0 - 2.0 * t)) / 2.0
			: (1.0 + EaseOutBounce(2.0 * t - 1.0)) / 2.0;
	}
}