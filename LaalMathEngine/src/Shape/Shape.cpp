#include "Shape/Shape.h"

namespace laal
{
	Shape::Shape() :
		m_lId(-1),
		m_Parent(nullptr),
		m_Position(ORIGIN),
		m_dWidth(0.0),
		m_dHeight(0.0),
		m_dDepth(0.0),
		m_Center(ORIGIN),
		m_bComputeBox(true),
		m_dStrokeWidth(DEFAULT_STROKE_WIDTH),
		m_bHasStroke(true),
		m_nZIndex(0),
		m_StartShape(nullptr),
		m_TargetShape(nullptr),
		m_sText(""),
		m_nFontSize(10),
		m_bHasText(false),
		m_bScalable(true)
	{

	}

	Shape::~Shape()
	{

	}

	void Shape::Id(const std::string& id)
	{
		m_lId = StringHash(id);
	}

	long long Shape::Id() const
	{
		return m_lId;
	}

	Shape* Shape::GetShapeById(const std::string& id)
	{
		long long hashId = StringHash(id);
		if (m_lId == hashId)
		{
			return this;
		}

		for (Shape* shape : m_ChildShapes)
		{
			if (shape->GetShapeById(id) != nullptr)
			{
				return shape;
			}
		}
		return nullptr;
	}

	void Shape::Add(Shape* shape)
	{
		if (shape == nullptr)
		{
			return;
		}
		if (std::find(m_ChildShapes.begin(), m_ChildShapes.end(), shape) == m_ChildShapes.end())
		{
			m_ChildShapes.push_back(shape);
			shape->m_Parent = this;
			shape->m_nZIndex = m_nZIndex + 1;
		}
	}

	void Shape::Remove(Shape* shape)
	{
		if (shape == nullptr)
		{
			return;
		}
		auto it = std::find(m_ChildShapes.begin(), m_ChildShapes.end(), shape);
		if (it != m_ChildShapes.end())
		{
			m_ChildShapes.erase(it);
			shape->m_Parent = nullptr;
			shape->m_nZIndex = 0;
		}
	}

	bool Shape::Contains(const Shape* shape) const
	{
		return Contains(shape->m_lId);
	}

	bool Shape::Contains(long long id) const
	{
		for (Shape* childShape : m_ChildShapes)
		{
			if (childShape->m_lId == id)
			{
				return true;
			}
		}
		return false;
	}

	bool Shape::Contains(const std::string& id) const
	{
		return Contains(StringHash(id));
	}

	bool Shape::IsLeaf() const
	{
		return m_ChildShapes.empty();
	}

	std::vector<Shape*> Shape::ChildShapes() const
	{
		return m_ChildShapes;
	}

	void Shape::AddPath(const Path& path)
	{
		m_Paths.push_back(path);
	}

	void Shape::StartNewPath(const Point& point)
	{
		Path path;
		path.AddPoint(point);
		m_Paths.push_back(path);
	}

	void Shape::ClosePath()
	{
		if (NumPaths() == 0)
		{
			return;
		}
		if (Distance(LastPath()->LastPoint(), LastPath()->FirstPoint()) >= TOLERANCE_FOR_POINT_EQUILITY)
		{
			LineTo(LastPath()->FirstPoint());
		}
		m_Paths.back().Close();
	}

	unsigned int Shape::NumPaths() const
	{
		return (unsigned int)m_Paths.size();
	}

	Path* Shape::LastPath()
	{
		if (NumPaths() == 0)
		{
			return nullptr;
		}
		return &(m_Paths.back());
	}

	std::vector<Path*> Shape::Paths()
	{
		std::vector<Path*> res;
		for (Path& path : m_Paths)
		{
			res.push_back(&path);
		}
		return res;
	}

	Point Shape::Position() const
	{
		return m_Position;
	}

	void Shape::Position(const Point& position)
	{
		m_Position = position;
	}

