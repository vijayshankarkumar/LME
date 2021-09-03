#include "Animation/Transform.h"

namespace laal
{
	Transform::Transform(Shape* root, double runtime, double lagtime) :
		Animation(root, runtime, lagtime)
	{

	}

	Transform::~Transform()
	{
		
	}

	void Transform::Begin()
	{
		Animation::Begin();
		m_pRootShape->SetTargetShape(m_pTargetShape);
	}

	void Transform::Update(Shape* shape, unsigned int frameCount)
	{
		shape->Interpolate(GetAlpha(frameCount));
	}

	Shape* Transform::GetTargetShape() const
	{
		return m_pTargetShape;
	}

	void Transform::Finish()
	{
		m_pRootShape->BecomeShape(m_pTargetShape);
	}

	Translate::Translate(Shape* root, double x, double y, double z, double runtime, double lagtime) :
		Animation(root, runtime, lagtime),
		m_TranslateVector(x, y, z)
	{

	}

	Translate::Translate(Shape* root, const Vector& alongVector, double runtime, double lagtime) :
		Animation(root, runtime, lagtime),
		m_TranslateVector(alongVector)
	{

	}

	Translate::~Translate()
	{

	}

	void Translate::Begin()
	{
		Animation::Begin();
		m_pTargetShape->Translate(m_TranslateVector);
	}

	void Translate::Update(Shape* shape, unsigned int frameCount)
	{
		//std::cout << "called from Translate Update()... frameCount => " << frameCount << std::endl;
		double prevAlpha = frameCount == 0 ? 0.0 : GetAlpha(frameCount - 1);
		double alpha = GetAlpha(frameCount);
		shape->Translate(m_TranslateVector * (alpha - prevAlpha));

		Point position = m_pStartShape->Position() * (1.0 - alpha) + m_pTargetShape->Position() * alpha;
		m_pRootShape->Position(position);
	}

	void Translate::Finish()
	{
		m_pRootShape->Position(m_pTargetShape->Position());
	}

	void Translate::ApplyChangeAfter(Shape* shape, double time)
	{
		Clip(time, 0, m_dRuntime);
		unsigned int frameCount = (unsigned int)(time * m_nFrameRate);
		frameCount = frameCount == 0 ? 0 : frameCount - 1;
		double alpha = GetAlpha(frameCount);
		shape->Translate(m_TranslateVector * alpha);
	}

	TranslateAboutPoint::TranslateAboutPoint(Shape* root, const Vector& alongVector, const Point& aboutPoint, double runtime, double lagtime) :
		Translate(root, alongVector, runtime, lagtime)
	{

	}

	TranslateAboutPoint::~TranslateAboutPoint()
	{

	}

	Scale::Scale(Shape* root, double scaleFactor, double runtime, double lagtime) :
		Animation(root, runtime, lagtime),
		m_ScaleVector(scaleFactor, scaleFactor, scaleFactor)
	{

	}

	Scale::Scale(Shape* root, double sx, double sy, double sz, double runtime, double lagtime) :
		Animation(root, runtime, lagtime),
		m_ScaleVector(sx, sy, sz)
	{

	}

	Scale::Scale(Shape* root, const Vector& scaleVector, double runtime, double lagtime) :
		Animation(root, runtime, lagtime),
		m_ScaleVector(scaleVector)
	{

	}

	Scale::~Scale()
	{

	}

	void Scale::Begin()
	{
		Animation::Begin();
		m_pTargetShape->Scale(m_ScaleVector);
	}

