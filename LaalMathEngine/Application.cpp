#include <Shape/SvgShape.h>
#include "Scene/Scene.h"
#include "Geometry/Polygon.h"
#include "Animation/Transform.h"
#include "Animation/Creation.h"
#include "Animation/Fading.h"
#include "Shape/ShapeGroup.h"
#include "Math/Bezier.h"
#include "Shape/Text.h"
#include "Geometry/NumberLine.h"
#include "Geometry/ParametricCurve.h"
#include "Animation/FollowPath.h"

class TestScene : public laal::Scene
{
public:

	void Construct() override
	{
		laal::ShapeGroup sg;

		laal::RoundRectangle rect1(0.6, 0.6, 0.1);
		sg.Add(&rect1);
		rect1.FillColor(laal::Color(0x290761));
		laal::RoundRectangle rect2(0.5, 0.5, 0.1);
		sg.Add(&rect2);
		rect2.FillColor(laal::Color(0x631ee3));

		Add(&sg);
		sg.StrokeWidth(0.0);
		sg.Rotate(gmtl::Math::PI_OVER_4, OUT);

		m_pCamera->Capture();
		m_pCamera->GetImage();
	}
};

//class HeartAnimation : public laal::Animation
//{
//protected:
//
//	double m_dMultStart;
//
//	double m_dMultEnd;
//
//	size_t m_nPoints;
//
//	std::vector<Point> m_Points;
//
//public:
//
//	HeartAnimation(laal::Shape* root, double from, double to, size_t nPts, double runtime, double lagtime) :
//		Animation(root, runtime, lagtime),
//		m_dMultStart(from),
//		m_dMultEnd(to),
//		m_nPoints(nPts)
//	{
//
//	}
//
//	void Begin() override
//	{
//		Animation::Begin();
//
//		m_Points.push_back(Point(0.8, 0.0, 0.0));
//		for (laal::Shape* shape : m_pRootShape->ChildShapes())
//		{
//			m_Points.push_back(shape->Paths()[0]->FirstPoint());
//		}
//		double alpha = 1.0;
//		double mult = m_dMultStart * (1.0 - alpha) + m_dMultEnd * alpha;
//		std::vector<laal::Shape*> childShapes = m_pRootShape->ChildShapes();
//		
//		for (unsigned int idx = 1; idx <= childShapes.size(); idx++)
//		{
//			laal::Shape* shape = childShapes[idx - 1];
//
//			Point firstPoint = m_Points[idx];
//
//			Point lastPoint = m_Points[(unsigned int)((double)idx * mult) % m_nPoints];
//
//			shape->Paths()[0]->Reset();
//
//			std::vector<Point> points(4);
//			points[0] = firstPoint;
//			points[3] = lastPoint;
//			points[1] = points[0] * (2.0 / 3.0) + points[3] * (1.0 / 3.0);
//			points[2] = points[0] * (1.0 / 3.0) + points[3] * (2.0 / 3.0);
//			shape->Paths()[0]->AddPoints(points);
//		}
//	}
//
//	void Update() override
//	{
//		if (!m_bAnimationStarted)
//		{
//			m_nFrameCount++;
//			m_bAnimationStarted = m_nFrameCount >= (unsigned int)((double)m_nFrameRate * m_dStartOffset);
//			m_nFrameCount = m_bAnimationStarted ? 0 : m_nFrameCount;
//			return;
//		}
//		if (!m_IsUpdatingMap[m_pRootShape])
//		{
//			return;
//		}
//
//		double alpha = GetAlpha(m_nFrameCount);
//		double mult = m_dMultStart * (1.0 - alpha) + m_dMultEnd * alpha;
//		std::vector<laal::Shape*> childShapes = m_pRootShape->ChildShapes();
//		for (unsigned int idx = 1; idx <= childShapes.size(); idx++)
//		{
//			laal::Shape* shape = childShapes[idx - 1];
//
//			Point firstPoint = m_Points[idx];
//			Point lastPoint = m_Points[(size_t)((double)idx * mult) % m_nPoints];
//
//			shape->Paths()[0]->Reset();
//
//			std::vector<Point> points(4);
//			points[0] = firstPoint;
//			points[3] = lastPoint;
//			points[1] = points[0] * (2.0 / 3.0) + points[3] * (1.0 / 3.0);
//			points[2] = points[0] * (1.0 / 3.0) + points[3] * (2.0 / 3.0);
//			shape->Paths()[0]->AddPoints(points);
//		}
//		m_nFrameCount++;
//	}
//};
//
//class TestScene : public laal::Scene
//{
//public:
//
//	void SetUp() override
//	{
//		m_sMovieFile = "Videos/lme";
//		Scene::SetUp();
//	}
//
//	void Construct() override
//	{
//		unsigned int multiplier = 1;
//		size_t nPts = 200;
//		std::vector<double> theta = laal::Linspace(0.0, gmtl::Math::TWO_PI, (int)nPts + 1);
//		std::vector<Point> points(nPts);
//		double radius = 0.8;
//		for (size_t i = 0; i < nPts; i++)
//		{
//			points[i] = Point(radius * gmtl::Math::cos(theta[i]), radius * gmtl::Math::sin(theta[i]), 0.0);
//		}
//
//		laal::ShapeGroup sg;
//
//		laal::Circle cr(radius);
//		cr.StrokeColor(laal::YELLOW);
//		sg.Add(&cr);
//
//		laal::ShapeGroup lg;
//
//		std::vector<laal::Line> lines(nPts);
//		for (size_t i = 1; i < nPts; i++)
//		{
//			lines[i] = laal::Line(points[i], points[(i * multiplier) % nPts]);
//			lg.Add(&lines[i]);
//		}
//		lg.StrokeGradient(laal::YELLOW, laal::ORANGE_RED);
//		sg.Add(&lg);
//		sg.StrokeWidth(1.0);
//		Add(&sg);
//
//		HeartAnimation ha(&lg, 1, 3, nPts, 6, 0.0);
//		Add(&ha);
//		Play();
//		Wait(0.5);
//
//		//laal::Create crt(&lg, 2.0, 0.01);
//		//crt.EaseFunction(laal::EaseInOutExpo);
//		//Add(&crt);
//		//Play();
//		//Wait(0.5);
//
//		//GetCamera()->Capture();
//		//GetCamera()->GetImage();
//	}
//};

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		laal::ShapeGroup sg;
//
//		laal::Circle rect(0.2);
//		rect.StrokeWidth(3);
//		rect.StrokeColor(laal::ORANGE_RED);
//		sg.Add(&rect);
//
//		laal::Circle rect1(0.1);
//		rect1.StrokeWidth(3);
//		rect1.StrokeColor(laal::ORANGE);
//		sg.Add(&rect1);
//		rect1.Translate(0.0, rect.Height() / 2.0 + rect1.Height() / 2.0, 0.0);
//
//		Add(&sg);
//
//		laal::Translate tr(&sg, -0.5, 0.5, 0.0, 1.0, 0.0);
//		Add(&tr);
//		laal::Scale sc(&sg, 0.5, 1.0, 0.0);
//		Add(&sc);
//		laal::Rotate rt(&sg, gmtl::Math::TWO_PI, OUT, 1.0, 0.0);
//		Add(&rt);
//		Play();
//		Wait(0.5);
//
//		//tr.ApplyChangeAfter(rt.TargetShape(), 1.0);
//		//sc.ApplyChangeAfter(rt.TargetShape(), 1.0);
//		//sc.ApplyChangeAfter(tr.TargetShape(), 1.0);
//		//tr.ApplyChangeAfter(sc.TargetShape(), 1.0);
//		//rt.ApplyChangeAfter(tr.TargetShape(), 1.0);
//		//tr.Begin();
//		//rt.Begin();
//		//sc.Begin();
//		//Add(rt.TargetShape());
//		//Add(tr.TargetShape());
//		//Add(sc.TargetShape());
//
//		//GetCamera()->Capture();
//		//GetCamera()->GetImage();
//	}
//};

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		laal::ShapeGroup logo;
//
//		laal::Circle cr(0.1);
//		cr.StrokeWidth(0.0);
//		cr.FillColor(laal::RED);
//		Add(&cr);
//		
//		laal::AnnularSector as1(0.1, 0.2, gmtl::Math::PI_OVER_2, 0.0);
//		as1.StrokeWidth(0);
//		as1.FillColor(laal::YELLOW);
//		logo.Add(&as1);
//		laal::AnnularSector as1d(0.1, 0.2, gmtl::Math::PI_OVER_2, gmtl::Math::PI);
//		as1d.StrokeWidth(0);
//		as1d.FillColor(laal::YELLOW);
//		logo.Add(&as1d);
//
//		laal::AnnularSector as(0.2, 0.3, gmtl::Math::PI_OVER_2, gmtl::Math::PI_OVER_2);
//		as.StrokeWidth(0);
//		as.FillColor(laal::PURPLE);
//		logo.Add(&as);
//		laal::AnnularSector asd(0.2, 0.3, gmtl::Math::PI_OVER_2, 3.0 * gmtl::Math::PI_OVER_2);
//		asd.StrokeWidth(0);
//		asd.FillColor(laal::PURPLE);
//		logo.Add(&asd);
//
//		laal::AnnularSector as2(0.3, 0.4, gmtl::Math::PI_OVER_2, 2.0 * gmtl::Math::PI_OVER_2);
//		as2.StrokeWidth(0);
//		as2.FillColor(laal::MID_NIGHT_BLUE);
//		logo.Add(&as2);
//		laal::AnnularSector as2d(0.3, 0.4, gmtl::Math::PI_OVER_2, 0.0);
//		as2d.StrokeWidth(0);
//		as2d.FillColor(laal::MID_NIGHT_BLUE);
//		logo.Add(&as2d);
//
//		laal::AnnularSector as3(0.4, 0.5, gmtl::Math::PI_OVER_2, 3.0 * gmtl::Math::PI_OVER_2);
//		as3.StrokeWidth(0);
//		as3.FillColor(laal::ORANGE_RED);
//		logo.Add(&as3);
//		laal::AnnularSector as3d(0.4, 0.5, gmtl::Math::PI_OVER_2, gmtl::Math::PI_OVER_2);
//		as3d.StrokeWidth(0);
//		as3d.FillColor(laal::ORANGE_RED);
//		logo.Add(&as3d);
//
//		Add(&logo);
//
//		laal::Rotate rt(&logo, gmtl::Math::PI, OUT, 2.0, 0.1);
//		rt.EaseFunction(laal::EaseInOutExpo);
//		Add(&rt);
//		Play();
//		Wait(0.5);
//	}
//};

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		laal::Text waterMark(Point(1.0, -0.9, 0.0), "(Made with LME)");
//		waterMark.SetFontSize(20);
//		waterMark.FillColor(laal::Color(0.7, 0.7, 0.7, 0.7));
//		Add(&waterMark);
//
//		laal::ShapeGroup logo;
//
//		unsigned int nRects = 8;
//		double width = 0.25;
//		double widthSmall = 0.17;
//		double height = 0.08;
//		double radius = 0.04;
//		std::vector<laal::RoundRectangle> rects(nRects);
//		for (unsigned int i = 0; i < nRects; i++)
//		{
//			rects[i] = laal::RoundRectangle(width, height, radius);
//			rects[i].Translate((width / 2.0) - radius, 0, 0);
//			rects[i].RotateAboutPoint((double)i * gmtl::Math::TWO_PI / 8.0, OUT, ORIGIN);
//			logo.Add(&rects[i]);
//		}
//		logo.StrokeColor(laal::RED);
//		logo.FillColor(laal::ORANGE_RED);
//		logo.FillOpacity(0.5);
//		logo.StrokeWidth(1);
//		Add(&logo);
//
//		laal::Rotate rtLogo(&logo, gmtl::Math::TWO_PI, OUT, 2.0, 0.1);
//		rtLogo.EaseFunction(laal::EaseInOutExpo);
//		Add(&rtLogo);
//		laal::FadeIn fdLogo(&logo, 2.0, 0.1);
//		fdLogo.EaseFunction(laal::EaseInOutExpo);
//		Add(&fdLogo);
//		Play();
//
//		laal::Rotate rtLogoAgain(&logo, -gmtl::Math::TWO_PI, OUT, 2.0, 0.1);
//		rtLogoAgain.EaseFunction(laal::EaseInOutExpo);
//		Add(&rtLogoAgain);
//		Play();
//
//		laal::ShapeGroup lShape;
//		lShape.Add(&rects[0]);
//		lShape.Add(&rects[2]);
//		laal::Transform trRect0(&rects[0], 1.0, 0.0);
//		trRect0.EaseFunction(laal::EaseInOutExpo);
//		trRect0.GetTargetShape()->Strech(widthSmall / width, X_AXIS);
//		trRect0.GetTargetShape()->Translate(widthSmall - width + radius, 0, 0);
//		Add(&trRect0);
//
//		laal::ShapeGroup lShapeInv;
//		lShapeInv.Add(&rects[4]);
//		lShapeInv.Add(&rects[6]);
//		laal::Transform trRect4(&rects[4], 1.0, 0.0);
//		trRect4.EaseFunction(laal::EaseInOutExpo);
//		trRect4.GetTargetShape()->Strech(widthSmall / width, X_AXIS);
//		trRect4.GetTargetShape()->Translate(-widthSmall + width - radius, 0, 0);
//		Add(&trRect4);
//
//		laal::ShapeGroup aShape;
//		aShape.Add(&rects[5]);
//		aShape.Add(&rects[7]);
//		laal::Transform trRect7(&rects[7], 1.0, 0.0);
//		trRect7.EaseFunction(laal::EaseInOutExpo);
//		trRect7.GetTargetShape()->RotateAboutPoint(gmtl::Math::PI_OVER_4, OUT, ORIGIN);
//		trRect7.GetTargetShape()->Strech(widthSmall / width, X_AXIS);
//		trRect7.GetTargetShape()->Translate(widthSmall - width + radius, 0, 0);
//		trRect7.GetTargetShape()->RotateAboutPoint(-gmtl::Math::PI_OVER_4, OUT, ORIGIN);
//		Add(&trRect7);
//
//		laal::ShapeGroup aShapeInv;
//		aShapeInv.Add(&rects[1]);
//		aShapeInv.Add(&rects[3]);
//		laal::Transform trRect3(&rects[3], 1.0, 0.0);
//		trRect3.EaseFunction(laal::EaseInOutExpo);
//		trRect3.GetTargetShape()->RotateAboutPoint(-3.0 * gmtl::Math::PI_OVER_4, OUT, ORIGIN);
//		trRect3.GetTargetShape()->Strech(widthSmall / width, X_AXIS);
//		trRect3.GetTargetShape()->Translate(widthSmall - width + radius, 0, 0);
//		trRect3.GetTargetShape()->RotateAboutPoint(3.0 * gmtl::Math::PI_OVER_4, OUT, ORIGIN);
//		Add(&trRect3);
//		Play();
//
//		laal::Translate trLShape(&lShape, -1.22 * width, 0.0, 0.0, 1.0, 0.0);
//		trLShape.EaseFunction(laal::EaseInOutExpo);
//		Add(&trLShape);
//		laal::Translate trLShapeInv(&lShapeInv, 1.22 * width, 0.0, 0.0, 1.0, 0.0);
//		trLShapeInv.EaseFunction(laal::EaseInOutExpo);
//		Add(&trLShapeInv);
//		laal::Translate trAShape(&aShape, -0.37 * width, 0.0, 0.0, 1.0, 0.0);
//		trAShape.EaseFunction(laal::EaseInOutExpo);
//		Add(&trAShape);
//		laal::Translate trAShapeInv(&aShapeInv, 0.37 * width, 0.0, 0.0, 1.0, 0.0);
//		trAShapeInv.EaseFunction(laal::EaseInOutExpo);
//		Add(&trAShapeInv);
//		Play();
//
//		laal::ShapeGroup shapeGroup;
//		shapeGroup.Add(&lShape);
//		shapeGroup.Add(&lShapeInv);
//		shapeGroup.Add(&aShape);
//		shapeGroup.Add(&aShapeInv);
//
//		laal::Rotate rtSg(&shapeGroup, gmtl::Math::TWO_PI, OUT, 2.0, 0.0);
//		rtSg.EaseFunction(laal::EaseInOutExpo);
//		Add(&rtSg);
//		Play();
//		Wait(0.5);
//	}
//};

