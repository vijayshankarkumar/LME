#include "Geometry/Arc.h"

namespace laal
{
	Arc::Arc() :
		m_dRadius(1.0),
		m_nNumComponents(4),
		m_dAngle(gmtl::Math::PI_OVER_2),
		m_dStartAngle(0.0)
	{
		InitPath();
	}

	Arc::Arc(double radius, double angle, double startAngle) :
		m_dRadius(radius),
		m_nNumComponents(4), 
		m_dAngle(angle),
		m_dStartAngle(startAngle)
	{
		InitPath();
	}

	Arc::~Arc()
	{

	}

	/*void Arc::InitPoints()
	{
		std::vector<gmtl::Point3f> points;
		std::vector<double> angles = Linspace(m_fStartAngle, m_fStartAngle + m_fAngle, 2 * m_nNumComponents + 1);
		for (double angle : angles)
		{
			points.push_back(gmtl::Point3f(gmtl::Math::cos(angle), gmtl::Math::sin(angle), 0.0f));
		}
		double theta = m_fAngle / m_nNumComponents;
		for (int i = 1; i < (int)points.size(); i += 2)
		{
			points[i] /= gmtl::Math::cos(theta / 2.0f);
		}
		SetPoints(points);
		Scale(m_fRadius);
	}*/

	void Arc::InitPath()
	{
		//std::cout << "In the InitPath of arc" << std::endl;
		std::vector<Point> points;

		double theta = m_dAngle / 4.0;
		double l = (4.0 / 3.0) * gmtl::Math::tan(theta / 4.0);
		double ax = 1.0;
		double ay = 0.0;
		double bx = 1.0;
		double by = l;
		double cx = gmtl::Math::cos(theta) + l * gmtl::Math::sin(theta);
		double cy = gmtl::Math::sin(theta) - l * gmtl::Math::cos(theta);
		double dx = gmtl::Math::cos(theta);
		double dy = gmtl::Math::sin(theta);
		
		std::vector<double> angles = Linspace(m_dStartAngle, m_dStartAngle + m_dAngle, m_nNumComponents + 1);
		
		//std::cout << "before shart new path" << std::endl;
		StartNewPath(Point(
			ax * gmtl::Math::cos(angles[0]) - ay * gmtl::Math::sin(angles[0]),
			ay * gmtl::Math::cos(angles[0]) + ax * gmtl::Math::sin(angles[0]),
			0.0
		));
		//std::cout << "after start new path" << std::endl;
		//std::cout << "number of paths " << NumPaths() << std::endl;

		for (int i = 0; i < m_nNumComponents; i++)
		{
			points.push_back(
				Point(
					bx * gmtl::Math::cos(angles[i]) - by * gmtl::Math::sin(angles[i]), 
					by * gmtl::Math::cos(angles[i]) + bx * gmtl::Math::sin(angles[i]),
					0.0
				)
			);
			points.push_back(
				Point(
					cx * gmtl::Math::cos(angles[i]) - cy * gmtl::Math::sin(angles[i]),
					cy * gmtl::Math::cos(angles[i]) + cx * gmtl::Math::sin(angles[i]),
					0.0
				)
			);
			points.push_back(
				Point(
					dx * gmtl::Math::cos(angles[i]) - dy * gmtl::Math::sin(angles[i]),
					dy * gmtl::Math::cos(angles[i]) + dx * gmtl::Math::sin(angles[i]),
					0.0f
				)
			);
		}
		//std::cout << "after the loop" << std::endl;
		//if (LastPath() == nullptr)
		//{
		//	std::cout << "last path is nullptr" << std::endl;
		//}
		//std::cout << "after the if" << std::endl;
		LastPath()->AddPoints(points);
		//std::cout << "after the add points " << std::endl;
		Scale(m_dRadius);
		//std::cout << "after the scaling" << std::endl;
	}

	double Arc::Radius() const
	{
		return m_dRadius;
	}

	double Arc::Angle() const
	{
		return m_dAngle;
	}

	int Arc::NumComponents() const
	{
		return m_nNumComponents;
	}

	double Arc::ArcLength() const
	{
		return m_dRadius * m_dAngle;
	}

	double Arc::StartAngle() const
	{
		return m_dStartAngle;
	}

	Circle::Circle() : 
		Arc(1.0, gmtl::Math::TWO_PI, 0.0)
	{
		ClosePath();
	}

	Circle::Circle(double radius) :
		Arc(radius, gmtl::Math::TWO_PI, 0.0)
	{
		ClosePath();
	}

	Circle::~Circle()
	{

	}

	Dot::Dot() :
		Circle(0.01)
	{
		NonScalable();
		StrokeWidth(0);
		FillColor(laal::WHITE);
	}

	Dot::Dot(double radius) :
		Circle(radius)
	{
		NonScalable();
		StrokeWidth(0);
		FillColor(laal::WHITE);
	}

	Dot::~Dot()
	{

	}

	Ellipse::Ellipse() : 
		m_dStrechFactor(1.5)
	{
		m_dStrechFactor = 1.5;
		Strech(1.5, X_AXIS);
	}

	Ellipse::Ellipse(double radius, double strechFactor) :
		m_dStrechFactor(strechFactor),
		Circle(radius)
	{
		Strech(strechFactor, X_AXIS);
	}

	Ellipse::~Ellipse()
	{

	}

	CircularSector::CircularSector() :
		Arc(1.0, gmtl::Math::PI_OVER_2, 0.0)
	{
		InitPath();
	}

	CircularSector::CircularSector(double radius, double angle, double startAngle) :
		Arc(radius, angle, startAngle)
	{
		InitPath();
	}

	CircularSector::~CircularSector()
	{

	}

	void CircularSector::InitPath()
	{
		LineTo(Point(0.0, 0.0, 0.0));
		ClosePath();
	}

	AnnularSector::AnnularSector() :
		m_dInnerRadius(1.0),
		m_dOuterRadius(1.2)

	{
		InitPath();
	}

	AnnularSector::AnnularSector(double innerRadius, double outerRadius, double angle, double startAngle) :
		m_dInnerRadius(innerRadius),
		m_dOuterRadius(outerRadius),
		Arc(innerRadius, angle, startAngle)
	{
		InitPath();
	}

	AnnularSector::~AnnularSector()
	{

	}

	void AnnularSector::InitPath()
	{
		std::vector<Point> points = LastPath()->Points();
		for (auto& point : points)
		{
			for (int i = 0; i < 3; i++)
			{
				point[i] *= m_dOuterRadius / m_dInnerRadius;
			}
		}
		std::reverse(points.begin(), points.end());

		LineTo(points.front());
		points.erase(points.begin());
		LastPath()->AddPoints(points);
		ClosePath();
	}

	double AnnularSector::InnerRadius() const
	{
		return m_dInnerRadius;
	}

	double AnnularSector::OuterRadius() const
	{
		return m_dOuterRadius;
	}

	Annulus::Annulus() :
		AnnularSector(1.0, 1.2, gmtl::Math::TWO_PI, 0.0)
	{

	}

	Annulus::Annulus(double innerRadius, double outerRadius) :
		AnnularSector(innerRadius, outerRadius, gmtl::Math::TWO_PI, 0.0)
	{

	}

	Annulus::~Annulus()
	{

	}
}