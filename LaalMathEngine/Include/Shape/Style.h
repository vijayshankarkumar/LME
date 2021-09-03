#ifndef LAAL_STYLE_HPP
#define LAAL_STYLE_HPP

#include "Shape/Gradient.h"

namespace laal
{
	//! =========================================
	//! [Style]
	//! =========================================
	enum STYLE_TYPE
	{
		STYLE_NONE = 0,
		STYLE_FILL_COLOR = 1,
		STYLE_LINEAR_GRADIENT = 2,
		STYLE_RADIAL_GRADIENT = 3,
		STYLE_PATTERN = 4
	};

	enum FILL_RULE
	{
		FILL_RULE_NONEZERO = 0,
		FILL_RULE_EVENODD = 1
	};

	class Style
	{
	protected:

		STYLE_TYPE m_nStyleType;

		FILL_RULE m_nFillRule;
		
		Color m_Color;
		
		double m_dOpacity;

		LinearGradient m_LinearGradient;

		RadialGradient m_RadialGradient;

	public:

		Style();

		~Style();

		void StyleType(STYLE_TYPE styleType);

		STYLE_TYPE StyleType() const;

		void FillRule(FILL_RULE fillRule);

		FILL_RULE FillRule() const;
		
		void SetColor(const Color& color);

		Color GetColor() const;

		void Opacity(double opacity);

		double Opacity() const;

		void SetLinearGradient(const LinearGradient& linearGradient);

		LinearGradient GetLinearGradient() const;

		void SetRadialGradient(const RadialGradient& radialGradient);

		RadialGradient GetRadialGradient() const;

		void Interpolate(const Style& start, const Style& end, double alpha);
	};
}

#endif // !STYLE_H
