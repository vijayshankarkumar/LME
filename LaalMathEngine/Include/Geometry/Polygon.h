#ifndef LAAL_POLYGON_HPP
#define LAAL_POLYGON_HPP

#include "Shape/Shape.h"
#include "Arc.h"
#include "Math/SimpleFunctions.h"

namespace laal
{
	//! ============================================
	//! [Line]
	//! ============================================
	class Line : public Shape
	{

	protected:

		Point m_P1;

		Point m_P2;

	public:

		Line();

		Line(const Point& p0, const Point& p1);

		virtual ~Line();

		double LineLength() const;

		void InitPath();

		void SetP1AsOrigin();

		void SetP2AsOrigin();
	};

	//! ============================================
	//! [RegularPolygon]
	//! ============================================
	class RegularPolygon : public Shape
	{

	protected:

		unsigned int m_nSides;

		double m_dDiagonal;

	public:

		RegularPolygon();

		RegularPolygon(unsigned int sides, double diagonal);

		virtual ~RegularPolygon();

		void InitPath();

		unsigned int Sides() const;

		double Diagonal() const;
	};

	//! ============================================
	//! [Triangle]
	//! ============================================
	class Triangle : public RegularPolygon
	{

	public:

		Triangle();

		Triangle(double sideLength);

		virtual ~Triangle();
	};

	//! ============================================
	//! [Arrow]
	//! ============================================
	class Arrow : public Shape
	{

	protected:

		Point m_P1;

		Point m_P2;

		double m_dTipSize;

		Line m_Line;

		Triangle m_Tip;

	public:

		Arrow();

		Arrow(const Point& p0, const Point& p1);

		virtual ~Arrow();

		void AddLine();

		void AddTip();

		void TipSize(double tipSize);

		double TipSize() const;

		Point StartPoint() const;

		Point EndPoint() const;
	};

	//! ============================================
	//! [DoubleArrow]
	//! ============================================
	class DoubleArrow : public Arrow
	{

	protected:

		Triangle m_Tip1;

	public:

		DoubleArrow();

		DoubleArrow(const Point& p0, const Point& p1);

		~DoubleArrow();

		void AddOtherTip();
	};

	//! ============================================
	//! [Rectangle]
	//! ============================================
	class Rectangle : public RegularPolygon
	{

	public:

		Rectangle();

		Rectangle(double width, double height);

		virtual ~Rectangle();
	};

	//! ============================================
	//! [RoundedRectangle]
	//! ============================================
	class RoundRectangle : public Arc
	{

	protected:

		double m_dRectWidth;

		double m_dRectHeight;

	public:

		RoundRectangle();

		RoundRectangle(double width, double height, double radius);

		virtual ~RoundRectangle();

		void InitPath();
	};
}

#endif // ! LAAL_POLYGON_HPP
