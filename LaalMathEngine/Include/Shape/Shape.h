#ifndef LAAL_SHAPE_HPP
#define LAAL_SHAPE_HPP

#include <vector>
#include <functional>
#include <gmtl/gmtl.h>

#include "Utils/Arguments.h"
#include "Utils/Constants.h"
#include "Shape/Path.h"
#include "Shape/Style.h"


typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal
{
	//! ============================================
	//! [Shape]
	//! ============================================
	class Shape
	{
	protected:

		long long m_lId;

		Shape* m_Parent;

		Point m_Position;

		double m_dWidth;

		double m_dHeight;

		double m_dDepth;

		Point m_Center;

		bool m_bComputeBox;

		std::vector<Path> m_Paths;

		std::vector<Shape*> m_ChildShapes;

		Style m_FillStyle;

		Style m_StrokeStyle;

		double m_dStrokeWidth;

		bool m_bHasStroke;

		unsigned int m_nZIndex;

		std::string m_sText;

		unsigned int m_nFontSize;

		bool m_bHasText;

		Shape* m_StartShape;

		Shape* m_TargetShape;

		bool m_bScalable;

	public:

		Shape();

		~Shape();

		void Id(const std::string& id);

		long long Id() const;

		Shape* GetShapeById(const std::string& id);

		void Add(Shape* shape);

		void Remove(Shape* shape);

		bool Contains(const Shape* shape) const;

		bool Contains(long long id) const;

		bool Contains(const std::string& id) const;

		bool IsLeaf() const;

		std::vector<Shape*> ChildShapes() const;

		void AddPath(const Path& path);

		void StartNewPath(const Point& point);

		void ClosePath();

		unsigned int NumPaths() const;

		Path* LastPath();

		std::vector<Path*> Paths();

		Point Position() const;

		void Position(const Point& position);

		void ApplyPointFunction(std::function<void(Point&)> func, const Point& aboutPoint);

		void Translate(double dx, double dy, double dz);

		void Translate(const Vector& alongVector);

		void TranslateAboutPoint(double dx, double dy, double dz, const Point& aboutPoint);

		void TranslateAboutPoint(const Vector& alongVector, const Point& aboutPoint);

		void MoveTo(double x, double y, double z);

		void MoveTo(const Point& destPoint);

		void MoveToAboutPoint(double x, double y, double z, const Point& aboutPoint);

		void MoveToAboutPoint(const Point& destPoint, const Point& aboutPoint);

		void Scale(double scaleFactor);

		void Scale(double sx, double sy, double sz);

		void Scale(const Vector& scaleVector);

		void ScaleAboutPoint(double scaleFactor, const Point& aboutPoint);

		void ScaleAboutPoint(double sx, double sy, double sz, const Point& aboutPoint);

		void ScaleAboutPoint(const Vector& scaleVector, const Point& aboutPoint);

		void Strech(double strechFactor, const Vector& axis);

		void StrechAboutPoint(double strechFactor, const Vector& axis, const Point& aboutPoint);

		void Rotate(double angle, const Vector& axis);

		void RotateAboutPoint(double angle, const Vector& axis, const Point& aboutPoint);

		void Flip(const Vector& axis);

		void FlipAboutPoint(const Vector& axis, const Point& aboutPoint);

		void ComputeBox();

		Point Center();

		void Width(double width);

		double Width();

		void Height(double height);

		double Height();

		void Depth(double depth);

		double Depth();

		void ToEdge(const Vector& edge);

		void ToLeft();

		void ToRight();

		void ToDown();

		void ToUp();

		void ToIn();

		void ToOut();

		void NextTo(Shape* shape, const Vector& edge);

		void LeftTo(Shape* shape);

		void RightTo(Shape* shape);
		
		void DownTo(Shape* shape);
		
		void UpTo(Shape* shape);

		void InTo(Shape* shape);

		void OutTo(Shape* shape);

		void SetStyle(std::string key, any value);

		void SetStyle(Arguments& otherStyle);

		void SetFillStyle(const Style& style);

		Style GetFillStyle() const;

		void SetStrokeStyle(const Style& style);

		Style GetStrokeStyle() const;

		void FillStyleType(STYLE_TYPE styleType);

		STYLE_TYPE FillStyleType() const;

		void StrokeStyleType(STYLE_TYPE styleType);

		STYLE_TYPE StrokeStyleType() const;

		void FillColor(const Color& color);

		Color FillColor() const;

		void FillOpacity(double fillOpacity);

		double FillOpacity() const;

		void StrokeColor(const Color& strokeColor);

		Color StrokeColor() const;

		void StrokeOpacity(double strokeOpacity);

		double StrokeOpacity() const;

		void StrokeWidth(double strokeWidth);

		double StrokeWidth() const;

		bool HasStroke() const;

		void FillLinearGradient(const LinearGradient& linearGradient);

		LinearGradient FillLinearGradient() const;

		void StrokeLinearGradient(const LinearGradient& linearGradient);

		LinearGradient StrokeLinearGradient() const;

		void FillRadialGradient(const RadialGradient& radialGradient);

		RadialGradient FillRadialGradient() const;

		void StrokeRadialGradient(const RadialGradient& radialGradient);

		RadialGradient StrokeRadialGradient() const;

		void LineTo(const Point& point);

		void AddQuadTo(const Point& p1, const Point& p2);

		void AddCubicTo(const Point& p1, const Point& p2, const Point& p3);

		void Copy(Shape* shape) const;

		void SetStartShape(Shape* startShape);

		Shape* StartShape();

		void SetTargetShape(Shape* targetShape);

		Shape* TargetShape();

		void ZIndex(unsigned int zIndex);

		unsigned int ZIndex() const;

		void ComputeZIndex();

		bool operator<(const Shape* other) const;

		void BecomeStartShape();

		void BecomeTargetShape();

		void BecomeShape(Shape* root);

		std::string GetText() const;

		unsigned int GetFontSize() const;

		bool HasText() const;

		void Scalable();

		void NonScalable();

		void Interpolate(double alpha);
	};
}
#endif // !LAAL_SHAPE_HPP