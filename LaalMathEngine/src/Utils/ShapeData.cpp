#include "Utils/ShapeData.h"

namespace laal
{
	void Path::Append(float x, float y, float z)
	{
		m_Points.push_back(gmtl::Point3f(x, y, z));
	}

	void Path::Append(const gmtl::Point3f& point)
	{
		m_Points.push_back(point);
	}

	void Path::Append(const std::list<gmtl::Point3f>& points)
	{
		for (auto& point : points)
		{
			m_Points.push_back(point);
		}
	}

	void Path::Set(const std::list<gmtl::Point3f>& points)
	{
		m_Points = points;
	}

	void Path::Reset()
	{
		m_Points.clear();
	}

	unsigned int Path::Size() const
	{
		return m_Points.size();
	}

	void Path::Closed(bool isClosed)
	{
		m_bIsClosed = isClosed;
	}

	bool Path::Closed() const
	{
		return m_bIsClosed;
	}

	std::list<gmtl::Point3f>* Path::Points()
	{
		return &m_Points;
	}
}