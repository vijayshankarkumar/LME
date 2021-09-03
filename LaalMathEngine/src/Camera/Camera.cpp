#include "Camera/Camera.h"

namespace laal
{
	Camera::Camera() :
		m_Position(ORIGIN),
		m_dFrameWidth(FRAME_WIDTH),
		m_dFrameHeight(FRAME_HEIGHT),
		m_nPixelWidth(DEFAULT_PIXEL_WIDTH),
		m_nPixelHeight(DEFAULT_PIXEL_HEIGHT)
	{
		InitImage();
		InitContext();
		LoadFont();
	}

	Camera::Camera(double frameWidth, double frameHeight, unsigned int pixelWidth, unsigned int pixelHeight) :
		m_dFrameWidth(frameWidth),
		m_dFrameHeight(frameHeight),
		m_nPixelWidth(pixelWidth),
		m_nPixelHeight(pixelHeight)
	{
		InitImage();
		InitContext();
		LoadFont();
	}

	Camera::~Camera()
	{
		m_Ctx->end();
		delete m_Img;
		delete m_Ctx;
		delete m_CtxText;
	}

	void Camera::InitImage()
	{
		m_Img = new BLImage(m_nPixelWidth, m_nPixelHeight, BL_FORMAT_PRGB32);
	}

	void Camera::InitContext()
	{
		m_Ctx = new BLContext(*m_Img);
		m_Ctx->fillAll();
		m_Ctx->setCompOp(BL_COMP_OP_SRC_OVER);

		double fr = m_nPixelHeight / 2.0;
		double pw = m_nPixelWidth / 2.0;
		double ph = m_nPixelHeight / 2.0;
		BLMatrix2D mat(
			fr, 0.0,
			0.0, -1.0 * fr,
			pw, ph
		);
		m_Ctx->setMatrix(mat);
		m_Ctx->userToMeta();

		m_CtxText = new BLContext(*m_Img);
		m_CtxText->fillAll();
		m_CtxText->setCompOp(BL_COMP_OP_SRC_OVER);
	}

	void Camera::Capture()
	{
		ClearImage();
		std::vector<Shape*> shapes;
		SortedShapes(shapes);
		for (Shape* shape : shapes)
		{
			if (shape->HasText())
			{
				RenderText(shape);
			}
			else {
				RenderShape(shape);
			}
		}
	}

	void Camera::GetImage()
	{
		static int count = 0;
		std::string file = "./TestFrames/frame" + std::to_string(count++) + ".bmp";
		m_Img->writeToFile(file.c_str());
	}

	uint8_t* Camera::ImageData()
	{
		BLImageData data;
		m_Img->getData(&data);
		return (uint8_t*)data.pixelData;
	}

	unsigned int Camera::ImageStride()
	{
		BLImageData data;
		m_Img->getData(&data);
		return (unsigned int)data.stride;
	}

	void Camera::ClearImage()
	{
		uint8_t* data = ImageData();
		uint8_t a = 255;
		uint8_t r = 25;
		uint8_t g = 25;
		uint8_t b = 25;
		for (unsigned int idx = 0; idx < m_nPixelWidth * m_nPixelHeight * 4; idx++)
		{
			switch (idx % 4)
			{
			case 3:
				data[idx] = a;
				break;
				
			case 2:
				data[idx] = r;
				break;

			case 1:
				data[idx] = g;
				break;

			case 0:
				data[idx] = b;
				break;

			default:
				break;
			}
		}
	}

	double Camera::FrameWidth() const
	{
		return m_dFrameWidth;
	}

	double Camera::FrameHeight() const
	{
		return m_dFrameHeight;
	}

	unsigned int Camera::PixelWidth() const
	{
		return m_nPixelWidth;
	}

	unsigned int Camera::PixelHeight() const
	{
		return m_nPixelHeight;
	}

	void Camera::RenderShape(Shape* shape)
	{
		SetStrokeStyle(shape, m_Ctx);
		SetFillStyle(shape, m_Ctx);
		SetPath(shape);
	}