/*class TestScene : public laal::Scene
{
public:

	void Construct() override
	{
		laal::Line ln(Point(-1, 0, 0), Point(1, 0, 0));
		ln.StrokeColor(laal::ORANGE_RED);
		Add(&ln);

		auto func1 = [](double t)
		{
			return t;
		};
		auto func2 = [](double t)
		{
			return (1.0 / gmtl::Math::TWO_PI) * gmtl::Math::sin(t * gmtl::Math::TWO_PI);
		};

		laal::ParametricCurve pc(func1, func2, -1, 1);
		pc.StrokeColor(laal::BLUE_VIOLET);
		Add(&pc);

		//laal::Arrow ar(Point(0, 0, 0), Point(0.5, 0.0, 0.0));
		//Add(&ar);

		laal::ShapeGroup sg;
		laal::Dot dt;
		dt.Translate(0.5, 0.0,  0.0);
		sg.Add(&dt);
		laal::Line ln1(Point(0.0, 0.0, 0.0), Point(0.5, 0.0, 0.0));
		ln1.StrokeColor(laal::WHITE);
		sg.Add(&ln1);
		Add(&sg);

		laal::FollowPath fp(&sg, func1, func2, -1, 1, 3.0, 0);
		fp.EaseFunction(laal::EaseInOutExpo);
		Add(&fp);
		fp.Begin();
		Play();
		Wait(0.5);
		//ar.Rotate(gmtl::Math::aTan(laal::Derivative(func1, func2, -1)), OUT);

		//GetCamera()->Capture();
		//GetCamera()->GetImage();
	}
};*/

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		auto func1 = [](double t)
//		{
//			//return 0.5 * gmtl::Math::cos(t);
//			return t;
//		};
//		auto func2 = [](double t)
//		{
//			//return 0.5 * gmtl::Math::sin(t);
//			return t * t - 0.5;
//			//return t * t * t;
//			//return gmtl::Math::exp(t);
//		};
//
//		laal::Rectangle rect(0.4, 0.1);
//		rect.FillColor(laal::GREEN_A);
//		rect.StrokeWidth(0);
//		Add(&rect);
//
//		laal::FollowPath fp(&rect, func1, func2, -1.0, 1.0, 3, 0.0);
//		fp.EaseFunction(laal::EaseInOutExpo);
//		Add(&fp);
//		Play();
//		Wait(0.5);
//
//		//std::cout << "derivate of func2 at 0 => " << laal::Derivative(func2, 0) << std::endl;
//		//std::cout << "derivate of func1 at 0 => " << laal::Derivative(func1, 0) << std::endl;
//		//std::cout << "derivate at (0, 0, 0) => " << laal::Derivative(func1, func2, Point(0, 0, 0)) << std::endl;
//		//std::cout << "derivative at t = 0 => " << laal::Derivative(func1, func2, 0.0) << std::endl;
//		//std::cout << "derivative at t = 0.234 => " << laal::Derivative(func1, func2, 0.234) << std::endl;
//		//std::cout << "derivative at t = 0.7561 => " << laal::Derivative(func1, func2, 0.7561) << std::endl;
//		//std::cout << "slope at t = 0 => " << gmtl::Math::aTan(laal::Derivative(func1, func2, 0.0)) << std::endl;
//		//std::cout << "slope at t = 0.234 => " << gmtl::Math::aTan(laal::Derivative(func1, func2, 0.234)) << std::endl;
//		//std::cout << "slope at t = 0.7561 => " << gmtl::Math::aTan(laal::Derivative(func1, func2, 0.7561)) << std::endl;
//	}
//};

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		double R = 1.0;
//		double r = 0.5;
//		double d = r;
//		auto fun1 = [&](double theta)
//		{
//			return (R - r) * gmtl::Math::cos(theta) + d * gmtl::Math::cos(((R - r) / r) * theta);
//			//return r * gmtl::Math::cos(theta);
//			//return theta;
//			//return R * gmtl::Math::cos(theta);
//		};
//		auto fun2 = [&](double theta)
//		{
//			return (R - r) * gmtl::Math::sin(theta) - d * gmtl::Math::sin(((R - r) / r) * theta);
//			//return r * gmtl::Math::sin(theta);
//			//return theta * theta;
//			//return r * gmtl::Math::sin(theta);
//		};
//
//		laal::ParametricCurve pc(fun1, fun2, 0, gmtl::Math::PI / 2.0);
//		pc.StrokeColor(laal::ORANGE);
//		Add(&pc);
//
//		GetCamera()->Capture();
//		GetCamera()->GetImage();
//	}
//};

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		laal::ShapeGroup sg;
//		std::vector<laal::Circle> dots(11);
//		double start = -1.0;
//		for (laal::Circle& dot : dots)
//		{
//			dot.Scale(0.05);
//			dot.MoveTo(start, 0.0, 0.0);
//			sg.Add(&dot);
//			start += 0.2;
//		}
//		laal::LinearGradient lg(-1.0, 0.0, 1.0, 0.0, laal::SPREAD_PAD);
//		lg.AddStop(0.0, laal::RED);
//		lg.AddStop(0.5, laal::ORANGE_RED);
//		lg.AddStop(1.0, laal::ORANGE);
//		sg.FillLinearGradient(lg);
//		sg.StrokeWidth(0);
//		Add(&sg);
//
//		//laal::Translate tr(&sg, 0.0, 0.5, 0.0, 1.0, 0.1);
//		laal::Rotate tr(&sg, gmtl::Math::PI, OUT, 1.5, 0.1);
//		tr.EaseFunction(laal::EaseInOutExpo);
//		Add(&tr);
//		Play();
//		Wait(0.5);
//	}
//};

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		laal::Line x(Point(-1, 0, 0), Point(1, 0, 0));
//		x.StrokeColor(laal::DARK_ORANGE);
//		Add(&x);
//
//		laal::Line y(Point(0, -1, 0), Point(0, 1, 0));
//		y.StrokeColor(laal::DARK_ORANGE);
//		Add(&y);
//
//		laal::Text tx(Point(0.5, 0.5, 0), "Laal Math Engine\nis awesome.\nI love LME.");
//		tx.SetFontSize(15);
//		tx.FillColor(laal::YELLOW);
//		Add(&tx);
//
//		GetCamera()->Capture();
//		GetCamera()->GetImage();
//	}
//};

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		laal::ShapeGroup sg;
//
//		laal::RegularPolygon rp1(6, 0.1);
//		rp1.StrokeColor(laal::YELLOW);
//		sg.Add(&rp1);
//
//		laal::RegularPolygon rp2(6, 0.3);
//		rp2.StrokeColor(laal::YELLOW);
//		sg.Add(&rp2);
//
//		laal::RegularPolygon rp3(6, 0.5);
//		rp3.StrokeColor(laal::YELLOW);
//		sg.Add(&rp3);
//
//		laal::RegularPolygon rp4(6, 0.7);
//		rp4.StrokeColor(laal::YELLOW);
//		sg.Add(&rp4);
//
//		Add(&sg);
//		sg.Scale(0.5); 
//
//		//laal::Rotate rt(&sg, gmtl::Math::PI / 3.0, OUT, 1.0, 0.3);
//		//rt.EaseFunction(laal::EaseInOutExpo);
//		//Add(&rt);
//		laal::Scale sc(&sg, 2.0, 1.0, 0.1);
//		sc.EaseFunction(laal::EaseInOutCubic);
//		Add(&sc);
//		Play();
//		Wait(0.5);
//	}
//};