	void Scale::Update(Shape* shape, unsigned int frameCount)
	{
		double prevAlpha = frameCount == 0 ? 0.0 : GetAlpha(frameCount - 1);
		double alpha = GetAlpha(frameCount);
		Vector prevScaleVector = Vector(1.0, 1.0, 1.0) * (1.0 - prevAlpha) + m_ScaleVector * prevAlpha;

		Vector scaleVector = Vector(1.0, 1.0, 1.0) * (1.0 - alpha) + m_ScaleVector * alpha;
		if (prevScaleVector[0] > 0.0 && prevScaleVector[1] > 0.0 && prevScaleVector[2] > 0.0)
		{
			shape->ScaleAboutPoint(Vector(1.0 / prevScaleVector[0], 1.0 / prevScaleVector[1], 1.0 / prevScaleVector[2]), m_pRootShape->Position());
		}
		shape->ScaleAboutPoint(scaleVector, m_pRootShape->Position());
	}

	void Scale::ApplyChangeAfter(Shape* shape, double time)
	{
		Clip(time, 0, m_dRuntime);
		unsigned int frameCount = (unsigned int)(time * m_nFrameRate);
		frameCount = frameCount == 0 ? 0 : frameCount - 1;
		double alpha = GetAlpha(frameCount);
		Vector scaleVector = Vector(1.0, 1.0, 1.0) * (1.0 - alpha) + m_ScaleVector * alpha;
		shape->Scale(scaleVector);
	}

	void Scale::Finish()
	{
		m_pRootShape->Position(m_pTargetShape->Position());
	}

	Strech::Strech(Shape* root, double strechFactor, const Vector& axis, double runtime, double lagtime) :
		Scale(root, axis[0] == 1.0 ? strechFactor : 1.0, axis[1] == 1.0 ? strechFactor : 1.0, axis[2] == 1.0 ? strechFactor : 1.0, runtime, lagtime)
	{

	}

	Strech::~Strech()
	{

	}

	ScaleAboutPoint::ScaleAboutPoint(Shape* root, const Vector& scaleVector, const Point& aboutPoint, double runtime, double lagtime) :
		Scale(root, scaleVector, runtime, lagtime)
	{

	}

	ScaleAboutPoint::ScaleAboutPoint(Shape* root, double scaleFactor, const Point& aboutPoint, double runtime, double lagtime) :
		Scale(root, scaleFactor, runtime, lagtime),
		m_AboutPoint(aboutPoint)
	{

	}

	ScaleAboutPoint::~ScaleAboutPoint()
	{

	}

	void ScaleAboutPoint::Begin()
	{
		Animation::Begin();
		m_pTargetShape->ScaleAboutPoint(m_ScaleVector, m_AboutPoint);
	}

	void ScaleAboutPoint::Update(Shape* shape, unsigned int frameCount)
	{
		double prevAlpha = frameCount == 0 ? 0.0 : GetAlpha(frameCount - 1);
		double alpha = GetAlpha(frameCount);
		Vector prevScaleVector = Vector(1.0, 1.0, 1.0) * (1.0 - prevAlpha) + m_ScaleVector * prevAlpha;

		Vector scaleVector = Vector(1.0, 1.0, 1.0) * (1.0 - alpha) + m_ScaleVector * alpha;
		if (prevScaleVector[0] > 0.0 && prevScaleVector[1] > 0.0 && prevScaleVector[2] > 0.0)
		{
			shape->ScaleAboutPoint(Vector(1.0 / prevScaleVector[0], 1.0 / prevScaleVector[1], 1.0 / prevScaleVector[2]), m_AboutPoint);
		}
		shape->ScaleAboutPoint(scaleVector, m_AboutPoint);
	}

	void ScaleAboutPoint::ApplyChangeAfter(Shape* shape, double time)
	{
		Clip(time, 0, m_dRuntime);
		unsigned int frameCount = (unsigned int)(time * m_nFrameRate);
		frameCount = frameCount == 0 ? 0 : frameCount - 1;
		double alpha = GetAlpha(frameCount);
		Vector scaleVector = Vector(1.0, 1.0, 1.0) * (1.0 - alpha) + m_ScaleVector * alpha;
		shape->ScaleAboutPoint(scaleVector, m_AboutPoint);
	}

	void ScaleAboutPoint::Finish()
	{
		m_pRootShape->Position(m_pTargetShape->Position());
	}