	void Camera::SetStrokeStyle(Shape* shape, BLContext* ctx)
	{
		Style strokeStyle = shape->GetStrokeStyle();

		switch (strokeStyle.FillRule())
		{

		case FILL_RULE_NONEZERO:
			ctx->setFillRule(BL_FILL_RULE_NON_ZERO);
			break;

		case FILL_RULE_EVENODD:
			ctx->setFillRule(BL_FILL_RULE_EVEN_ODD);
			break;

		default:
			break;
		}

		switch (strokeStyle.StyleType())
		{

		case STYLE_NONE:
		{
			Color color = strokeStyle.GetColor();
			color.Alpha(0.0);
			ctx->setStrokeStyle(BLRgba32(color.ARGB()));
			break;
		}

		case STYLE_FILL_COLOR:
		{
			Color color = strokeStyle.GetColor();
			color.Alpha(strokeStyle.Opacity());
			ctx->setStrokeStyle(BLRgba32(color.ARGB()));
			break;
		}
		case STYLE_LINEAR_GRADIENT:
		{
			LinearGradient lg = strokeStyle.GetLinearGradient();
			BLGradient linear(BLLinearGradientValues(lg.X0(), lg.Y0(), lg.X1(), lg.Y1()));
			for (std::pair<double, Color> stop : lg.Stops())
			{
				linear.addStop(stop.first, BLRgba32(stop.second.ARGB()));
			}

			switch (lg.SpreadType())
			{

			case SPREAD_PAD:
				linear.setExtendMode(BL_EXTEND_MODE_PAD);
				break;

			case SPREAD_REFLECT:
				linear.setExtendMode(BL_EXTEND_MODE_REFLECT);
				break;

			case SPREAD_REPEAT:
				linear.setExtendMode(BL_EXTEND_MODE_REPEAT);
				break;

			default:
				break;
			}
			ctx->setStrokeStyle(linear);
			break;
		}
		case STYLE_RADIAL_GRADIENT:
		{
			RadialGradient rg = strokeStyle.GetRadialGradient();
			BLGradient radial(BLRadialGradientValues(rg.X0(), rg.Y0(), rg.X1(), rg.Y1(), rg.R()));
			for (std::pair<double, Color> stop : rg.Stops())
			{
				radial.addStop(stop.first, BLRgba32(stop.second.ARGB()));
			}

			switch (rg.SpreadType())
			{

			case SPREAD_PAD:
				radial.setExtendMode(BL_EXTEND_MODE_PAD);
				break;

			case SPREAD_REFLECT:
				radial.setExtendMode(BL_EXTEND_MODE_REFLECT);
				break;

			case SPREAD_REPEAT:
				radial.setExtendMode(BL_EXTEND_MODE_REPEAT);
				break;

			default:
				break;
			}
			ctx->setStrokeStyle(radial);
			break;
		}
		default:
			break;
		}

		double strokeWidth = shape->StrokeWidth();
		strokeWidth /= m_nPixelHeight;
		ctx->setStrokeWidth(strokeWidth);
	}

	void Camera::SetFillStyle(Shape* shape, BLContext* ctx)
	{
		Style fillStyle = shape->GetFillStyle();

		switch (fillStyle.FillRule())
		{

		case FILL_RULE_NONEZERO:
			ctx->setFillRule(BL_FILL_RULE_NON_ZERO);
			break;

		case FILL_RULE_EVENODD:
			ctx->setFillRule(BL_FILL_RULE_EVEN_ODD);
			break;

		default:
			break;
		}

		switch (fillStyle.StyleType())
		{

		case STYLE_NONE:
		{
			Color color = fillStyle.GetColor();
			color.Alpha(0.0);
			ctx->setFillStyle(BLRgba32(color.ARGB()));
			break;
		}

		case STYLE_FILL_COLOR:
		{
			Color color = fillStyle.GetColor();
			color.Alpha(fillStyle.Opacity());
			ctx->setFillStyle(BLRgba32(color.ARGB()));
			break;
		}
		case STYLE_LINEAR_GRADIENT:
		{
			LinearGradient lg = fillStyle.GetLinearGradient();
			BLGradient linear(BLLinearGradientValues(lg.X0(), lg.Y0(), lg.X1(), lg.Y1()));
			for (std::pair<double, Color> stop : lg.Stops())
			{
				linear.addStop(stop.first, BLRgba32(stop.second.ARGB()));
			}

			switch (lg.SpreadType())
			{

			case SPREAD_PAD:
				linear.setExtendMode(BL_EXTEND_MODE_PAD);
				break;

			case SPREAD_REFLECT:
				linear.setExtendMode(BL_EXTEND_MODE_REFLECT);
				break;

			case SPREAD_REPEAT:
				linear.setExtendMode(BL_EXTEND_MODE_REPEAT);
				break;

			default:
				break;
			}
			ctx->setFillStyle(linear);
			break;
		}
		case STYLE_RADIAL_GRADIENT:
		{
			RadialGradient rg = fillStyle.GetRadialGradient();
			//std::cout << rg.X0() << " " << rg.Y0() << " " << rg.X1() << " " << rg.Y1() << " " << rg.R() << std::endl;
			BLGradient radial(BLRadialGradientValues(rg.X0(), rg.Y0(), rg.X1(), rg.Y1(), rg.R()));
			for (std::pair<double, Color> stop : rg.Stops())
			{
				//std::cout << stop.first << " -> " << stop.second.ARGB() << std::endl;
				radial.addStop(stop.first, BLRgba32(stop.second.ARGB()));
			}

			switch (rg.SpreadType())
			{

			case SPREAD_PAD:
				radial.setExtendMode(BL_EXTEND_MODE_PAD);
				break;

			case SPREAD_REFLECT:
				radial.setExtendMode(BL_EXTEND_MODE_REFLECT);
				break;

			case SPREAD_REPEAT:
				radial.setExtendMode(BL_EXTEND_MODE_REPEAT);
				break;

			default:
				break;
			}
			ctx->setFillStyle(radial);
			break;
		}
		default:
			break;
		}
	}

