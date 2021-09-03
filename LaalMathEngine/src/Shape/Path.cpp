#include "Shape/Path.h"
#include "Math/SimpleFunctions.h"

namespace laal
{
	Path::Path() :
		m_bIsClosed(false),
		m_bIsPartial(false),
		m_nNPPC(4),
		m_dStartAlpha(0.0),
		m_dEndAlpha(1.0),
		m_nLineJoin(JOIN_MITER),
		m_nLineCap(CAP_BUTT),
		m_dMiterLimit(0.01)
	{

	}

	Path::Path(unsigned int size) :
		m_bIsClosed(false),
		m_bIsPartial(false),
		m_nNPPC(4),
		m_dStartAlpha(0.0),
		m_dEndAlpha(1.0),
		m_nLineJoin(JOIN_MITER),
		m_nLineCap(CAP_BUTT),
		m_dMiterLimit(0.01)
	{
		m_Points.resize(size);
	}

	Path::~Path()
	{

	}

	void Path::AddPoint(const Point& point)
	{
		m_Points.push_back(point);
	}

	void Path::AddPoints(const std::vector<Point>& points)
	{
		for (Point point : points)
		{
			m_Points.push_back(point);
		}
	}

	void Path::SetPoints(const std::vector<Point>& points)
	{
		m_Points = points;
	}

	bool Path::IsClosed() const
	{
		return m_bIsClosed;
	}

	bool Path::IsPartial() const
	{
		return m_bIsPartial;
	}

	void Path::Close()
	{
		m_bIsClosed = true;
	}

	void Path::Open()
	{
		m_bIsClosed = false;
	}

	void Path::BecomePartial()
	{
		m_bIsPartial = true;
	}

	void Path::BecomeComplete()
	{
		m_bIsPartial = false;
	}

	void Path::AlphaValue(double t0, double t1)
	{
		m_dStartAlpha = t0;
		m_dEndAlpha = t1;
	}

	std::vector<Point> Path::Points()
	{
		if (m_bIsPartial)
		{
			return PartialPoints(m_dStartAlpha, m_dEndAlpha);
		}
		return m_Points;
	}

	void Path::ApplyFunction(std::function<void(Point&)> func)
	{
		for (Point& point : m_Points)
		{
			func(point);
		}
	}

	void Path::Reset()
	{
		m_Points.clear();
	}

	unsigned int Path::Size() const
	{
		return (unsigned int)m_Points.size();
	}

	Point Path::FirstPoint() const
	{
		return m_Points.front();
	}

	Point Path::LastPoint() const
	{
		return m_Points.back();
	}

	Point Path::MinPoint()
	{
		Point mn = Point(1e9, 1e9, 1e9);
		for (Point& point : m_Points)
		{
			for (int i = 0; i < 3; i++)
			{
				mn[i] = std::min(point[i], mn[i]);
			}
		}
		return mn;
	}

	Point Path::MaxPoint()
	{
		Point mx = Point(-1e9, -1e9, -1e9);
		for (Point& point : m_Points)
		{
			for (int i = 0; i < 3; i++)
			{
				mx[i] = std::max(point[i], mx[i]);
			}
		}
		return mx;
	}

	//TODO reconstruct this function to reduce ambliguity.
	std::vector<Point> Path::PartialPoints(double t0, double t1)
	{
		Clip(t0, 0.0, 1.0);
		Clip(t1, 0.0, 1.0);
		if (t0 > t1)
		{
			std::swap(t0, t1);
		}

		std::vector<Point> points;

		double numCurves = (Size() / (m_nNPPC - 1)) - 1.0;
		if (m_Points.empty())
		{
			return points;
		}
		int lowerIdx = (int)(numCurves * t0);
		int upperIdx = (int)(numCurves * t1);
		//std::cout << "lowerIdx => " << lowerIdx << std::endl;
		//std::cout << "upperIdx => " << upperIdx << std::endl;

		double lowerRem = (numCurves * t0) - lowerIdx;
		double upperRem = (numCurves * t1) - upperIdx;
		std::vector<Point> partialPoints;
		unsigned int idx;
		if (lowerIdx == upperIdx)
		{
			idx = lowerIdx * (m_nNPPC - 1);
			partialPoints = PartialCubicBezierPoints(m_Points[idx], m_Points[idx + 1], m_Points[idx + 2], m_Points[idx + 3], t0, t1);
			for (Point point : partialPoints)
			{
				points.push_back(point);
			}
			m_bIsClosed = false;
			return points;

		}

	    idx = lowerIdx * (m_nNPPC - 1);
		partialPoints = PartialCubicBezierPoints(m_Points[idx], m_Points[idx + 1], m_Points[idx + 2], m_Points[idx + 3], lowerRem, 1.0);
		for (Point point : partialPoints)
		{
			points.push_back(point);
		}

		idx = (lowerIdx + 1) * (m_nNPPC - 1);
		if (points.empty())
		{
			points.push_back(m_Points[idx]);
		}
		idx++;
		while (idx <= upperIdx * (m_nNPPC - 1))
		{
			points.push_back(m_Points[idx]);
			idx++;
		}

		idx = upperIdx * (m_nNPPC - 1);
		partialPoints = PartialCubicBezierPoints(m_Points[idx], m_Points[idx + 1], m_Points[idx + 2], m_Points[idx + 3], 0.0, upperRem);
		for (int i = 1; i < partialPoints.size(); i++)
		{
			points.push_back(partialPoints[i]);
		}

		m_bIsClosed = false;
		return points;
	}

	void Path::Interpolate(const Path& start, const Path& end, double alpha)
	{
		for (unsigned int i = 0; i < Size(); i++)
		{
			InterpolatePoint(m_Points[i], start.m_Points[i], end.m_Points[i], alpha);
		}
	}

	void Path::LineJoin(LINE_JOIN lineJoin)
	{
		m_nLineJoin = lineJoin;
	}

	LINE_JOIN Path::LineJoin() const
	{
		return m_nLineJoin;
	}

	void Path::LineCap(LINE_CAP lineCap)
	{
		m_nLineCap = lineCap;
	}

	LINE_CAP Path::LineCap() const
	{
		return m_nLineCap;
	}

	void Path::MiterLimit(double miterLimit)
	{
		m_dMiterLimit = miterLimit;
	}

	double Path::MiterLimit() const
	{
		return m_dMiterLimit;
	}
}