	void Shape::ApplyPointFunction(std::function<void(Point&)> func, const Point& aboutPoint)
	{
		//std::cout << "-------" << std::endl;
		//std::cout << "m_Position -> " << m_Position << std::endl;
		//std::cout << "aboutPoint -> " << aboutPoint << std::endl;
		m_Position -= aboutPoint;
		//std::cout << "m_Position -> " << m_Position << std::endl;
		//std::cout << "aboutPoint -> " << aboutPoint << std::endl;
		func(m_Position);
		//std::cout << "m_Position -> " << m_Position << std::endl;
		//std::cout << "aboutPoint -> " << aboutPoint << std::endl;
		m_Position += aboutPoint;
		//std::cout << "m_Position -> " << m_Position << std::endl;
		//std::cout << "aboutPoint -> " << aboutPoint << std::endl;
		//std::cout << "------" << std::endl;

		auto funcPrev = [&](Point& point)
		{
			point -= aboutPoint;
		};

		auto funcNext = [&](Point& point)
		{
			point += aboutPoint;
		};
		
		for (Path& path : m_Paths)
		{
			path.ApplyFunction(funcPrev);
			path.ApplyFunction(func);
			path.ApplyFunction(funcNext);
		}
	}

	void Shape::Translate(double dx, double dy, double dz)
	{
		TranslateAboutPoint(Vector(dx, dy, dz), Point(m_Position));
	}

	void Shape::Translate(const Vector& alongVector)
	{
		TranslateAboutPoint(alongVector, Point(m_Position));
	}

	void Shape::TranslateAboutPoint(double dx, double dy, double dz, const Point& aboutPoint)
	{
		TranslateAboutPoint(Vector(dx, dy, dz), aboutPoint);
	}

	void Shape::TranslateAboutPoint(const Vector& alongVector, const Point& aboutPoint)
	{
		m_bComputeBox = true;

		auto func = [&](Point& point)
		{
			point += alongVector;
		};
		ApplyPointFunction(func, aboutPoint);

		if (IsLeaf())
		{
			return;
		}

		for (Shape* shape : m_ChildShapes)
		{
			shape->TranslateAboutPoint(alongVector, aboutPoint);
		}
	}

	void Shape::MoveTo(double x, double y, double z)
	{
		MoveToAboutPoint(Point(x, y, z), Point(m_Position));
	}

	void Shape::MoveTo(const Point& destPoint)
	{
		MoveToAboutPoint(destPoint, Point(m_Position));
	}

	void Shape::MoveToAboutPoint(double x, double y, double z, const Point& aboutPoint)
	{
		MoveToAboutPoint(Point(x, y, z), aboutPoint);
	}

	void Shape::MoveToAboutPoint(const Point& destPont, const Point& aboutPoint)
	{
		m_bComputeBox = true;

		Vector alongVector(destPont[0] - aboutPoint[0], destPont[1] - aboutPoint[1], destPont[2] - aboutPoint[2]);
		/*std::cout << "----------" << std::endl;
		std::cout << "destPoint = " << destPont << std::endl;
		std::cout << "aboutPoint = " << aboutPoint << std::endl;
		std::cout << "alongVector = " << alongVector << std::endl;
		std::cout << "----------" << std::endl;*/
		auto func = [&](Point& point)
		{
			point += alongVector;
		};
		ApplyPointFunction(func, aboutPoint);

		if (IsLeaf())
		{
			return;
		}

		for (Shape* shape : m_ChildShapes)
		{
			shape->MoveToAboutPoint(destPont, aboutPoint);
		}
	}

	void Shape::Scale(double scaleFactor)
	{
		ScaleAboutPoint(Vector(scaleFactor, scaleFactor, scaleFactor), Point(m_Position));
	}

	void Shape::Scale(double sx, double sy, double sz)
	{
		ScaleAboutPoint(Vector(sx, sy, sz), Point(m_Position));
	}

	void Shape::Scale(const Vector& scaleVector)
	{
		ScaleAboutPoint(scaleVector, Point(m_Position));
	}

	void Shape::ScaleAboutPoint(double scaleFactor, const Point& aboutPoint)
	{
		ScaleAboutPoint(Vector(scaleFactor, scaleFactor, scaleFactor), aboutPoint);
	}

	void Shape::ScaleAboutPoint(double sx, double sy, double sz, const Point& aboutPoint)
	{
		ScaleAboutPoint(Vector(sx, sy, sz), aboutPoint);
	}

