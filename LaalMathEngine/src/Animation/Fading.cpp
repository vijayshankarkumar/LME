#include "Animation/Fading.h"

namespace laal
{
	Fade::Fade(Shape* root, std::pair<double, double> strokeOpacity, std::pair<double, double> fillOpacity, double runtime, double lagtime) :
		Animation(root, runtime, lagtime),
		m_dStartFillOpacity(fillOpacity.first),
		m_dEndFillOpacity(fillOpacity.second),
		m_dStartStrokeOpacity(strokeOpacity.first),
		m_dEndStrokeOpacity(strokeOpacity.second)
	{

	}

	Fade::~Fade()
	{

	}

	void Fade::Begin()
	{
		Animation::Begin();
		m_pRootShape->StrokeOpacity(m_dStartStrokeOpacity);
		m_pRootShape->FillOpacity(m_dStartFillOpacity);
	}

	void Fade::Update(Shape* shape, unsigned int frameCount)
	{
		double alpha = GetAlpha(frameCount);
		double strokeOpacity, fillOpacity;
		InterpolateDouble(strokeOpacity, m_dStartStrokeOpacity, m_dEndStrokeOpacity, alpha);
		InterpolateDouble(fillOpacity, m_dStartFillOpacity, m_dEndFillOpacity, alpha);
		shape->StrokeOpacity(strokeOpacity);
		shape->FillOpacity(fillOpacity);
	}

	void Fade::Finish()
	{
		m_pRootShape->StrokeOpacity(m_dEndStrokeOpacity);
		m_pRootShape->FillOpacity(m_dEndFillOpacity);
	}

	FadeIn::FadeIn(Shape* root, double runtime, double lagtime) :
		Fade(root, std::make_pair(0.0, root->StrokeOpacity()), std::make_pair(0.0, root->FillOpacity()), runtime, lagtime)
	{

	}

	FadeIn::~FadeIn()
	{

	}

	FadeOut::FadeOut(Shape* root, double runtime, double lagtime) :
		Fade(root, std::make_pair(root->StrokeOpacity(), 0.0), std::make_pair(root->FillOpacity(), 0.0), runtime, lagtime)
	{

	}

	FadeOut::~FadeOut()
	{

	}
}