//class TestScene : public laal::Scene
//{
//public:
//
//	void Construct() override
//	{
//		laal::NumberLine nl(-2.0, 2.0, 0.5, 1, laal::LINE_TICK);
//		Add(&nl);
//		nl.HideTicks();
//		nl.HideLabels();
//
//		laal::Create cr(&nl, 1.0, 0);
//		Add(&cr);
//		Play();
//		Wait(0.5);
//
//		nl.ShowTicks();
//		nl.ShowLabels();
//		laal::FadeIn fdTick(nl.Ticks(), 1.0, 0.02);
//		laal::FadeIn fdLabel(nl.Labels(), 1.0, 0.02);
//		Add(&fdTick);
//		Add(&fdLabel);
//		Play();
//		Wait(0.5);
//
//		laal::NumberLine dupNl(-2, 2, 0.5, 1, laal::LINE_TICK);
//		Add(&dupNl);
//		dupNl.HideLabels();
//
//		laal::Translate tr(&dupNl, 0.0, -0.3, 0.0, 1.0, 0.0);
//		tr.EaseFunction(laal::EaseInOutQuint);
//		Add(&tr);
//		Play();
//		Wait(0.5);
//
//		dupNl.ShowLabels();
//		dupNl.Labels()->Translate(0.0, -0.3, 0.0);
//		laal::FadeIn fdDupLabel(dupNl.Labels(), 1.0, 0.02);
//		Add(&fdDupLabel);
//		Play();
//		Wait(0.5);
//
//		dupNl.SubDivide(3);
//		laal::Strech st(&dupNl, 1.5, X_AXIS, 1.0, 0.0);
//		Add(&st);
//		Play();
//		Wait(1.0);
//
//		double sigma = 0.8408964;
//		for (int y = 1; y <= 7; y++)
//		{
//			for (int x = 1; x <= 7; x++)
//			{
//				double res = (1.0 / (gmtl::Math::TWO_PI * sigma * sigma)) * gmtl::Math::exp(-1.0 * ((x - 4) * (x - 4) + (y - 4) * (y - 4)) / (2.0 * sigma * sigma));
//				std::cout << res << " ";
//			}
//			std::cout << std::endl;
//		}
//	}
//};

