#include "Node/Element.h"

namespace laal
{
	Element::Element() :
		m_lId(-1),
		m_Parent(nullptr),
		m_dWidth(0.0),
		m_dHeight(0.0),
		m_dDepth(0.0),
		m_dBorderWidth(0.0),
		m_dMargin(0.0),
		m_dPadding(0.0),
		m_bHasBackgroundColor(false),
		m_BackgroundColor(BLACK)
	{
		
	}

	Element::~Element()
	{

	}

	std::string Element::NodeType() const
	{
		return "Element";
	}

	bool Element::IsLeaf()
	{
		return m_ChildElements.empty();
	}

	bool Element::Contains(Element* element) const
	{
		return element != nullptr && std::find(m_ChildElements.begin(), m_ChildElements.end(), element) != m_ChildElements.end();
	}

	bool Element::Contains(const std::string& id) const
	{
		for (Element* element : m_ChildElements)
		{
			if (element->m_lId == StringHash(id))
			{
				return true;
			}
		}
		return false;
	}

	bool Element::Contains(long long id) const
	{
		for (Element* element : m_ChildElements)
		{
			if (element->m_lId == id)
			{
				return true;
			}
		}
		return false;
	}

	Element* Element::GetElementById(const std::string& id) const
	{
		for (Element* element : m_ChildElements)
		{
			if (element->m_lId == StringHash(id))
			{
				return element;
			}
		}
		return nullptr;
	}

	void Element::Add(Element* element)
	{
		if (element == nullptr)
		{
			return;
		}
		m_ChildElements.push_back(element);
		element->m_Parent = this;
	}

	void Element::Remove(Element* element)
	{
		if (element == nullptr)
		{
			return;
		}
		if (Contains(element))
		{
			auto it = m_ChildElements.end();
			for (auto itt = m_ChildElements.begin(); itt != m_ChildElements.end(); itt = itt + 1)
			{
				if ((*itt)->m_lId == element->m_lId)
				{
					it = itt;
					break;
				}
			}
			m_ChildElements.erase(it);
			(*it)->m_Parent = nullptr;
		}
	}

	std::vector<Element*> Element::ChildElements() const
	{
		return m_ChildElements;
	}

	void Element::SetShape(Shape* shape)
	{
		if (shape == nullptr)
		{
			return;
		}
		m_Shape = shape;
	}

	Shape* Element::GetShape() const
	{
		return m_Shape;
	}

	Point Element::Position() const
	{
		return m_Position;
	}

	void Element::Translate(double dx, double dy, double dz)
	{
		Translate(Vector(dx, dy, dz));
	}

	void Element::Translate(const Vector& alongVector)
	{
		m_Position += alongVector;
	}

	void Element::MoveTo(double x, double y, double z)
	{
		MoveToAboutPoint(Point(x, y, z), Point(m_Position));
	}

	void Element::MoveTo(const Point& destPoint)
	{
		MoveToAboutPoint(destPoint, Point(m_Position));
	}

	void Element::MoveToAboutPoint(double x, double y, double z, const Point& aboutPoint)
	{
		MoveToAboutPoint(Point(x, y, z), aboutPoint);
	}

	void Element::MoveToAboutPoint(const Point& destPont, const Point& aboutPoint)
	{
		Vector alongVector(destPont[0] - aboutPoint[0], destPont[1] - aboutPoint[1], destPont[2] - aboutPoint[2]);
		Translate(alongVector);

		if (IsLeaf())
		{
			return;
		}

		for (Element* element : m_ChildElements)
		{
			element->MoveToAboutPoint(destPont, aboutPoint);
		}
	}

	void Element::Scale(double scaleFactor)
	{
		Scale(Vector(scaleFactor, scaleFactor, scaleFactor));
	}

	void Element::Scale(double sx, double sy, double sz)
	{
		Scale(Vector(sx, sy, sz));
	}

