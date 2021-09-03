#include "Shape/ShapeGroup.h"

namespace laal
{
	ShapeGroup::ShapeGroup()
	{

	}

	ShapeGroup::~ShapeGroup()
	{

	}

	ShapeGroup::ShapeGroup(ShapeGroup* shapeGroup)
	{
		Add(shapeGroup);
	}

	ShapeGroup::ShapeGroup(ShapeGroup* shapeGroup1, ShapeGroup* shapeGroup2)
	{
		Add(shapeGroup1);
		Add(shapeGroup2);
	}

	ShapeGroup::ShapeGroup(std::vector<ShapeGroup*> shapeGroups)
	{
		for (ShapeGroup* shapeGroup : shapeGroups)
		{
			Add(shapeGroup);
		}
	}

	void ShapeGroup::StrokeGradient(const Color& startColor, const Color& endColor)
	{
		Color color;
		double alpha;
		size_t size = m_ChildShapes.size();
		for (size_t i = 0; i < size; i++)
		{
			alpha = (double)i / (double)size;
			color.Interpolate(startColor, endColor, alpha);
			m_ChildShapes[i]->StrokeColor(color);
		}
	}

	void ShapeGroup::FillGradient(const Color& startColor, const Color& endColor)
	{
		Color color;
		double alpha;
		size_t size = m_ChildShapes.size();
		for (size_t i = 0; i < size; i++)
		{
			alpha = (double)i / (double)size;
			color.Interpolate(startColor, endColor, alpha);
			m_ChildShapes[i]->FillColor(color);
		}
	}
}