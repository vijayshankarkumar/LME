#ifndef LAAL_ELEMENT_NODE_HPP
#define LAAL_ELEMENT_NODE_HPP

#include <vector>
#include <list>
#include <string>
#include <functional>
#include <gmtl/gmtl.h>

#include "Utils/Arguments.h"
#include "Math/SimpleFunctions.h"
#include "Utils/Color.h"
#include "Shape/Shape.h"
#include "Node/Node.h"

typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal
{
	//! =======================================
	//! [Element]
	//! =======================================
	
	class Element : public Node
	{
	protected:

		long long m_lId;

		Element* m_Parent;

		std::vector<Element*> m_ChildElements;

		Shape* m_Shape;

		Point m_Position;

		double m_dWidth;

		double m_dHeight;

		double m_dDepth;

		double m_dBorderWidth;

		double m_dMargin;

		double m_dPadding;

		Color m_BackgroundColor;

		double m_dBackgroundOpacity;

		bool m_bHasBackgroundColor;

	public:

		Element();

		virtual ~Element();

		std::string NodeType() const override;

		void Add(Element* node);

		void Remove(Element* node);

		bool IsLeaf() override;

		bool Contains(Element* element) const;

		bool Contains(const std::string& id) const;

		bool Contains(long long id) const;

		std::vector<Element*> ChildElements() const;

		void SetShape(Shape* shape);

		Shape* GetShape() const;

		Element* GetElementById(const std::string& id) const;

		Point Position() const;

		void Translate(double dx, double dy, double dz);

		void Translate(const Vector& alongVector);

		void MoveTo(double x, double y, double z);

		void MoveTo(const Point& destPoint);

		void MoveToAboutPoint(double x, double y, double z, const Point& aboutPoint);

		void MoveToAboutPoint(const Point& destPoint, const Point& aboutPoint);

		void Scale(double scaleFactor);

		void Scale(double sx, double sy, double sz);

		void Scale(const Vector& scaleVector);

		void Strech(double strechFactor, const Vector& axis);

		virtual void SetStyle(std::string key, any value);

		virtual void SetStyle(Arguments& otherStyle);

		void BackgroundColor(const Color& color);

		Color BackgroundColor() const;

		void BackgroundOpacity(double backgroundOpacity);

		double BackgroundOpacity() const;

		void Width(double width);
		
		double Width();

		void Height(double height);

		double Height();

		void Depth(double depth);

		double Depth();

		void BorderWidth(double borderWidth);
		
		double BorderWidth() const;

		void Margin(double margin);

		double Margin() const;

		void Padding(double padding);

		double Padding() const;

		void FloatToEdge(const Vector& edge);

		void FloatLeft();

		void FloatRight();
		
		void FloatDown();
		
		void FloatUp();
		
		void FloatIn();
		
		void FloatOut();
		
		void FloatNextTo(Element* element, const Vector& edge);
		
		void FloatLeftTo(Element* element);
		
		void FloatRightTo(Element* element);
		
		void FloatDownTo(Element* element);
		
		void FloatUpTo(Element* element);
		
		void FloatInTo(Element* element);
		
		void FloatOutTo(Element* element);
	};
}

#endif // !LAAL_ELEMENT_NODE_HPP
