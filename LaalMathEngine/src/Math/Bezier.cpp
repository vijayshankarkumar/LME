#include "Math/Bezier.h"

namespace laal
{
	void computeControlsPoints(const std::vector<Point>& knots, std::vector<Point>& outP1, std::vector<Point>& outP2)
	{
		int n = (int)knots.size() - 1;
		// Calculate first Bezier control points
		// Right hand side vector
		std::vector<double> rhs(n);

		// Set right hand side X values
		for (int i = 1; i < n - 1; ++i)
		{
			rhs[i] = 4.0 * knots[i][0] + 2.0 * knots[i + 1][0];
		}
		rhs[0] = knots[0][0] + 2 * knots[1][0];
		rhs[n - 1] = (8.0 * knots[n - 1][0] + knots[n][0]) / 2.0f;

		// Get first control points X-values
		std::vector<double> x(n);
		GetFirstControlPoints(rhs, x);

		// Set right hand side Y values
		for (int i = 1; i < n - 1; ++i)
		{
			rhs[i] = 4.0 * knots[i][1] + 2.0 * knots[i + 1][1];
		}
		rhs[0] = knots[0][1] + 2.0f * knots[1][1];
		rhs[n - 1] = (8.0 * knots[n - 1][1] + knots[n][1]) / 2.0f;

		// Get first control points Y-values
		std::vector<double> y(n);
		GetFirstControlPoints(rhs, y);

		outP1.resize(n);
		outP2.resize(n);
		for (int i = 0; i < n; ++i)
		{
			// First control point
			outP1[i] = Point(x[i], y[i], 0.0);
			// Second control point
			if (i < n - 1)
				outP2[i] = Point(
					2.0 * knots[i + 1][0] - x[i + 1],
					2.0 * knots[i + 1][1] - y[i + 1],
					0.0
				);
			else
				outP2[i] = Point(
					(knots[n][0] + x[n - 1]) / 2.0,
					(knots[n][1] + y[n - 1]) / 2.0,
					0.0
				);
		}
	}

	void GetFirstControlPoints(std::vector<double>& rhs, std::vector<double>& out) {
		int n = (int)rhs.size();
		// out -> Solution vector.
		std::vector<double> tmp(n); // Temp workspace.

		double b = 2.0;
		out[0] = rhs[0] / b;
		for (int i = 1; i < n; i++) // Decomposition and forward substitution.
		{
			tmp[i] = 1.0 / b;
			b = (i < n - 1 ? 4.0 : 3.5) - tmp[i];
			out[i] = (rhs[i] - out[i - 1]) / b;
		}
		for (int i = 1; i < n; i++)
		{
			out[n - i - 1] -= tmp[n - i] * out[n - i]; // Backsubstitution.
		}
	}

	std::vector<Point> PartialCubicBezierPoints(const Point& P1, const Point& P2, const Point& P3, const Point& P4, double t0, double t1)
	{
		double u0 = 1 - t0;
		double u1 = 1 - t1;
		std::vector<Point> Q(4);
		Q[0] = u0 * u0 * u0 * P1 + (t0 * u0 * u0 + u0 * t0 * u0 + u0 * u0 * t0) * P2 + (t0 * t0 * u0 + u0 * t0 * t0 + t0 * u0 * t0) * P3 + t0 * t0 * t0 * P4;
		Q[1] = u0 * u0 * u1 * P1 + (t0 * u0 * u1 + u0 * t0 * u1 + u0 * u0 * t1) * P2 + (t0 * t0 * u1 + u0 * t0 * t1 + t0 * u0 * t1) * P3 + t0 * t0 * t1 * P4;
		Q[2] = u0 * u1 * u1 * P1 + (t0 * u1 * u1 + u0 * t1 * u1 + u0 * u1 * t1) * P2 + (t0 * t1 * u1 + u0 * t1 * t1 + t0 * u1 * t1) * P3 + t0 * t1 * t1 * P4;
		Q[3] = u1 * u1 * u1 * P1 + (t1 * u1 * u1 + u1 * t1 * u1 + u1 * u1 * t1) * P2 + (t1 * t1 * u1 + u1 * t1 * t1 + t1 * u1 * t1) * P3 + t1 * t1 * t1 * P4; 
		return Q;
	}
}