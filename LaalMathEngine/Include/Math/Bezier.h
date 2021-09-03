#ifndef LAAL_BEZIER_HPP
#define LAAL_BEZIER_HPP

#include "gmtl/gmtl.h"

typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal
{
	void computeControlsPoints(const std::vector<Point>& knots, std::vector<Point>& outP1, std::vector<Point>& outP2);

	void GetFirstControlPoints(std::vector<double>& rhs, std::vector<double>& out);

	std::vector<Point> PartialCubicBezierPoints(const Point& p1, const Point& p2, const Point& p3, const Point& p4, double t0, double t1);
}

#endif // !LAAL_BEZIER_HPP
