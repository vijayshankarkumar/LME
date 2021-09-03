#ifndef LAAL_PARAMETRIC_CURVE_HPP
#define LAAL_PARAMETRIC_CURVE_HPP

#include "Shape/Shape.h"
#include "Math/Bezier.h"

namespace laal
{
	//! ============================================
	//! [ParametricCurve]
	//! ============================================
	class ParametricCurve : public Shape
	{
	protected:

		double m_dTMin;
		
		double m_dTMax;

		double m_dStep;

		std::function<double(double)> m_Xt;

		std::function<double(double)> m_Yt;

	public:

		ParametricCurve(std::function<double(double)> xt, std::function<double(double)> yt, double tMin, double tMax);

		virtual ~ParametricCurve();

		void InitPath();

		Point GetPointAtT(double t);
	};

	//! =========================================
	//! [FunctionCurve]
	//! =========================================
	class FunctionCurve : public ParametricCurve
	{

	public:

		FunctionCurve(std::function<double(double)> func, double tMin, double tMax);

		virtual ~FunctionCurve();
	};
}
#endif // !LAAL_PARAMETRIC_CURVE_HPP