#ifndef LAAL_SVG_SHAPE_HPP
#define LAAL_SVG_SHAPE_HPP

#include "Shape/Shape.h"
#include "Utils/nanosvg.h"

namespace laal
{
	//! =======================================
	//! [SvgShape]
	//! =======================================
	class SvgShape : public Shape
	{
	protected:


	public:

		SvgShape();

		SvgShape(const std::string& fileName);

		virtual ~SvgShape();

		void InitChildShapes(const std::string& fileName);

		void SetFillStyle(NSVGshape* fromShape, Shape* toShape);

		void SetStrokeStyle(NSVGshape* fromShape, Shape* toShape);

		void SetPath(NSVGshape* fromShape, Shape* toShape);
	};
}

#endif // !LAAL_SVG_SHAPE_HPP