	void Camera::SetPath(Shape* shape)
	{
		std::vector<Path*> paths = shape->Paths();
		for (Path* path : paths)
		{
			BLPath blPath;
			std::vector<Point> points = path->Points();
			blPath.moveTo(points[0][0], points[0][1]);
			for (unsigned int i = 1; i < points.size(); i += 3)
			{
				blPath.cubicTo(points[i][0], points[i][1], points[i + 1][0], points[i + 1][1], points[i + 2][0], points[i + 2][1]);
			}

			switch (path->LineJoin())
			{

			case JOIN_BAVEL:
				m_Ctx->setStrokeJoin(BL_STROKE_JOIN_BEVEL);
				break;

			case JOIN_MITER:
				m_Ctx->setStrokeJoin(BL_STROKE_JOIN_MITER_CLIP);
				break;

			case JOIN_ROUND:
				m_Ctx->setStrokeJoin(BL_STROKE_JOIN_ROUND);
				break;

			default:
				break;
			}

			switch (path->LineCap())
			{

			case CAP_BUTT:
				m_Ctx->setStrokeCaps(BL_STROKE_CAP_BUTT);
				break;

			case CAP_ROUND:
				m_Ctx->setStrokeCaps(BL_STROKE_CAP_ROUND);
				break;

			case CAP_SQUARE:
				m_Ctx->setStrokeCaps(BL_STROKE_CAP_SQUARE);
				break;

			default:
				break;
			}

			if (path->IsClosed())
			{
				blPath.close();
				m_Ctx->fillPath(blPath);
			}
			m_Ctx->strokePath(blPath);
		}
	}

	void Camera::LoadFont()
	{

		BLResult err = m_FontFace.createFromFile("trueType/SourceCodePro-Regular.ttf");
		if (err) {
			printf("Failed to load a font-face (err=%u)\n", err);
			return;
		}
	}

	void Camera::RenderText(Shape* shape)
	{
		SetStrokeStyle(shape, m_CtxText);
		SetFillStyle(shape, m_CtxText);

		std::string str = shape->GetText();
		std::vector<std::vector<char>> text;
		SetText(str, text);

		double fr = (double)m_nPixelHeight / 2.0;
		double ph = (double)m_nPixelHeight / 2.0;
		double pw = (double)m_nPixelWidth / 2.0;

		float fontSize = (float)shape->GetFontSize();

		Point position = shape->Position();
		position *= ph;
		position -= Point(-pw, ph, 0.0);
		position[1] *= -1.0;


		BLFont font;
		font.createFromFace(m_FontFace, fontSize);

		Color color = shape->FillColor();
		color.Alpha(shape->FillOpacity());


		BLFontMetrics fontMatrics = font.metrics();
		BLTextMetrics textMatrics;
		BLGlyphBuffer glyphBuffer;
		BLPoint point(position[0], position[1]);
		for (std::vector<char>& txt : text)
		{
			glyphBuffer.setUtf8Text(&txt[0], txt.size());
			font.shape(glyphBuffer);
			font.getTextMetrics(glyphBuffer, textMatrics);
			point.x = position[0] - (textMatrics.boundingBox.x1 - textMatrics.boundingBox.x0) / 2.0;
			m_CtxText->fillGlyphRun(point, font, glyphBuffer.glyphRun());
			point.y += fontMatrics.ascent + fontMatrics.descent + fontMatrics.lineGap;
		}
	}

	void Camera::SetText(const std::string& str, std::vector<std::vector<char>>& out)
	{
		std::vector<char> txt;
		for (char c : str)
		{
			if (c == '\n')
			{
				out.push_back(txt);
				txt.clear();
			}
			else {
				txt.push_back(c);
			}
		}
		if (!txt.empty())
		{
			out.push_back(txt);
		}
	}

	void Camera::SetRootShape(Shape* root)
	{
		m_RootShape = root;
	}

	Shape* Camera::GetRootShape() const
	{
		return m_RootShape;
	}

	void Camera::SortedShapes(std::vector<Shape*>& out)
	{
		Shape* root = m_RootShape;
		SortedShapes(root, out);
		
		std::sort(out.begin(), out.end());
	}

	void Camera::SortedShapes(Shape* root, std::vector<Shape*>& shapes)
	{
		shapes.push_back(root);
		if (root->IsLeaf())
		{
			return;
		}
		for (Shape* shape : root->ChildShapes())
		{
			SortedShapes(shape, shapes);
		}
	}
}