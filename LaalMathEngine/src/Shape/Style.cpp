#include "Shape/Style.h"

namespace laal
{
	Style::Style() :
		m_nStyleType(STYLE_NONE),
		m_nFillRule(FILL_RULE_NONEZERO),
		m_Color(BLACK),
		m_dOpacity(1.0)
	{

	}

	Style::~Style()
	{

	}

	void Style::StyleType(STYLE_TYPE styleType)
	{
		m_nStyleType = styleType;
	}

	STYLE_TYPE Style::StyleType() const
	{
		return m_nStyleType;
	}

	void Style::FillRule(FILL_RULE fillRule)
	{
		m_nFillRule = fillRule;
	}

	FILL_RULE Style::FillRule() const
	{
		return m_nFillRule;
	}

	void Style::SetColor(const Color& color)
	{
		m_Color = color;
		m_nStyleType = STYLE_FILL_COLOR;
	}

	Color Style::GetColor() const
	{
		return m_Color;
	}

	void Style::Opacity(double opacity)
	{
		m_dOpacity = opacity;
	}

	double Style::Opacity() const
	{
		return m_dOpacity;
	}

	void Style::SetLinearGradient(const LinearGradient& linearGradient)
	{
		m_LinearGradient = linearGradient;
		m_nStyleType = STYLE_LINEAR_GRADIENT;
	}

	LinearGradient Style::GetLinearGradient() const
	{
		return m_LinearGradient;
	}

	void Style::SetRadialGradient(const RadialGradient& radialGradient)
	{
		m_RadialGradient = radialGradient;
		m_nStyleType = STYLE_RADIAL_GRADIENT;
	}

	RadialGradient Style::GetRadialGradient() const
	{
		return m_RadialGradient;
	}

	void Style::Interpolate(const Style& start, const Style& end, double alpha) {
		m_Color.Interpolate(start.GetColor(), end.GetColor(), alpha);
		InterpolateDouble(m_dOpacity, start.Opacity(), end.Opacity(), alpha);
	}
}