	void Element::Scale(const Vector& scaleVector)
	{
		m_dWidth *= scaleVector[0];
		m_dHeight *= scaleVector[1];
		m_dDepth *= scaleVector[2];

		if (IsLeaf())
		{
			return;
		}
		for (Element* element : m_ChildElements)
		{
			element->Scale(scaleVector);
		}
	}

	void Element::Strech(double strechFactor, const Vector& axis)
	{
		Scale(Vector(axis[0] == 0.0 ? 1.0 : strechFactor, axis[1] == 0.0 ? 1.0 : strechFactor, axis[2] == 0.0 ? 1.0 : strechFactor));
	}

	void Element::SetStyle(std::string key, any value)
	{

	}

	void Element::SetStyle(Arguments& otherStyle)
	{
		if (otherStyle.Contains("width"))
		{
			Width(otherStyle.Get("width").cast<double>());
		}
		if (otherStyle.Contains("height"))
		{
			Height(otherStyle.Get("height").cast<double>());
		}
		if (otherStyle.Contains("depth"))
		{
			Depth(otherStyle.Get("depth").cast<double>());
		}
		if (otherStyle.Contains("borderwidth"))
		{
			BorderWidth(otherStyle.Get("borderwidth").cast<double>());
		}
		if (otherStyle.Contains("margin"))
		{
			Margin(otherStyle.Get("margin").cast<double>());
		}
		if (otherStyle.Contains("padding"))
		{
			Padding(otherStyle.Get("padding").cast<double>());
		}
		if (otherStyle.Contains("backgroundcolor"))
		{
			BackgroundColor(otherStyle.Get("backgroundcolor").cast<Color>());
		}
		if (otherStyle.Contains("backgroundopacity"))
		{
			BackgroundOpacity(otherStyle.Get("backgroundopacity").cast<double>());
		}
	}

	void Element::BackgroundColor(const Color& color)
	{
		m_bHasBackgroundColor = true;
		m_BackgroundColor = color;
	}

	Color Element::BackgroundColor() const
	{
		return m_BackgroundColor;
	}

	void Element::BackgroundOpacity(double backgroundOpacity)
	{
		m_dBackgroundOpacity = backgroundOpacity;
	}

	double Element::BackgroundOpacity() const
	{
		return m_dBackgroundOpacity;
	}

	void Element::Width(double width)
	{
		Strech(width / m_dWidth, X_AXIS);
	}

	double Element::Width()
	{
		return m_dWidth;
	}

	void Element::Height(double height)
	{
		Strech(height / m_dHeight, Y_AXIS);
	}

	double Element::Height()
	{
		return m_dHeight;
	}

	void Element::Depth(double depth)
	{
		Strech(depth / m_dDepth, Z_AXIS);
	}

	double Element::Depth()
	{
		return m_dDepth;
	}

	void Element::BorderWidth(double borderWidth)
	{
		m_dBorderWidth = borderWidth;
	}

	double Element::BorderWidth() const
	{
		return m_dBorderWidth;
	}

	void Element::Margin(double margin)
	{
		m_dMargin = margin;
	}

	double Element::Margin() const
	{
		return m_dMargin;
	}

	void Element::Padding(double padding)
	{
		m_dPadding = padding;
	}

	double Element::Padding() const
	{
		return m_dPadding;
	}

