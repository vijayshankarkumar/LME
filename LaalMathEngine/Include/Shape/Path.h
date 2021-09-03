#ifndef LAAL_PATH_HPP
#define LAAL_PATH_HPP

#include <functional>
#include <gmtl/gmtl.h>

#include "Math/SimpleFunctions.h"
#include "Math/Bezier.h"

typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal
{
	enum LINE_JOIN
	{
		JOIN_MITER = 0,
		JOIN_BAVEL = 1,
		JOIN_ROUND = 2
	};

	enum LINE_CAP
	{
		CAP_BUTT = 0,
		CAP_ROUND = 1,
		CAP_SQUARE = 2
	};

	//! ============================================
	//! [Path]
	//! ============================================
	class Path
	{
	private:

		std::vector<Point> m_Points;

		bool m_bIsClosed;

		bool m_bIsPartial;

		unsigned int m_nNPPC;

		double m_dStartAlpha;

		double m_dEndAlpha;

		LINE_JOIN m_nLineJoin;

		LINE_CAP m_nLineCap;

		double m_dMiterLimit;

	public:

		Path();

		Path(unsigned int size);

		~Path();

		void AddPoint(const Point& point);

		void AddPoints(const std::vector<Point>& points);

		void SetPoints(const std::vector<Point>& points);

		bool IsClosed() const;

		bool IsPartial() const;

		void Close();

		void Open();

		void BecomePartial();

		void BecomeComplete();

		void AlphaValue(double t0, double t1);

		std::vector<Point> Points();

		void ApplyFunction(std::function<void(Point&)> func);

		void Reset();

		unsigned int Size() const;

		Point FirstPoint() const;

		Point LastPoint() const;

		Point MinPoint();

		Point MaxPoint();

		std::vector<Point> PartialPoints(double t0, double t1);

		void Interpolate(const Path& start, const Path& end, double alpha);

		void LineJoin(LINE_JOIN lineJoin);

		LINE_JOIN LineJoin() const;

		void LineCap(LINE_CAP lineCap);

		LINE_CAP LineCap() const;

		void MiterLimit(double miterLimit);

		double MiterLimit() const;
	};
}

#endif // !LAAL_PATH_HPP
