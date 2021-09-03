#ifndef LAAL_SHAPE_GROUP_HPP
#define LAAL_SHAPE_GROUP_HPP

#include <vector>
#include "Shape/Shape.h"

namespace laal
{
	//! ============================================
	//! [ShapeGroup]
	//! ============================================
	class ShapeGroup : public Shape
	{
	public:

		ShapeGroup();

		virtual ~ShapeGroup();

		ShapeGroup(ShapeGroup* shapeGroup);

		ShapeGroup(ShapeGroup* shapeGroup1, ShapeGroup* shapeGroup2);

		ShapeGroup(std::vector<ShapeGroup*> shapeGroups);

		void StrokeGradient(const Color& startColor, const Color& endColor);

		void FillGradient(const Color& startColor, const Color& endColor);
	};
}

#endif // !LAAL_SHAPE_GROUP_HPP
