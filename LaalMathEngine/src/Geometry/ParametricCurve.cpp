#include "Geometry/ParametricCurve.h"

namespace laal
{
	ParametricCurve::ParametricCurve(std::function<double(double)> xt, std::function<double(double)> yt, double tMin, double tMax) :
		m_dTMin(tMin),
		m_dTMax(tMax),
		m_dStep(0.1),
		m_Xt(xt),
		m_Yt(yt)
	{
		InitPath();
	}

	ParametricCurve::~ParametricCurve()
	{

	}

	void ParametricCurve::InitPath()
	{
		std::vector<Point> knots, p1, p2;
		for (double t = m_dTMin; t < m_dTMax; t += m_dStep)
		{
			knots.push_back(GetPointAtT(t));
		}
		knots.push_back(GetPointAtT(m_dTMax));
		
		computeControlsPoints(knots, p1, p2);
		StartNewPath(knots[0]);
		for (int i = 0; i < (int)knots.size() - 1; i++)
		{
			LastPath()->AddPoint(p1[i]);
			LastPath()->AddPoint(p2[i]);
			LastPath()->AddPoint(knots[i + 1]);
		}
	}

	Point ParametricCurve::GetPointAtT(double t)
	{
		return Point(m_Xt(t), m_Yt(t), 0.0);
	}

	FunctionCurve::FunctionCurve(std::function<double(double)> func, double tMin, double tMax) :
		ParametricCurve([](double t) {return t; }, func, tMin, tMax)
	{

	}

	FunctionCurve::~FunctionCurve()
	{

	}
}