int main()
{
	laal::Scene* scene = new TestScene();
	scene->SetUp();
	scene->Construct();
	delete scene;

	return 0;

	//BLImage img(480, 480, BL_FORMAT_PRGB32);
	//BLContext ctx(img);

	//ctx.setCompOp(BL_COMP_OP_SRC_COPY);
	//ctx.fillAll();

	//double fr = 480.0 / 2.0;
	//double pw = 480.0 / 2.0;
	//double ph = 480.0 / 2.0;
	//BLMatrix2D mat(
	//	fr, 0.0,
	//	0.0, -1.0 * fr,
	//	pw, ph
	//);
	//ctx.setMatrix(mat);
	//ctx.userToMeta();

	//// First shape filld by a radial gradient.
	//BLGradient radial(BLRadialGradientValues(0, 0, 0, 0, 0.8));
	//radial.addStop(0.0, BLRgba32(0xFFFFFFFF));
	//radial.addStop(1.0, BLRgba32(0xFFFF6F3F));
	//radial.setExtendMode(BL_EXTEND_MODE_PAD);

	//ctx.setCompOp(BL_COMP_OP_SRC_OVER);
	//ctx.setFillStyle(radial);
	//ctx.fillCircle(0, 0, 0.8);

	//ctx.end();
	//img.writeToFile("TestFrames/frame1.bmp");

	//return 0;
}