	void Shape::ScaleAboutPoint(const Vector& scaleVector, const Point& aboutPoint)
	{
		if (!m_bScalable)
		{
			m_Position -= aboutPoint;
			Point position;
			for (int i = 0; i < 3; i++)
			{
				position[i] = m_Position[i] * scaleVector[i];
			}
			m_Position += aboutPoint;
			MoveTo(position);
			return;
		}
		m_bComputeBox = true;

		auto func = [&](Point& point)
		{
			for (int i = 0; i < 3; i++)
			{
				point[i] *= scaleVector[i];
			}
		};
		ApplyPointFunction(func, aboutPoint);

		if (IsLeaf())
		{
			return;
		}

		for (Shape* shape : m_ChildShapes)
		{
			shape->ScaleAboutPoint(scaleVector, aboutPoint);
		}
	}

	void Shape::Strech(double strechFactor, const Vector& axis)
	{
		StrechAboutPoint(strechFactor, axis, Point(m_Position));
	}

	void Shape::StrechAboutPoint(double strechFactor, const Vector& axis, const Point& aboutPoint)
	{
		m_bComputeBox = true;
		Vector scaleVector;
		for (int i = 0; i < 3; i++)
		{
			scaleVector[i] = axis[i] == 0.0f ? 1 : strechFactor;
		}
		ScaleAboutPoint(scaleVector, aboutPoint);

		if (IsLeaf())
		{
			return;
		}

		for (Shape* shape : m_ChildShapes)
		{
			shape->StrechAboutPoint(strechFactor, axis, aboutPoint);
		}
	}

	void Shape::Rotate(double angle, const Vector& axis)
	{
		RotateAboutPoint(angle, axis, Point(m_Position));
	}

	void Shape::RotateAboutPoint(double angle, const Vector& axis, const Point& aboutPoint)
	{
		m_bComputeBox = true;

		auto func = [&](Point& point)
		{
			double sinAngle = gmtl::Math::sin(angle / 2.0);
			double cosAngle = gmtl::Math::cos(angle / 2.0);
			gmtl::Quatd quat(axis[0] * sinAngle, axis[1] * sinAngle, axis[2] * sinAngle, cosAngle);
			gmtl::Quatd quatInv = quat;
			gmtl::invert(quatInv);
			gmtl::Quatd pointQuat(point[0], point[1], point[2], 0.0f);
			gmtl::Quatd rotatedQuat = quat * pointQuat * quatInv;
			point[0] = rotatedQuat[0];
			point[1] = rotatedQuat[1];
			point[2] = rotatedQuat[2];
		};
		ApplyPointFunction(func, aboutPoint);

		if (IsLeaf())
		{
			return;
		}

		for (Shape* shape : m_ChildShapes)
		{
			shape->RotateAboutPoint(angle, axis, aboutPoint);
		}
	}

	void Shape::Flip(const Vector& axis)
	{
		Rotate(gmtl::Math::PI, axis);
	}

	void Shape::FlipAboutPoint(const Vector& axis, const Point& aboutPoint)
	{
		RotateAboutPoint(gmtl::Math::PI, axis, aboutPoint);
	}

	void Shape::ComputeBox()
	{
		if (!m_bComputeBox)
		{
			return;
		}
		Point mn = Point(1e9, 1e9, 1e9);
		Point mx = Point(-1e9, -1e9, -1e9);

		for (Path& path : m_Paths)
		{
			Point mnPath = path.MinPoint();
			Point mxPath = path.MaxPoint();
			for (int i = 0; i < 3; i++)
			{
				mn[i] = std::min(mn[i], mnPath[i]);
				mx[i] = std::max(mx[i], mxPath[i]);
			}
		}

		if (IsLeaf())
		{
			m_dWidth = mx[0] - mn[0];
			m_dHeight = mx[1] - mn[1];
			m_dDepth = mx[2] - mn[2];
			m_Center = Point((mn[0] + mx[0]) / 2.0f, (mn[1] + mx[1]) / 2.0f, (mn[2] + mx[2]) / 2.0f);
			m_bComputeBox = false;
			return;
		}
		Point elMn, elMx;
		for (Shape* shape : m_ChildShapes)
		{
			shape->ComputeBox();
			elMn = shape->m_Center - Point(shape->m_dWidth / 2.0f, shape->m_dHeight / 2.0f, shape->m_dDepth / 2.0f);
			elMx = shape->m_Center + Point(shape->m_dWidth / 2.0f, shape->m_dHeight / 2.0f, shape->m_dDepth / 2.0f);
			for (int i = 0; i < 3; i++)
			{
				mn[i] = std::min(mn[i], elMn[i]);
				mx[i] = std::max(mx[i], elMx[i]);
			}
		}
		m_dWidth = mx[0] - mn[0];
		m_dHeight = mx[1] - mn[1];
		m_dDepth = mx[2] - mn[2];
		m_Center = Point((mn[0] + mx[0]) / 2.0f, (mn[1] + mx[1]) / 2.0f, (mn[2] + mx[2]) / 2.0f);
		m_bComputeBox = false;
	}

