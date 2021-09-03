#include "Shape/Gradient.h"

namespace laal
{
	LinearGradient::LinearGradient() :
		m_X0(-1.0),
		m_Y0(0.0),
		m_X1(1.0),
		m_Y1(0.0),
		m_SpreadType(SPREAD_PAD)
	{

	}

	LinearGradient::LinearGradient(double x0, double y0, double x1, double y1, SPREAD_TYPE spreadType) :
		m_X0(x0),
		m_Y0(y0),
		m_X1(x1),
		m_Y1(y1),
		m_SpreadType(spreadType)
	{

	}

	LinearGradient::~LinearGradient()
	{

	}

	void LinearGradient::AddStop(double offset, const Color& color)
	{
		m_Stops.push_back(std::make_pair(offset, color));
	}

	void LinearGradient::SetMatrix(const gmtl::Matrix23f& matrix)
	{
		m_Matrix = matrix;
	}

	double LinearGradient::X0() const
	{
		return m_X0;
	}

	double LinearGradient::Y0() const
	{
		return m_Y0;
	}

	double LinearGradient::X1() const
	{
		return m_X1;
	}

	double LinearGradient::Y1() const
	{
		return m_Y1;
	}

	gmtl::Matrix23f LinearGradient::Matrix() const
	{
		return m_Matrix;
	}

	std::vector<std::pair<double, Color>> LinearGradient::Stops() const
	{
		return m_Stops;
	}

	void LinearGradient::SpreadType(SPREAD_TYPE spreadType)
	{
		m_SpreadType = spreadType;
	}

	SPREAD_TYPE LinearGradient::SpreadType() const
	{
		return m_SpreadType;
	}

	RadialGradient::RadialGradient() :
		m_R(0.0f)
	{

	}

	RadialGradient::RadialGradient(double x0, double y0, double x1, double y1, double r, SPREAD_TYPE spreadType) :
		m_R(r),
		LinearGradient(x0, y0, x1, y1, spreadType)
	{

	}

	RadialGradient::~RadialGradient()
	{

	}

	double RadialGradient::R() const
	{
		return m_R;
	}
}