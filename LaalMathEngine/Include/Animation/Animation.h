#ifndef LAAL_ANIMATION_HPP
#define LAAL_ANIMATION_HPP

#include <map>

#include "Shape/Shape.h"
#include "Math/PathFunctions.h"
#include "Math/EasingFunctions.h"

namespace laal
{
	//! ============================================
	//! [Animation]
	//! ============================================
	class Animation {

	protected:

		Shape* m_pRootShape;

		Shape* m_pStartShape;

		Shape* m_pTargetShape;

		double m_dRuntime;

		double m_dLagtime;

		double m_dStartOffset;

		unsigned int m_nFrameRate;

		std::function<double(double)> m_EaseFunction;

		std::map<Shape*, bool> m_IsUpdatingMap;

		std::map<Shape*, Shape*> m_StartMap;

		std::map<Shape*, Shape*> m_TargetMap;

		unsigned int m_nFrameCount;

		bool m_bAnimationStarted;

	public:

		Animation();

		Animation(Shape* root, double runtime, double lagtime);

		virtual ~Animation();

		virtual void Begin();

		virtual void Update();

		virtual void Finish();

		virtual void Update(Shape* shape, unsigned int frameCount);

		virtual void ApplyChangeAfter(Shape* shape, double time);

		void SetShape();

		void CopyShape(Shape* fromShape, Shape* toShape);

		void DeleteShape(Shape* root);

		Shape* RootShape() const;

		Shape* StartShape() const;

		Shape* TargetShape() const;

		double GetAlpha(unsigned int frameCount);

		void EaseFunction(std::function<double(double)> rateFunction);

		std::function<double(double)> EaseFunction() const;

		void Runtime(double runtime);

		double Runtime() const;

		virtual unsigned int TotalFrames();

		void Lagtime(double lagtime);

		double Lagtime() const;

		void FrameRate(unsigned int frameRate);

		unsigned int FrameRate() const;

		void StartOffset(double startOffset);

		double StartOffset() const;
	};
}
#endif // !LAAL_ANIMATION_HPP