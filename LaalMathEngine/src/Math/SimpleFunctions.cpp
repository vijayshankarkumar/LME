#include "Math/SimpleFunctions.h"
#include "Utils/Constants.h"

namespace laal
{
	void Clip(int& value, int lowerBound, int upperBound)
	{
		value = std::min(std::max(value, lowerBound), upperBound);
	}

	void Clip(double& value, const double& lowerBound, const double& upperBound)
	{
		value = std::min(std::max(value, lowerBound), upperBound);
	}

	void Clip(Point& value, const Point& lowerBound, const Point& upperBound)
	{
		for (int i = 0; i < 3; i++)
		{
			Clip(value[i], lowerBound[i], upperBound[i]);
		}
	}

	void Clip(Vector& value, const Vector& lowerBound, const Vector& upperBound)
	{
		for (int i = 0; i < 3; i++)
		{
			Clip(value[i], lowerBound[i], upperBound[i]);
		}
	}

	void Normalize(Vector& vect)
	{
		double dist = Distance(vect, ORIGIN);
		if (dist < -1e8)
		{
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			vect[i] /= dist;
		}
	}

	long long StringHash(const std::string& str)
	{
		long long hash = 0;
		long long primePow = 1;
		long long mod = 1000000007;
		for (int i = 0; i < str.length(); i++)
		{
			hash = (hash + (str[i] + 1) * primePow) % mod;
			primePow = (primePow * 31) % mod;
		}
		return hash;
	}

	std::vector<double> Linspace(double start, double end, int size)
	{
		double delta = (end - start) / (size - 1.0f);
		std::vector<double> res(size);
		for (int i = 0; i < size; i++)
		{
			res[i] = start + delta * i;
		}
		return res;
	}

	std::vector<Point> Linspace(const Point& start, const Point& end, int size)
	{
		std::vector<double> resX = Linspace(start[0], end[0], size);
		std::vector<double> resY = Linspace(start[1], end[1], size);
		std::vector<double> resZ = Linspace(start[2], end[2], size);

		std::vector<Point> res(size);
		for (int i = 0; i < size; i++)
		{
			res[i] = Point(resX[i], resY[i], resZ[i]);
		}
		return res;
	}

	double Distance(const Point& a, const Point& b)
	{
		return gmtl::Math::sqrt(gmtl::Math::sqr(a[0] - b[0]) + gmtl::Math::sqr(a[1] - b[1]) + gmtl::Math::sqr(a[2] - b[2]));
	}

	void InterpolateDouble(double& value, const double& start, const double& end, double alpha)
	{
		Clip(alpha, 0.0, 1.0);
		value = start * (1.0 - alpha) + end * alpha;
	}

	void InterpolatePoint(Point& value, const Point& start, const Point& end, double alpha)
	{
		Clip(alpha, 0.0, 1.0);
		value = start * (1.0 - alpha) + end * alpha;
	}

	double Derivative(std::function<double(double)> func, double atPoint)
	{
		double h = gmtl::Math::sqrt(DBL_EPSILON);
		return (func(atPoint + h) - func(atPoint - h)) / (2.0 * h);
	}

	double Derivative(std::function<double(double)> Xt, std::function<double(double)> Yt, double atPoint)
	{
		return Derivative(Yt, atPoint) / Derivative(Xt, atPoint);
	}
}