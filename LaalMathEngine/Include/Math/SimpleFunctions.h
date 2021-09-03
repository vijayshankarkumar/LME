#ifndef LAAL_SIMPLE_FUNCTIONS_HPP
#define LAAL_SIMPLE_FUNCTIONS_HPP

#include <vector>
#include <gmtl/gmtl.h>
#include <functional>

typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal
{
	void Clip(int& value, int lowerBound, int upperBount);

	void Clip(double& value, const double& lowerBound, const double& upperBound);

	void Clip(Point& value, const Point& lowerBound, const Point& upperBound);
	
	void Clip(Vector& value, const Vector& lowerBound, const Vector& upperBound);

	void Normalize(Vector& vect);

	long long StringHash(const std::string& str);

	std::vector<double> Linspace(double start, double end, int size);

	std::vector<Point> Linspace(const Point& start, const Point& end, int size);

	double Distance(const Point& a, const Point& b);

	void InterpolateDouble(double& value, const double& start, const double& end, double alpha);

	void InterpolatePoint(Point& value, const Point& start, const Point& end, double alpha);

	double Derivative(std::function<double(double)> func, double atPoint);

	double Derivative(std::function<double(double)> Xt, std::function<double(double)> Yt, double atPoint);
}

#endif // !LAAL_SIMPLE_FUNCTIONS_HPP
