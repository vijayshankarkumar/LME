#ifndef SHAPE_DATA_H
#define SHAPE_DATA_H

#include <list>
#include <gmtl/gmtl.h>

namespace laal
{
	//! =========================================
	//! [Path]
	//! =========================================
	class Path
	{

	private:

		std::list<gmtl::Point3f> m_Points;

		bool m_bIsClosed;

	public:

		void Append(float x, float y, float z);

		void Append(const gmtl::Point3f& point);

		void Append(const std::list<gmtl::Point3f>& points);

		void Set(const std::list<gmtl::Point3f>& points);

		void Reset();

		unsigned int Size() const;

		void Closed(bool isClosed);

		bool Closed() const;

		std::list<gmtl::Point3f>* Points();
	};

	enum FILL_TYPE
	{
		FILL_NONE = 0,
		FILL_COLOR = 1,
		FILL_LINEAR = 2,
		FILL_RADIAL = 3
	};

	enum SPREAD_TYPE
	{
		SPREAD_PAD = 0,
		SPREAD_REFLECT = 1,
		SPREAD_REPEAT = 2
	};

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

	enum FILL_RULE
	{
		FILL_RULE_NONEZERO = 0,
		FILL_RULE_EVENODD = 1
	};

	//! =========================================
	//! [Style]
	//! =========================================
	class Style
	{

	};

	//! =========================================
	//! [ShapeData]
	//! =========================================
	class ShapeData
	{

	};
}

#endif // !SHAPE_DATA_H
