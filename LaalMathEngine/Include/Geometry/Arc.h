#ifndef LAAL_ARC_HPP
#define LAAL_ARC_HPP

#include "Shape/Shape.h"
#include "Math/SimpleFunctions.h"

namespace laal
{
	//! ============================================
	//! [Arc]
	//! ============================================
	class Arc : public Shape
	{
	protected:

		double m_dRadius;

		int m_nNumComponents;

		double m_dAngle;

		double m_dStartAngle;

	public:

		Arc();

		Arc(double radius, double angle, double startAngle);

		virtual ~Arc();

		void InitPath();

		double Radius() const;

		double Angle() const;

		double StartAngle() const;

		int NumComponents() const;

		double ArcLength() const;
	};

	//! ============================================
	//! [Circle]
	//! ============================================
	
	class Circle : public Arc
	{

	public:

		Circle();

		Circle(double radius);

		virtual ~Circle();
	};

	//! ============================================
	//! [Dot]
	//! ============================================
	class Dot : public Circle
	{
	public:

		Dot();

		Dot(double radius);

		virtual ~Dot();
	};

	//! ============================================
	//! [Ellipse]
	//! ============================================
	class Ellipse : public Circle
	{

	protected:

		double m_dStrechFactor;

	public:

		Ellipse();

		Ellipse(double radius, double strechFactor);

		virtual ~Ellipse();
	};

	class CircularSector : public Arc
	{

	public:

		CircularSector();

		CircularSector(double radius, double angle, double startAngle);

		virtual ~CircularSector();

		void InitPath();
	};

	//! ============================================
	//! [AnnularSector]
	//! ============================================
	class AnnularSector : public Arc
	{

	protected:

		double m_dInnerRadius;

		double m_dOuterRadius;

	public:

		AnnularSector();

		AnnularSector(double innerRadius, double outerRadius, double angle, double startAngle);

		virtual ~AnnularSector();

		void InitPath();

		double InnerRadius() const;

		double OuterRadius() const;
	};

	//! ============================================
	//! [Annulus]
	//! ============================================
	class Annulus : public AnnularSector
	{

	public:

		Annulus();

		Annulus(double innerRadius, double outerRadius);

		virtual ~Annulus();
	};
}

#endif // !LAAL_ARC_HPP
