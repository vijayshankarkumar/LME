#include "Utils/Color.h"

namespace laal {

	Color::Color() :
		m_dRed(1.0f),
		m_dGreen(1.0f),
		m_dBlue(1.0f),
		m_dAlpha(0xff)
	{
	
	}

	Color::Color(double r, double g, double b, double a)
	{
		Clip(r, 0.0, 1.0);
		Clip(g, 0.0, 1.0);
		Clip(b, 0.0, 1.0);
		Clip(a, 0.0, 1.0);
		m_dRed = r;
		m_dGreen = g;
		m_dBlue = b;
		m_dAlpha = a;
	}

	Color::~Color()
	{

	}

	Color::Color(unsigned int hexColor, double a)
	{
		m_dBlue = hexColor & ((1 << 8) - 1);
		m_dBlue /= 255.0;
		hexColor >>= 8;
		m_dGreen = hexColor & ((1 << 8) - 1);
		m_dGreen /= 255.0;
		hexColor >>= 8;
		m_dRed = hexColor & ((1 << 8) - 1);
		m_dRed /= 255.0;
		m_dAlpha = a;
	}

	unsigned int Color::RGB()
	{
		return 
			((unsigned int)(m_dRed * 255.0f)<< 16) +
			((unsigned int)(m_dGreen * 255.0f) << 8) +
			((unsigned int)(m_dBlue * 255.0f));
	}

	unsigned  int Color::RGBA()
	{
		return 
			((unsigned int)(m_dRed * 255.0f) << 24) +
			((unsigned int)(m_dGreen * 255.0f) << 16) +
			((unsigned int)(m_dBlue * 255.0f)<< 8) +
			((unsigned int)(m_dAlpha * 255.0f));
	}

	unsigned  int Color::ARGB()
	{
		return 
			((unsigned int)(m_dAlpha * 255.0f)<< 24) +
			((unsigned int)(m_dRed * 255.0f)<< 16) +
			((unsigned int)(m_dGreen * 255.0f)<< 8) +
			((unsigned int)(255.0f * m_dBlue));
	}

	double Color::Red() const
	{
		return m_dRed;
	}

	double Color::Green() const
	{
		return m_dGreen;
	}

	double Color::Blue() const
	{
		return m_dBlue;
	}

	double Color::Alpha() const
	{
		return m_dAlpha;
	}

	void Color::Red(double r)
	{
		m_dRed = r;
	}

	void Color::Green(double g)
	{
		m_dGreen = g;
	}

	void Color::Blue(double b)
	{
		m_dBlue = b;
	}

	void Color::Alpha(double a)
	{
		m_dAlpha = a;
	}

	void Color::Interpolate(const Color& start, const Color& end, double alpha)
	{
		Clip(alpha, 0.0, 1.0);
		InterpolateDouble(m_dRed, start.m_dRed, end.m_dRed, alpha);
		InterpolateDouble(m_dGreen, start.m_dGreen, end.m_dGreen, alpha);
		InterpolateDouble(m_dBlue, start.m_dBlue, end.m_dBlue, alpha);
		InterpolateDouble(m_dAlpha, start.m_dAlpha, end.m_dAlpha, alpha);
	}
}