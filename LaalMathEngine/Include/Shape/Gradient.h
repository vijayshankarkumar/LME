#ifndef LAAL_GRADIENT_HPP
#define LAAL_GRADIENT_HPP

#include <vector>
#include <gmtl/gmtl.h>

#include "Utils/Constants.h"

typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal
{
	//! ============================================
	//! [LinearGradient]
	//! ============================================
	enum SPREAD_TYPE
	{
		SPREAD_PAD = 0,
		SPREAD_REFLECT = 1,
		SPREAD_REPEAT = 2
	};

	class LinearGradient
	{

	protected:

		double m_X0;

		double m_Y0;

		double m_X1;

		double m_Y1;

		gmtl::Matrix23f m_Matrix;

		SPREAD_TYPE m_SpreadType;

		std::vector<std::pair<double, Color>> m_Stops;

	public:

		LinearGradient();

		LinearGradient(double x0, double y0, double x1, double y1, SPREAD_TYPE spreadType);

		virtual ~LinearGradient();

		void AddStop(double offset, const Color& color);

		void SetMatrix(const gmtl::Matrix23f& matrix);

		void SpreadType(SPREAD_TYPE spreadType);

		double X0() const;

		double Y0() const;

		double X1() const;

		double Y1() const;

		gmtl::Matrix23f Matrix() const;

		std::vector<std::pair<double, Color>> Stops() const;

		SPREAD_TYPE SpreadType() const;
	};

	//! ============================================
	//! [RadialGradient]
	//! ============================================
	class RadialGradient : public LinearGradient
	{

	protected:

		double m_R;

	public:

		RadialGradient();

		RadialGradient(double x0, double y0, double x1, double y1, double r, SPREAD_TYPE spreadType);

		~RadialGradient();

		double R() const;
	};
}

#endif // !LAAL_GRADIENT_HPP