	Point ScaleAboutPoint::AboutPoint() const
	{
		return m_AboutPoint;
	}

	MoveTo::MoveTo(Shape* root, double destX, double destY, double destZ, double runtime, double lagtime) :
		Translate(root, Vector(destX - root->Position()[0], destY - root->Position()[1], destZ - root->Position()[2]), runtime, lagtime)
	{

	}

	MoveTo::MoveTo(Shape* root, const Point& dest, double runtime, double lagtime) :
		Translate(root, Vector(dest - root->Position()), runtime, lagtime)
	{

	}

	MoveTo::~MoveTo()
	{

	}

	MoveToAboutPoint::MoveToAboutPoint(Shape* root, const Point& destPoint, const Point& aboutPoint, double runtime, double lagtime) :
		Translate(root, Vector(destPoint - aboutPoint), runtime, lagtime)
	{

	}

	MoveToAboutPoint::~MoveToAboutPoint()
	{

	}

	Rotate::Rotate(Shape* root, double angle, const Vector& axis, double runtime, double lagtime) :
		Animation(root, runtime, lagtime),
		m_dAngle(angle),
		m_Axis(axis)
	{

	}

	Rotate::~Rotate()
	{

	}

	void Rotate::Begin()
	{
		Animation::Begin();
		m_pTargetShape->Rotate(m_dAngle, m_Axis);
	}

	void Rotate::Update(Shape* shape, unsigned int frameCount)
	{
		Animation::Update(shape, frameCount);
		double prevAlpha = frameCount == 0 ? 0.0 : GetAlpha(frameCount - 1);
		double alpha = GetAlpha(frameCount);

		shape->RotateAboutPoint(m_dAngle * (alpha - prevAlpha), m_Axis, m_pRootShape->Position());
	}

	void Rotate::Finish()
	{
		m_pRootShape->Position(m_pTargetShape->Position());
	}

	void Rotate::ApplyChangeAfter(Shape* shape, double time)
	{
		Clip(time, 0, m_dRuntime);
		unsigned int frameCount = (unsigned int)(time * m_nFrameRate);
		frameCount = frameCount == 0 ? 0 : frameCount - 1;
		double alpha = GetAlpha(frameCount);
		shape->Rotate(m_dAngle * alpha, m_Axis);
	}

	RotateAboutPoint::RotateAboutPoint(Shape* shape, double angle, const Vector& axis, const Point& aboutPoint, double runtime, double lagtime) :
		Rotate(shape, angle, axis, runtime, lagtime),
		m_AboutPoint(aboutPoint)
	{

	}

	RotateAboutPoint::~RotateAboutPoint()
	{

	}

	void RotateAboutPoint::Begin()
	{
		Animation::Begin();
		m_pTargetShape->RotateAboutPoint(m_dAngle, m_Axis, m_AboutPoint);
	}

	void RotateAboutPoint::Update(Shape* shape, unsigned int frameCount)
	{
		Animation::Update(shape, frameCount);
		double prevAlpha = frameCount == 0 ? 0.0 : GetAlpha(frameCount - 1);
		double alpha = GetAlpha(frameCount);

		shape->RotateAboutPoint(m_dAngle * (alpha - prevAlpha), m_Axis, m_AboutPoint);
	}

	void RotateAboutPoint::Finish()
	{
		m_pRootShape->Position(m_pTargetShape->Position());
	}

	void RotateAboutPoint::ApplyChangeAfter(Shape* shape, double time)
	{
		Clip(time, 0, m_dRuntime);
		unsigned int frameCount = (unsigned int)(time * m_nFrameRate);
		frameCount = frameCount == 0 ? 0 : frameCount - 1;
		double alpha = GetAlpha(frameCount);
		shape->RotateAboutPoint(m_dAngle * alpha, m_Axis, m_AboutPoint);
	}

	Point RotateAboutPoint::AboutPoint() const
	{
		return m_AboutPoint;
	}
}