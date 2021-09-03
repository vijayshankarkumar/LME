#include "Shape/SvgShape.h"

namespace laal
{
	SvgShape::SvgShape()
	{

	}

	SvgShape::SvgShape(const std::string& fileName)
	{
		InitChildShapes(fileName);
	}

	SvgShape::~SvgShape()
	{
		for (Shape* shape : m_ChildShapes)
		{
			delete shape;
		}
	}

	void SvgShape::InitChildShapes(const std::string& fileName)
	{
		NSVGimage* image;
		image = nsvgParseFromFile(fileName.c_str(), "px", 96);
		//std::cout << "after the image init..." << std::endl;
		for (NSVGshape* shape = image->shapes; shape != NULL; shape = shape->next) {
			//std::cout << "In ther loop..." << std::endl;
			Shape* childShape = new Shape();
			SetFillStyle(shape, childShape);
			SetStrokeStyle(shape, childShape);
			SetPath(shape, childShape);
			Add(childShape);
		}
		nsvgDelete(image);
	}

	void SvgShape::SetFillStyle(NSVGshape* fromShape, Shape* toShape)
	{
		Style fillStyle;
		switch (fromShape->fill.type)
		{
		case NSVG_PAINT_NONE:
			fillStyle.StyleType(STYLE_NONE);
			break;

		case NSVG_PAINT_COLOR:
		{
			unsigned int color = fromShape->fill.color;
			double r = (double)(color & 255) / 255.0;
			color >>= 8;
			double g = (double)(color & 255) / 255.0;
			color >>= 8;
			double b = (double)(color & 255) / 255.0;
			color >>= 8;
			double a = (double)(color) / 255.0;
			fillStyle.SetColor(Color(r, g, b, a));
			//std::cout << "fill color => " << r << " " << g << " " << b << " " << a << std::endl;
			break; 
		}
		
		case NSVG_PAINT_LINEAR_GRADIENT:
			break;

		case NSVG_PAINT_RADIAL_GRADIENT:
			break;

		default:
			break;
		}

		switch (fromShape->fillRule)
		{
		case NSVG_FILLRULE_EVENODD:
			fillStyle.FillRule(FILL_RULE_EVENODD);
			break;

		case NSVG_FILLRULE_NONZERO:
			fillStyle.FillRule(FILL_RULE_NONEZERO);
			break;

		default:
			break;
		}

		fillStyle.Opacity(fromShape->opacity);
		toShape->SetFillStyle(fillStyle);
	}

	void SvgShape::SetStrokeStyle(NSVGshape* fromShape, Shape* toShape)
	{
		/*switch (fromShape->stroke.type)
		{
		case NSVG_PAINT_NONE:
			toShape->FillType(FILL_NONE);
			break;

		case NSVG_PAINT_COLOR:
			toShape->StrokeColor(fromShape->fill.color);
			break;

		case NSVG_PAINT_LINEAR_GRADIENT:
			break;

		case NSVG_PAINT_RADIAL_GRADIENT:
			break;

		default:
			break;
		}

		switch (fromShape->fillRule)
		{
		case NSVG_FILLRULE_EVENODD:
			toShape->FillRule(FILL_RULE_EVENODD);
			break;

		case NSVG_FILLRULE_NONZERO:
			toShape->FillRule(FILL_RULE_NONEZERO);
			break;

		default:
			break;
		}*/

		if (fromShape->fill.type == NSVG_PAINT_COLOR)
		{
			unsigned int color = fromShape->fill.color;
			double r = (double)(color & 255) / 255.0;
			color >>= 8;
			double g = (double)(color & 255) / 255.0;
			color >>= 8;
			double b = (double)(color & 255) / 255.0;
			color >>= 8;
			double a = (double)(color) / 255.0;
			toShape->StrokeColor(Color(r, g, b, a));
			//std::cout << "stroke color => " << r << " " << g << " " << b << " " << a << std::endl;
		}

		toShape->StrokeOpacity(fromShape->opacity);
		toShape->StrokeWidth(fromShape->strokeWidth);
		//std::cout << "stroke type => " << fromShape->stroke.type << std::endl;
		//std::cout << "stroke width => " << fromShape->strokeWidth << std::endl;
		
	}

	void SvgShape::SetPath(NSVGshape* fromShape, Shape* toShape)
	{
		for (NSVGpath* path = fromShape->paths; path != NULL; path = path->next) {
			toShape->StartNewPath(Point(path->pts[0], path->pts[1], 0.0));
			for (int i = 0; i < path->npts - 1; i += 3) {
				float* p = &path->pts[i * 2];
				toShape->LastPath()->AddPoint(Point(p[2], p[3], 0.0));
				toShape->LastPath()->AddPoint(Point(p[4], p[5], 0.0));
				toShape->LastPath()->AddPoint(Point(p[6], p[7], 0.0));
			}
			toShape->LastPath()->MiterLimit(fromShape->miterLimit);

			switch (fromShape->strokeLineJoin)
			{
			case NSVG_JOIN_BEVEL:
				toShape->LastPath()->LineJoin(JOIN_BAVEL);
				break;

			case NSVG_JOIN_MITER:
				toShape->LastPath()->LineJoin(JOIN_MITER);
				break;

			case NSVG_JOIN_ROUND:
				toShape->LastPath()->LineJoin(JOIN_ROUND);
				break;

			default:
				break;
			}

			switch (fromShape->strokeLineCap)
			{
			case NSVG_CAP_BUTT:
				toShape->LastPath()->LineCap(CAP_BUTT);
				break;

			case NSVG_CAP_ROUND:
				toShape->LastPath()->LineCap(CAP_ROUND);
				break;

			case NSVG_CAP_SQUARE:
				toShape->LastPath()->LineCap(CAP_SQUARE);
				break;

			default:
				break;
			}
			//std::cout << "path closed flag => " << (int)path->closed << std::endl;
			if ((int)path->closed == 0) {
				toShape->LastPath()->Close();
				//std::cout << "path is closed...." << std::endl;
			}
		}
	}
}