	Point Shape::Center()
	{
		ComputeBox();
		return m_Center;
	}

	void Shape::Width(double width)
	{
		Strech(width / m_dWidth, X_AXIS);
		m_bComputeBox = true;
	}

	double Shape::Width()
	{
		ComputeBox();
		return m_dWidth;
	}

	void Shape::Height(double height)
	{
		Strech(height / m_dHeight, Y_AXIS);
		m_bComputeBox = true;
	}

	double Shape::Height()
	{
		ComputeBox();
		return m_dHeight;
	}

	void Shape::Depth(double depth)
	{
		Strech(depth / m_dDepth, Z_AXIS);
		m_bComputeBox = true;
	}

	double Shape::Depth()
	{
		ComputeBox();
		return m_dDepth;
	}

	void Shape::ToEdge(const Vector& edge)
	{
		if (m_Parent == nullptr)
		{
			return;
		}
		if (m_Parent->m_bComputeBox)
		{
			m_Parent->ComputeBox();
		}
		if (m_bComputeBox)
		{
			ComputeBox();
		}
		Point sh(m_Parent->m_dWidth / 2.0, m_Parent->m_dHeight / 2.0, m_Parent->m_dDepth / 2.0);
		Point ll = m_Parent->m_Center - sh;
		Point ul = m_Parent->m_Center + sh;

		if (edge == LEFT)
		{
			double px = ll[0] + m_dWidth / 2.0 + (m_dStrokeWidth / 2.0) + (m_Parent->m_dStrokeWidth / 2.0);
			MoveToAboutPoint(Point(px, m_Center[1], m_Center[2]), m_Center);
		}
		if (edge == RIGHT)
		{
			double px = ul[0] - m_dWidth / 2.0 - (m_dStrokeWidth / 2.0) - (m_Parent->m_dStrokeWidth / 2.0);
			MoveToAboutPoint(Point(px, m_Center[1], m_Center[2]), m_Center);
		}
		if (edge == DOWN)
		{
			double py = ll[1] + m_dHeight / 2.0 + (m_dStrokeWidth / 2.0) + (m_Parent->m_dStrokeWidth / 2.0);
			MoveToAboutPoint(Point(m_Center[0], py, m_Center[2]), m_Center);
		}
		if (edge == UP)
		{
			double py = ul[1] - m_dHeight / 2.0 - (m_dStrokeWidth / 2.0) - (m_Parent->m_dStrokeWidth / 2.0);
			MoveToAboutPoint(Point(m_Center[0], py, m_Center[2]), m_Center);
		}
		if (edge == IN)
		{
			double pz = ll[2] + m_dDepth / 2.0 + (m_dStrokeWidth / 2.0) + (m_Parent->m_dStrokeWidth / 2.0);
			MoveToAboutPoint(Point(m_Center[0], m_Center[1], -pz), m_Center);
		}
		if (edge == OUT)
		{
			double pz = ul[2] - m_dDepth / 2.0 - (m_dStrokeWidth / 2.0) - (m_Parent->m_dStrokeWidth / 2.0);
			MoveToAboutPoint(Point(m_Center[0], m_Center[1], pz), m_Center);
		}
		m_bComputeBox = true;
	}

	void Shape::ToLeft()
	{
		ToEdge(LEFT);
	}

	void Shape::ToRight()
	{
		ToEdge(RIGHT);
	}

	void Shape::ToDown()
	{
		ToEdge(DOWN);
	}

	void Shape::ToUp()
	{
		ToEdge(UP);
	}

	void Shape::ToIn()
	{
		ToEdge(IN);
	}

	void Shape::ToOut()
	{
		ToEdge(OUT);
	}