	void Element::FloatToEdge(const Vector& edge)
	{
		if (m_Parent == nullptr)
		{
			return;
		}
		Point sh(m_Parent->m_dWidth / 2.0, m_Parent->m_dHeight / 2.0, m_Parent->m_dDepth / 2.0);
		Point ll = m_Parent->m_Position - sh;
		Point ul = m_Parent->m_Position + sh;

		if (edge == LEFT)
		{
			double px = ll[0] + m_dWidth / 2.0 + m_dMargin + m_Parent->m_dPadding;
			MoveToAboutPoint(Point(px, m_Position[1], m_Position[2]), m_Position);
		}
		if (edge == RIGHT)
		{
			double px = ul[0] - m_dWidth / 2.0 - m_dMargin - m_Parent->m_dPadding;
			MoveToAboutPoint(Point(px, m_Position[1], m_Position[2]), m_Position);
		}
		if (edge == DOWN)
		{
			double py = ll[1] + m_dHeight / 2.0 + m_dMargin + m_Parent->m_dPadding;
			MoveToAboutPoint(Point(m_Position[0], py, m_Position[2]), m_Position);
		}
		if (edge == UP)
		{
			double py = ul[1] - m_dHeight / 2.0 - m_dMargin - m_Parent->m_dPadding;
			MoveToAboutPoint(Point(m_Position[0], py, m_Position[2]), m_Position);
		}
		if (edge == IN)
		{
			double pz = ll[2] + m_dDepth / 2.0 + m_dMargin + m_Parent->m_dPadding;
			MoveToAboutPoint(Point(m_Position[0], m_Position[1], -pz), m_Position);
		}
		if (edge == OUT)
		{
			double pz = ul[2] - m_dDepth / 2.0 - m_dMargin - m_Parent->m_dPadding;
			MoveToAboutPoint(Point(m_Position[0], m_Position[1], pz), m_Position);
		}
	}

	void Element::FloatLeft()
	{
		FloatToEdge(LEFT);
	}

	void Element::FloatRight()
	{
		FloatToEdge(RIGHT);
	}

	void Element::FloatDown()
	{
		FloatToEdge(DOWN);
	}

	void Element::FloatUp()
	{
		FloatToEdge(UP);
	}

	void Element::FloatIn()
	{
		FloatToEdge(IN);
	}

	void Element::FloatOut()
	{
		FloatToEdge(OUT);
	}

	void Element::FloatNextTo(Element* element, const Vector& edge)
	{
		if (element == nullptr)
		{
			return;
		}
		
		if (edge == LEFT)
		{
			double px = element->m_Position[0] - element->m_dWidth / 2.0 - element->m_dMargin - m_dMargin - m_dWidth / 2.0;
			MoveToAboutPoint(Point(px, element->m_Position[1], element->m_Position[2]), m_Position);
		}
		if (edge == RIGHT)
		{
			double px = element->m_Position[0] + element->m_dWidth / 2.0 + element->m_dMargin + m_dMargin + m_dWidth / 2.0;
			MoveToAboutPoint(Point(px, element->m_Position[1], element->m_Position[2]), m_Position);
		}
		if (edge == DOWN)
		{
			double py = element->m_Position[1] - element->m_dHeight/ 2.0 - element->m_dMargin - m_dMargin - m_dHeight / 2.0;
			MoveToAboutPoint(Point(element->m_Position[0], py, element->m_Position[2]), m_Position);
		}
		if (edge == UP)
		{
			double py = element->m_Position[1] + element->m_dHeight / 2.0 + element->m_dMargin + m_dMargin + m_dHeight / 2.0;
			MoveToAboutPoint(Point(element->m_Position[0], py, element->m_Position[2]), m_Position);
		}
		if (edge == IN)
		{
			double pz = element->m_Position[2] - element->m_dDepth / 2.0 - element->m_dMargin - m_dMargin - m_dDepth / 2.0;
			MoveToAboutPoint(Point(element->m_Position[0], element->m_Position[1], pz), m_Position);
		}
		if (edge == OUT)
		{
			double pz = element->m_Position[2] + element->m_dDepth / 2.0 + element->m_dMargin + m_dMargin + m_dDepth / 2.0;
			MoveToAboutPoint(Point(element->m_Position[0], element->m_Position[1], pz), m_Position);
		}
	}

	void Element::FloatLeftTo(Element* element)
	{
		FloatNextTo(element, LEFT);
	}

	void Element::FloatRightTo(Element* element)
	{
		FloatNextTo(element, RIGHT);
	}

	void Element::FloatDownTo(Element* element)
	{
		FloatNextTo(element, DOWN);
	}

	void Element::FloatUpTo(Element* element)
	{
		FloatNextTo(element, UP);
	}

	void Element::FloatInTo(Element* element)
	{
		FloatNextTo(element, IN);
	}

	void Element::FloatOutTo(Element* element)
	{
		FloatNextTo(element, OUT);
	}
}