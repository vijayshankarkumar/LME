#include "Scene/LogoScene.h"

namespace laal
{
	void LogoScene::Construct()
	{
		AnimateLogo();
	}

	void LogoScene::AnimateLogo()
	{
		laal::Text waterMark(Point(1.0, -0.9, 0.0), "(Made with LME)");
		waterMark.SetFontSize(20);
		waterMark.FillColor(laal::Color(0.7, 0.7, 0.7, 0.7));
		Add(&waterMark);
		
		laal::ShapeGroup logo;
		
		unsigned int nRects = 8;
		double width = 0.25;
		double widthSmall = 0.17;
		double height = 0.08;
		double radius = 0.04;
		std::vector<laal::RoundRectangle> rects(nRects);
		for (unsigned int i = 0; i < nRects; i++)
		{
			rects[i] = laal::RoundRectangle(width, height, radius);
			rects[i].Translate((width / 2.0) - radius, 0, 0);
			rects[i].RotateAboutPoint((double)i * gmtl::Math::TWO_PI / 8.0, OUT, ORIGIN);
			logo.Add(&rects[i]);
		}
		logo.StrokeColor(laal::RED);
		logo.FillColor(laal::ORANGE_RED);
		logo.FillOpacity(0.5);
		logo.StrokeWidth(1);
		Add(&logo);
		
		laal::Rotate rtLogo(&logo, gmtl::Math::TWO_PI, OUT, 2.0, 0.1);
		rtLogo.EaseFunction(laal::EaseInOutExpo);
		Add(&rtLogo);
		laal::FadeIn fdLogo(&logo, 2.0, 0.1);
		fdLogo.EaseFunction(laal::EaseInOutExpo);
		Add(&fdLogo);
		Play();
		
		laal::Rotate rtLogoAgain(&logo, -gmtl::Math::TWO_PI, OUT, 2.0, 0.1);
		rtLogoAgain.EaseFunction(laal::EaseInOutExpo);
		Add(&rtLogoAgain);
		Play();
		
		laal::ShapeGroup lShape;
		lShape.Add(&rects[0]);
		lShape.Add(&rects[2]);
		laal::Transform trRect0(&rects[0], 1.0, 0.0);
		trRect0.EaseFunction(laal::EaseInOutExpo);
		trRect0.GetTargetShape()->Strech(widthSmall / width, X_AXIS);
		trRect0.GetTargetShape()->Translate(widthSmall - width + radius, 0, 0);
		Add(&trRect0);
		
		laal::ShapeGroup lShapeInv;
		lShapeInv.Add(&rects[4]);
		lShapeInv.Add(&rects[6]);
		laal::Transform trRect4(&rects[4], 1.0, 0.0);
		trRect4.EaseFunction(laal::EaseInOutExpo);
		trRect4.GetTargetShape()->Strech(widthSmall / width, X_AXIS);
		trRect4.GetTargetShape()->Translate(-widthSmall + width - radius, 0, 0);
		Add(&trRect4);
		
		laal::ShapeGroup aShape;
		aShape.Add(&rects[5]);
		aShape.Add(&rects[7]);
		laal::Transform trRect7(&rects[7], 1.0, 0.0);
		trRect7.EaseFunction(laal::EaseInOutExpo);
		trRect7.GetTargetShape()->RotateAboutPoint(gmtl::Math::PI_OVER_4, OUT, ORIGIN);
		trRect7.GetTargetShape()->Strech(widthSmall / width, X_AXIS);
		trRect7.GetTargetShape()->Translate(widthSmall - width + radius, 0, 0);
		trRect7.GetTargetShape()->RotateAboutPoint(-gmtl::Math::PI_OVER_4, OUT, ORIGIN);
		Add(&trRect7);
		
		laal::ShapeGroup aShapeInv;
		aShapeInv.Add(&rects[1]);
		aShapeInv.Add(&rects[3]);
		laal::Transform trRect3(&rects[3], 1.0, 0.0);
		trRect3.EaseFunction(laal::EaseInOutExpo);
		trRect3.GetTargetShape()->RotateAboutPoint(-3.0 * gmtl::Math::PI_OVER_4, OUT, ORIGIN);
		trRect3.GetTargetShape()->Strech(widthSmall / width, X_AXIS);
		trRect3.GetTargetShape()->Translate(widthSmall - width + radius, 0, 0);
		trRect3.GetTargetShape()->RotateAboutPoint(3.0 * gmtl::Math::PI_OVER_4, OUT, ORIGIN);
		Add(&trRect3);
		Play();
		
		laal::Translate trLShape(&lShape, -1.22 * width, 0.0, 0.0, 1.0, 0.0);
		trLShape.EaseFunction(laal::EaseInOutExpo);
		Add(&trLShape);
		laal::Translate trLShapeInv(&lShapeInv, 1.22 * width, 0.0, 0.0, 1.0, 0.0);
		trLShapeInv.EaseFunction(laal::EaseInOutExpo);
		Add(&trLShapeInv);
		laal::Translate trAShape(&aShape, -0.37 * width, 0.0, 0.0, 1.0, 0.0);
		trAShape.EaseFunction(laal::EaseInOutExpo);
		Add(&trAShape);
		laal::Translate trAShapeInv(&aShapeInv, 0.37 * width, 0.0, 0.0, 1.0, 0.0);
		trAShapeInv.EaseFunction(laal::EaseInOutExpo);
		Add(&trAShapeInv);
		Play();
		
		laal::ShapeGroup shapeGroup;
		shapeGroup.Add(&lShape);
		shapeGroup.Add(&lShapeInv);
		shapeGroup.Add(&aShape);
		shapeGroup.Add(&aShapeInv);
		
		laal::Rotate rtSg(&shapeGroup, gmtl::Math::TWO_PI, OUT, 2.0, 0.0);
		rtSg.EaseFunction(laal::EaseInOutExpo);
		Add(&rtSg);
		Play();
		Wait(0.5);

		Remove(&logo);
	}
}