	void Shape::NextTo(Shape* shape, const Vector& edge)
	{
		if (shape == nullptr)
		{
			return;
		}
		if (m_bComputeBox)
		{
			ComputeBox();
		}
		if (shape->m_bComputeBox)
		{
			shape->ComputeBox();
		}

		if (edge == LEFT)
		{
			double px = shape->m_Center[0] - shape->m_dWidth / 2.0 - (shape->m_dStrokeWidth / 2.0) - (m_dStrokeWidth / 2.0) - m_dWidth / 2.0;
			MoveToAboutPoint(Point(px, shape->m_Center[1], shape->m_Center[2]), m_Center);
		}
		if (edge == RIGHT)
		{
			double px = shape->m_Center[0] + shape->m_dWidth / 2.0f + (shape->m_dStrokeWidth / 2.0) + m_dStrokeWidth + m_dWidth / 2.0f;
			MoveToAboutPoint(Point(px, shape->m_Center[1], shape->m_Center[2]), m_Center);
		}
		if (edge == DOWN)
		{
			double py = shape->m_Center[1] - shape->m_dHeight / 2.0f - (shape->m_dStrokeWidth / 2.0) - m_dStrokeWidth - m_dHeight / 2.0f;
			MoveToAboutPoint(Point(shape->m_Center[0], py, shape->m_Center[2]), m_Center);
		}
		if (edge == UP)
		{
			double py = shape->m_Center[1] + shape->m_dHeight / 2.0f + (shape->m_dStrokeWidth / 2.0) + m_dStrokeWidth + m_dHeight / 2.0f;
			MoveToAboutPoint(Point(shape->m_Center[0], py, shape->m_Center[2]), m_Center);
		}
		if (edge == IN)
		{
			double pz = shape->m_Center[2] - shape->m_dDepth / 2.0f - (shape->m_dStrokeWidth / 2.0)- m_dStrokeWidth - m_dDepth / 2.0f;
			MoveToAboutPoint(Point(shape->m_Center[0], shape->m_Center[1], pz), m_Center);
		}
		if (edge == OUT)
		{
			double pz = shape->m_Center[2] + shape->m_dDepth / 2.0f + (shape->m_dStrokeWidth / 2.0 ) + m_dStrokeWidth + m_dDepth / 2.0f;
			MoveToAboutPoint(Point(shape->m_Center[0], shape->m_Center[1], pz), m_Center);
		}
		m_bComputeBox = true;
	}

	void Shape::LeftTo(Shape* shape)
	{
		NextTo(shape, LEFT);
	}

	void Shape::RightTo(Shape* shape)
	{
		NextTo(shape, RIGHT);
	}

	void Shape::DownTo(Shape* shape)
	{
		NextTo(shape, DOWN);
	}

	void Shape::UpTo(Shape* shape)
	{
		NextTo(shape, UP);
	}

	void Shape::InTo(Shape* shape)
	{
		NextTo(shape, IN);
	}

	void Shape::OutTo(Shape* shape)
	{
		NextTo(shape, OUT);
	}

	void Shape::SetStyle(std::string key, any value)
	{
		if (key == "width")
		{
			Width(value.cast<double>());
		}
		if (key == "height")
		{
			Height(value.cast<double>());
		}
		if (key == "depth")
		{
			Depth(value.cast<double>());
		}
		if (key == "fillcolor")
		{
			FillColor(value.cast<Color>());
		}
		if (key == "fillopacity")
		{
			FillOpacity(value.cast<double>());
		}
		if (key == "strokecolor")
		{
			StrokeColor(value.cast<Color>());
		}
		if (key == "strokeopacity")
		{
			StrokeOpacity(value.cast<double>());
		}
		if (key == "strokewidth")
		{
			StrokeWidth(value.cast<double>());
		}
	}

