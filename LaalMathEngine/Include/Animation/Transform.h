#ifndef LAAL_TRANSFORM_HPP
#define LAAL_TRANSFORM_HPP

#include "Animation/Animation.h"

namespace laal
{
	//! ============================================
	//! [Transform]
	//! ============================================
	class Transform : public Animation
	{
	public:

		Transform(Shape* root, double runtime, double lagtime);

		virtual ~Transform();

		void Begin() override;

		void Update(Shape* shape, unsigned int frameCount) override;

		Shape* GetTargetShape() const;

		void Finish() override;
	};

	//! ============================================
	//! [Translate]
	//! ============================================
	class Translate : public Animation
	{
	protected:

		Vector m_TranslateVector;

	public:

		Translate(Shape* root, double x, double y, double z, double runtime, double lagtime);

		Translate(Shape* root, const Vector& alongVector, double runtime, double ladtime);

		virtual ~Translate();

		void Begin() override;

		void Update(Shape* shape, unsigned int frameCount) override;

		void Finish() override;

		void ApplyChangeAfter(Shape* shape, double time);
	};

	//! ============================================
	//! [TranslateAboutPoint]
	//! ============================================
	class TranslateAboutPoint : public Translate
	{
	public:

		TranslateAboutPoint(Shape* root, const Vector& alongVector, const Point& aboutPoint, double runtime, double lagtime);

		virtual ~TranslateAboutPoint();
	};


	//! ============================================
	//! [Scale]
	//! ============================================
	class Scale : public Animation
	{
	protected:

		Vector m_ScaleVector;

	public:

		Scale(Shape* root, double scaleFactor, double runtime, double lagtime);

		Scale(Shape* root, double sx, double sy, double sz, double runtime, double lagtime);
		
		Scale(Shape* root, const Vector& scaleVector, double runtime, double lagtime);

		virtual ~Scale();

		void Begin() override;
		
		void Update(Shape* shape, unsigned int frameCount) override;

		void Finish() override;

		void ApplyChangeAfter(Shape* shape, double time);
	};

	//! ============================================
	//! [Strech]
	//! ============================================
	class Strech : public Scale
	{
	public:
		
		Strech(Shape* root, double strechFactor, const Vector& axis, double runtime, double lagtime);

		virtual ~Strech();
	};

	//! ============================================
	//! [ScaleAboutPoint]
	//! ============================================
	class ScaleAboutPoint : public Scale
	{
	protected:

		Point m_AboutPoint;

	public:

		ScaleAboutPoint(Shape* root, const Vector& scaleVector, const Point& aboutPoint, double runtime, double lagtime);

		ScaleAboutPoint(Shape* root, double scaleFactor, const Point& aboutPoint, double runtime, double lagtime);

		virtual ~ScaleAboutPoint();

		void Begin() override;

		void Update(Shape* shape, unsigned int frameCount) override;

		void Finish() override;

		void ApplyChangeAfter(Shape* shape, double time);

		Point AboutPoint() const;
	};

	//! ============================================
	//! [MoveTo]
	//! ============================================
	class MoveTo : public Translate
	{
	public:

		MoveTo(Shape* root, double destX, double destY, double destZ, double runtime, double lagtime);

		MoveTo(Shape* root, const Point& dest, double runtime, double lagtime);

		virtual ~MoveTo();
	};

	//! ============================================
	//! [MoveToAboutPoint]
	//! ============================================
	class MoveToAboutPoint : public Translate
	{
	public:

		MoveToAboutPoint(Shape* root, const Point& dest, const Point& aboutPoint, double runtime, double lagtime);

		virtual ~MoveToAboutPoint();
	};

	//! ============================================
	//! [Rotate]
	//! ============================================
	class Rotate : public Animation
	{
	protected:

		double m_dAngle;

		Vector m_Axis;

	public:

		Rotate(Shape* root, double angle, const Vector& axis, double runtime, double lagtime);

		virtual ~Rotate();

		void Begin() override;
		
		void Update(Shape* shape, unsigned int frameCount) override;

		void Finish() override;

		void ApplyChangeAfter(Shape* shape, double time) override;
	};

	//! ============================================
	//! [RotateAboutPoint]
	//! ============================================
	class RotateAboutPoint : public Rotate
	{
	protected:

		Point m_AboutPoint;

	public:

		RotateAboutPoint(Shape* root, double angle, const Vector& axis, const Point& aboutPoint, double runtime, double lagtime);

		virtual ~RotateAboutPoint();

		void Begin() override;

		void Update(Shape* shape, unsigned int frameCount) override;

		void Finish() override;

		void ApplyChangeAfter(Shape* shape, double time) override;

		Point AboutPoint() const;
	};
}

#endif // !LAAL_TRANSFORM_HPP
