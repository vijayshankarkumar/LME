#include "Geometry/Polygon.h"

namespace laal
{
	Line::Line() :
		m_P1(Point(0.0, 0.0, 0.0)),
		m_P2(Point(1.0, 1.0, 0.0))
	{
		InitPath();
	}

	Line::Line(const Point& p1, const Point& p2) :
		m_P1(p1),
		m_P2(p2)
	{
		InitPath();
	}

	Line::~Line()
	{

	}

	double Line::LineLength() const
	{
		return gmtl::Math::sqrt(
			(m_P1[0] - m_P2[0]) * (m_P1[0] - m_P2[0]) +
			(m_P1[1] - m_P2[1]) * (m_P1[1] - m_P2[1]) + 
			(m_P1[2] - m_P2[2]) * (m_P1[2] - m_P2[2])
			);
	}

	void Line::InitPath() {
		StartNewPath(m_P1);
		LineTo(m_P2);

		m_Position = (m_P1 + m_P2) * 0.5;
	}

	void Line::SetP1AsOrigin()
	{
		m_Position = m_P1;
	}

	void Line::SetP2AsOrigin()
	{
		m_Position = m_P1;
	}

	Arrow::Arrow() :
		m_P1(0.0, 0.0, 0.0),
		m_P2(1.0, 0.0, 0.0),
		m_dTipSize(0.02)
	{
		AddLine();
		AddTip();
	}

	Arrow::Arrow(const Point& p0, const Point& p1) :
		m_P1(p0),
		m_P2(p1),
		m_dTipSize(0.02)
	{
		AddLine();
		AddTip();
	}

	Arrow::~Arrow()
	{

	}

	void Arrow::AddLine()
	{
		m_Line = Line(m_P1, m_P2);
		m_Line.StrokeWidth(3.0);
		m_Line.StrokeColor(WHITE);
		m_Line.SetP1AsOrigin();
		Add(&m_Line);
	}

	void Arrow::AddTip()
	{
		m_Tip.Scale(m_dTipSize);
		m_Tip.Rotate(-1.0 * gmtl::Math::PI_OVER_2, OUT);
		m_Tip.MoveTo(m_P2);
		m_Tip.StrokeWidth(0);
		m_Tip.FillColor(WHITE);
		m_Tip.NonScalable();
		Add(&m_Tip);
	}

	void Arrow::TipSize(double tipSize)
	{
		m_dTipSize = tipSize;
	}

	double Arrow::TipSize() const
	{
		return m_dTipSize;
	}

	Point Arrow::StartPoint() const
	{
		return m_P1;
	}

	Point Arrow::EndPoint() const
	{
		return m_P2;
	}

	DoubleArrow::DoubleArrow()
	{
		AddOtherTip();
	}

	DoubleArrow::DoubleArrow(const Point& p0, const Point& p1) :
		Arrow(p0, p1)
	{
		AddOtherTip();
	}

	DoubleArrow::~DoubleArrow()
	{

	}

	void DoubleArrow::AddOtherTip()
	{
		m_Tip1.Scale(m_dTipSize);
		m_Tip1.Rotate(gmtl::Math::PI_OVER_2, OUT);
		m_Tip1.MoveTo(m_P1);
		m_Tip1.StrokeWidth(0);
		m_Tip1.FillColor(WHITE);
		m_Tip1.NonScalable();
		Add(&m_Tip1);
	}

	RegularPolygon::RegularPolygon() :
		m_nSides(3)
	{
		InitPath();
	}

	RegularPolygon::RegularPolygon(unsigned int sides, double diagonal) :
		m_nSides(sides),
		m_dDiagonal(diagonal)
	{
		InitPath();
	}

	RegularPolygon::~RegularPolygon() {

	}

	void RegularPolygon::InitPath()
	{
		std::vector<double> angles = Linspace(0.0, gmtl::Math::TWO_PI, m_nSides + 1);
		StartNewPath(Point(1.0, 0.0, 0.0));
		for (unsigned int i = 1; i < m_nSides; i++)
		{
			LineTo(Point(gmtl::Math::cos(angles[i]), gmtl::Math::sin(angles[i]), 0.0));
		}
		ClosePath();
		Scale(m_dDiagonal);
	}

	unsigned int RegularPolygon::Sides() const
	{
		return m_nSides;
	}

	double RegularPolygon::Diagonal() const {
		return m_dDiagonal;
	}

	Triangle::Triangle() :
		RegularPolygon(3, 1.0)
	{
		Rotate(gmtl::Math::PI_OVER_2, OUT);
	}

	Triangle::Triangle(double sideLength) :
		RegularPolygon(3, sideLength / gmtl::Math::cos(gmtl::Math::PI / 6.0))
	{
		Rotate(gmtl::Math::PI_OVER_2, OUT);
	}

	Triangle::~Triangle()
	{

	}

	Rectangle::Rectangle() :
		RegularPolygon(4, 1.0)
	{
		Rotate(gmtl::Math::PI_OVER_4, OUT);
	}

	Rectangle::Rectangle(double width, double height) :
		RegularPolygon(4, 1.0)
	{
		Rotate(gmtl::Math::PI_OVER_4, OUT);
		std::cout << Width() << "--" << Height() << std::endl;
		Scale(width / Width(), height / Height(), 1.0);
	}

	Rectangle::~Rectangle()
	{

	}

	RoundRectangle::RoundRectangle() :
		m_dRectWidth(1.0f),
		m_dRectHeight(1.0f),
		Arc(0.5f, gmtl::Math::PI_OVER_2, 0.0)
	{
		InitPath();
	}

	RoundRectangle::RoundRectangle(double width, double height, double radius) :
		m_dRectWidth(width),
		m_dRectHeight(height),
		Arc(std::min(radius, std::min(width / 2.0, height / 2.0)), gmtl::Math::PI_OVER_2, 0.0)
	{
		InitPath();
	}

	RoundRectangle::~RoundRectangle()
	{

	}

	void RoundRectangle::InitPath()
	{
		Point tr(1.0 * (m_dRectWidth / 2.0), 1.0 * (m_dRectHeight / 2.0), 0.0);
		Point tl(-1.0 * (m_dRectWidth / 2.0), 1.0 * (m_dRectHeight / 2.0), 0.0);
		Point bl(-1.0 * (m_dRectWidth / 2.0), -1.0 * (m_dRectHeight / 2.0), 0.0);
		Point br(1.0 * (m_dRectWidth / 2.0), -1.0 * (m_dRectHeight / 2.0), 0.0);

		Translate(Point(tr[0] - m_dRadius, tr[1] - m_dRadius, tr[2]));
		m_Position = ORIGIN;

		std::vector<Point> points = LastPath()->Points();

		LineTo(Point(tl[0] + m_dRadius, tl[1], 0.0));
		for (int i = (int)points.size() - 2; i >= 0; i--)
		{
			LastPath()->AddPoint((Point(-1.0 * points[i][0], points[i][1], points[i][2])));
		}
		LineTo(Point(bl[0], bl[1] + m_dRadius, bl[2]));
		for (int i = 1; i < (int)points.size(); i++)
		{
			LastPath()->AddPoint((Point(-1.0 * points[i][0], -1.0f * points[i][1], points[i][2])));
		}
		LineTo(Point(br[0] - m_dRadius, br[1], br[2]));
		for (int i = (int)points.size() - 2; i >= 0; i--)
		{
			LastPath()->AddPoint((Point(points[i][0], -1.0f * points[i][1], points[i][2])));
		}
		ClosePath();
	}
}