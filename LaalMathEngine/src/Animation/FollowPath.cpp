#include "Animation/FollowPath.h"

namespace laal
{
	FollowPath::FollowPath(
		Shape* root,
		std::function<double(double)> pathXt,
		std::function<double(double)> pathYt,
		double tMin,
		double tMax,
		double runtime,
		double lagtime) :
		Animation(root, runtime, lagtime),
		m_PathXt(pathXt),
		m_PathYt(pathYt),
		m_dTMin(tMin),
		m_dTMax(tMax)
	{

	}

	FollowPath::~FollowPath()
	{

	}

	double FollowPath::GetT(double alpha)
	{
		return m_dTMin + alpha * (m_dTMax - m_dTMin);
	}

	Point FollowPath::GetPointAtT(double t)
	{
		return Point(m_PathXt(t), m_PathYt(t), 0.0);
	}

	void FollowPath::Begin()
	{
		Animation::Begin();
		m_pRootShape->MoveTo(GetPointAtT(m_dTMin));
		m_pStartShape->MoveTo(GetPointAtT(m_dTMin));
		m_pTargetShape->MoveTo(GetPointAtT(m_dTMax));

		double angleStart = gmtl::Math::aTan(Derivative(m_PathXt, m_PathYt, m_dTMin));
		double angleEnd = gmtl::Math::aTan(Derivative(m_PathXt, m_PathYt, m_dTMax));
		m_pRootShape->Rotate(angleStart, OUT);
		m_pTargetShape->Rotate(angleEnd, OUT);
	}

	void FollowPath::Update(Shape* shape, unsigned int frameCount)
	{
		double alpha = GetAlpha(frameCount);
		double prevAlpha = frameCount == 0 ? 0.0 : GetAlpha(frameCount - 1);
		double t = GetT(alpha);
		double prevT = GetT(prevAlpha);

		Point point = GetPointAtT(t);
		Point startPoint = GetPointAtT(m_dTMin);
		shape->BecomeShape(m_StartMap[shape]);
		shape->Translate(Vector(point - startPoint));

		double angle = gmtl::Math::aTan(Derivative(m_PathXt, m_PathYt, t));
		double prevAngle = gmtl::Math::aTan(Derivative(m_PathXt, m_PathYt, prevT));

		shape->RotateAboutPoint(angle, OUT, point);
	}

	void FollowPath::ApplyChangeAfter(Shape* shape, double time)
	{
		Clip(time, 0, m_dRuntime);
		unsigned int frameCount = (unsigned int)(time * (double)m_nFrameRate);
		frameCount = frameCount == 0 ? 0 : frameCount - 1;

		double alpha = GetAlpha(frameCount);
		double t = GetT(alpha);
		
		Point point = GetPointAtT(t);
		shape->MoveTo(point);

		double angle = gmtl::Math::aTan(Derivative(m_PathXt, m_PathYt, t));
		shape->Rotate(angle, OUT);
	}

	void FollowPath::Finish()
	{
		m_pRootShape->Position(m_pTargetShape->Position());
	}
}