	void Shape::SetStyle(Arguments& otherStyle)
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
		if (otherStyle.Contains("fillcolor"))
		{
			FillColor(otherStyle.Get("fillcolor").cast<Color>());
		}
		if (otherStyle.Contains("fillopacity"))
		{
			FillOpacity(otherStyle.Get("fillopacity").cast<double>());
		}
		if (otherStyle.Contains("strokecolor"))
		{
			StrokeColor(otherStyle.Get("strokecolor").cast<Color>());
		}
		if (otherStyle.Contains("strokeopacity"))
		{
			StrokeOpacity(otherStyle.Get("strokeopacity").cast<double>());
		}
		if (otherStyle.Contains("strokewidth"))
		{
			StrokeWidth(otherStyle.Get("strokewidth").cast<double>());
		}
	}

	void Shape::SetFillStyle(const Style& style)
	{
		m_FillStyle = style;
	}

	Style Shape::GetFillStyle() const
	{
		return m_FillStyle;
	}

	void Shape::SetStrokeStyle(const Style& style)
	{
		m_FillStyle = style;
	}

	Style Shape::GetStrokeStyle() const
	{
		return m_StrokeStyle;
	}

	void Shape::FillStyleType(STYLE_TYPE styleType)
	{
		m_FillStyle.StyleType(styleType);
	}

	STYLE_TYPE Shape::FillStyleType() const
	{
		return m_FillStyle.StyleType();
	}

	void Shape::StrokeStyleType(STYLE_TYPE styleType)
	{
		m_StrokeStyle.StyleType(styleType);
	}

	STYLE_TYPE Shape::StrokeStyleType() const
	{
		return m_StrokeStyle.StyleType();
	}

	void Shape::FillColor(const Color& fillColor)
	{
		m_FillStyle.SetColor(fillColor);
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->FillColor(fillColor);
		}
	}

	Color Shape::FillColor() const
	{
		return m_FillStyle.GetColor();
	}

	void Shape::FillOpacity(double fillOpacity)
	{
		Clip(fillOpacity, 0.0, 1.0);
		m_FillStyle.Opacity(fillOpacity);
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->FillOpacity(fillOpacity);
		}
	}

	double Shape::FillOpacity() const
	{
		return m_FillStyle.Opacity();
	}

	void Shape::StrokeColor(const Color& strokeColor)
	{
		m_StrokeStyle.SetColor(strokeColor);
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->StrokeColor(strokeColor);
		}
	}

	Color Shape::StrokeColor() const
	{
		return m_StrokeStyle.GetColor();
	}

	void Shape::StrokeOpacity(double strokeOpacity)
	{
		Clip(strokeOpacity, 0.0, 1.0);
		m_StrokeStyle.Opacity(strokeOpacity);
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->StrokeOpacity(strokeOpacity);
		}
	}

	double Shape::StrokeOpacity() const
	{
		return m_StrokeStyle.Opacity();
	}

	void Shape::StrokeWidth(double strokeWidth)
	{
		m_bHasStroke = true;
		m_dStrokeWidth = strokeWidth;
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->StrokeWidth(strokeWidth);
		}
	}

	double Shape::StrokeWidth() const
	{
		return m_dStrokeWidth;
	}

	bool Shape::HasStroke() const
	{
		return m_dStrokeWidth > 0.0;
	}

	void Shape::LineTo(const Point& point)
	{
		if (NumPaths() == 0)
		{
			return;
		}
		Path* path = LastPath();
		double px = path->LastPoint()[0];
		double py = path->LastPoint()[1];
		double dx = point[0] - px;
		double dy = point[1] - py;
		path->AddPoint(Point(px + (dx / 3.0), py + (dy / 3.0), 0.0));
		path->AddPoint(Point(point[0] - (dx / 3.0), point[1] - (dy / 3.0), 0.0));
		path->AddPoint(point);
	}

	void Shape::AddQuadTo(const Point& p1, const Point& p2)
	{
		LastPath()->AddPoint(p1);
		LastPath()->AddPoint(p2);
	}

	void Shape::AddCubicTo(const Point& p1, const Point& p2, const Point& p3)
	{
		LastPath()->AddPoint(p1);
		LastPath()->AddPoint(p2);
		LastPath()->AddPoint(p3);
	}

	void Shape::FillLinearGradient(const LinearGradient& linearGradient)
	{
		m_FillStyle.SetLinearGradient(linearGradient);
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->FillLinearGradient(linearGradient);
		}
	}

	LinearGradient Shape::FillLinearGradient() const
	{
		return m_FillStyle.GetLinearGradient();
	}

	void Shape::FillRadialGradient(const RadialGradient& radialGradient)
	{
		m_FillStyle.SetRadialGradient(radialGradient);
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->FillRadialGradient(radialGradient);
		}
	}

	RadialGradient Shape::FillRadialGradient() const
	{
		return m_FillStyle.GetRadialGradient();
	}

	void Shape::StrokeLinearGradient(const LinearGradient& linearGradient)
	{
		m_StrokeStyle.SetLinearGradient(linearGradient);
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->StrokeLinearGradient(linearGradient);
		}
	}

	LinearGradient Shape::StrokeLinearGradient() const
	{
		return m_StrokeStyle.GetLinearGradient();
	}

	void Shape::StrokeRadialGradient(const RadialGradient& radialGradient)
	{
		m_StrokeStyle.SetRadialGradient(radialGradient);
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->StrokeRadialGradient(radialGradient);
		}
	}

	RadialGradient Shape::StrokeRadialGradient() const
	{
		return m_StrokeStyle.GetRadialGradient();
	}

	void Shape::Copy(Shape* shape) const
	{
		if (shape == nullptr)
		{
			return;
		}
		shape->m_lId = m_lId;
		shape->m_Parent = m_Parent;
		shape->m_Position = m_Position;
		shape->m_dWidth = m_dWidth;
		shape->m_dHeight = m_dHeight;
		shape->m_dDepth = m_dDepth;
		shape->m_Center = m_Center;
		shape->m_bComputeBox = m_bComputeBox;
		shape->m_dStrokeWidth = m_dStrokeWidth;
		shape->m_bHasStroke = m_bHasStroke;
		shape->m_FillStyle = m_FillStyle;
		shape->m_StrokeStyle = m_StrokeStyle;
		shape->m_Paths = m_Paths;
		shape->m_bScalable = m_bScalable;
		shape->m_bHasText = m_bHasText;
		shape->m_sText = m_sText;
	}

	void Shape::SetStartShape(Shape* startShape)
	{
		m_StartShape = startShape;
	}

	Shape* Shape::StartShape()
	{
		return m_StartShape;
	}

	void Shape::SetTargetShape(Shape* targetShape)
	{
		m_TargetShape = targetShape;
	}

	Shape* Shape::TargetShape()
	{
		return m_TargetShape;
	}

	void Shape::ZIndex(unsigned int zIndex)
	{
		m_nZIndex = zIndex;
	}

	unsigned int Shape::ZIndex() const
	{
		return m_nZIndex;
	}

	void Shape::ComputeZIndex()
	{
		m_nZIndex = m_Parent->m_nZIndex + 1;
		if (IsLeaf())
		{
			return;
		}
		for (Shape* shape : m_ChildShapes)
		{
			shape->ComputeZIndex();
		}
	}

	bool Shape::operator<(const Shape* other) const
	{
		return m_nZIndex < other->m_nZIndex;
	}

	void Shape::BecomeStartShape()
	{
		if (m_StartShape = nullptr)
		{
			return;
		}
		m_StartShape->Copy(this);
		for (Shape* shape : m_ChildShapes)
		{
			shape->BecomeStartShape();
		}
	}

	void Shape::BecomeTargetShape()
	{
		if (m_TargetShape == nullptr)
		{
			return;
		}
		m_TargetShape->Copy(this);
		for (Shape* shape : m_ChildShapes)
		{
			shape->BecomeTargetShape();
		}
	}

	void Shape::BecomeShape(Shape* root)
	{
		if (root == nullptr)
		{
			return;
		}
		root->Copy(this);
		
		for (size_t idx = 0; idx < m_ChildShapes.size(); idx++)
		{
			m_ChildShapes[idx]->BecomeShape(root->ChildShapes()[idx]);
		}
	}

	std::string Shape::GetText() const
	{
		return m_sText;
	}

	unsigned int Shape::GetFontSize() const
	{
		return m_nFontSize;
	}

	bool Shape::HasText() const
	{
		return m_bHasText;
	}

	void Shape::Scalable()
	{
		m_bScalable = true;
	}

	void Shape::NonScalable()
	{
		m_bScalable = false;
	}

	void Shape::Interpolate(double alpha)
	{
		if (m_StartShape == nullptr || m_TargetShape == nullptr)
		{
			return;
		}

		m_StrokeStyle.Interpolate(m_StartShape->m_StrokeStyle, m_TargetShape->m_StrokeStyle, alpha);
		m_FillStyle.Interpolate(m_StartShape->m_FillStyle, m_TargetShape->m_FillStyle, alpha);

		for (size_t i = 0; i < m_Paths.size(); i++)
		{
			m_Paths[i].Interpolate(m_StartShape->m_Paths[i], m_TargetShape->m_Paths[i], alpha);
		}
	}
}
