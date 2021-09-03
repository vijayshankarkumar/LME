#ifndef LAAL_FADING_HPP
#define LAAL_FADING_HPP

#include "Animation/Animation.h"

namespace laal
{
	//! ============================================
	//! [Fade]
	//! ============================================
	class Fade : public Animation
	{
	protected:

		double m_dStartFillOpacity;

		double m_dEndFillOpacity;

		double m_dStartStrokeOpacity;

		double m_dEndStrokeOpacity;

	public:

		Fade(Shape* root, std::pair<double, double> strokeOpacity, std::pair<double, double> fillOpacity, double runtime, double lagtime);

		virtual ~Fade();

		void Begin() override;

		void Update(Shape* shape, unsigned int frameCount);

		void Finish() override;
	};
	//! ============================================
	//! [FadeIn]
	//! ============================================
	class FadeIn : public Fade
	{

	public:

		FadeIn(Shape* root, double runtime, double lagtime);

		virtual ~FadeIn();
	};

	//! ============================================
	//! [FadeOut]
	//! ============================================
	class FadeOut : public Fade
	{

	public:

		FadeOut(Shape* root, double runtime, double lagtime);

		virtual ~FadeOut();
	};
}

#endif // !LAAL_FADING_HPP