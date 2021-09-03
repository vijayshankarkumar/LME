#include "Animation/Animation.h"

namespace laal
{
	Animation::Animation() :
		m_dRuntime(0.0),
		m_dLagtime(0.0),
		m_nFrameRate(DEFAULT_FRAME_RATE),
		m_EaseFunction(EaseSmooth),
		m_nFrameCount(0),
		m_dStartOffset(0.0),
		m_bAnimationStarted(false)
	{

	}

	Animation::Animation(Shape* root, double runtime, double lagtime) :
		m_pRootShape(root),
		m_dRuntime(runtime),
		m_dLagtime(lagtime),
		m_nFrameRate(DEFAULT_FRAME_RATE),
		m_EaseFunction(EaseSmooth),
		m_nFrameCount(0),
		m_dStartOffset(0.0),
		m_bAnimationStarted(false)
	{
		SetShape();
	}

	Animation::~Animation()
	{
		DeleteShape(m_pStartShape);
		DeleteShape(m_pTargetShape);
	}

	void Animation::Begin()
	{
		m_IsUpdatingMap.clear();
		m_StartMap[m_pRootShape] = m_pStartShape;
		m_TargetMap[m_pRootShape] = m_pTargetShape;
		m_IsUpdatingMap[m_pRootShape] = true;
		if (!m_pRootShape->IsLeaf())
		{
			std::vector<Shape*> childShapes = m_pRootShape->ChildShapes();
			std::vector<Shape*> childShapesStart = m_pStartShape->ChildShapes();
			std::vector<Shape*> childShapesTarget = m_pTargetShape->ChildShapes();
			for (unsigned int idx = 0; idx < childShapes.size(); idx++)
			{
				m_StartMap[childShapes[idx]] = childShapesStart[idx];
				m_TargetMap[childShapes[idx]] = childShapesTarget[idx];
				m_IsUpdatingMap[childShapes[idx]] = true;
			}
		}
		if ((unsigned int)(m_dStartOffset * (double)m_nFrameRate) == 0)
		{
			m_bAnimationStarted = true;
		}
	}

	void Animation::Update()
	{
		if (!m_bAnimationStarted)
		{
			m_nFrameCount++;
			m_bAnimationStarted = m_nFrameCount >= (unsigned int)((double)m_nFrameRate * m_dStartOffset);
			m_nFrameCount = m_bAnimationStarted ? 0 : m_nFrameCount;
			return;
		}
		if (!m_IsUpdatingMap[m_pRootShape])
		{
			return;
		}
		if (m_pRootShape->IsLeaf())
		{
			Update(m_pRootShape, m_nFrameCount);
			m_IsUpdatingMap[m_pRootShape] = m_nFrameCount < (unsigned int)(m_dRuntime * (double)m_nFrameRate) - 1;
			if (!m_IsUpdatingMap[m_pRootShape])
			{
				m_pRootShape->BecomeShape(m_pTargetShape);
			}
		}

		std::vector<Shape*> childShapes = m_pRootShape->ChildShapes();
		for (unsigned int idx = 0; idx < childShapes.size(); idx++)
		{
			Shape* shape = childShapes[idx];
			if (!m_IsUpdatingMap[shape])
			{
				continue;
			}

			unsigned int frameOffset = (unsigned int)((double)idx * m_dLagtime * (double)m_nFrameRate);
			if (m_nFrameCount >= frameOffset)
			{
				if (m_nFrameCount - frameOffset >= (unsigned int)(m_dRuntime * (double)m_nFrameRate) - 1)
				{
					//std::cout << "become is called..." << std::endl;
					shape->BecomeShape(m_TargetMap[shape]);
					m_IsUpdatingMap[shape] = false;
					continue;
				}
				Update(shape, m_nFrameCount - frameOffset);
			}
		}
		m_nFrameCount++;
	}

	void Animation::Finish()
	{
		
	}

	void Animation::Update(Shape* shape, unsigned int frameCount)
	{
		//std::cout << "called from animation update()..." << std::endl;
	}

	void Animation::ApplyChangeAfter(Shape* shape, double time)
	{
		Clip(time, 0, m_dRuntime);
		unsigned int frameCount = (unsigned int)(time * (double)m_nFrameRate);
		frameCount = frameCount == 0 ? 0 : frameCount - 1;
		Update(shape, frameCount);
	}

	void Animation::SetShape()
	{
		m_pStartShape = new Shape();
		CopyShape(m_pRootShape, m_pStartShape);

		m_pTargetShape = new Shape();
		CopyShape(m_pRootShape, m_pTargetShape);
	}

	void Animation::CopyShape(Shape* fromShape, Shape* toShape)
	{
		fromShape->Copy(toShape);
		if (fromShape->IsLeaf())
		{
			return;
		}
		
		for (Shape* shape : fromShape->ChildShapes())
		{
			Shape* childShape = new Shape();
			CopyShape(shape, childShape);
			toShape->Add(childShape);
		}
	}

	void Animation::DeleteShape(Shape* root)
	{
		if (root->IsLeaf())
		{
			delete root;
			return;
		}

		for (Shape* shape : root->ChildShapes())
		{
			DeleteShape(shape);
		}
		delete root;
	}

	Shape* Animation::RootShape() const
	{
		return m_pRootShape;
	}

	Shape* Animation::StartShape() const
	{
		return m_pStartShape;
	}

	Shape* Animation::TargetShape() const
	{
		return m_pTargetShape;
	}

	double Animation::GetAlpha(unsigned int frameCount)
	{
		frameCount++;
		double t = (double)frameCount / (m_dRuntime * (double)m_nFrameRate);
		Clip(t, 0.0, 1.0);
		return m_EaseFunction(t);
	}

	void Animation::EaseFunction(std::function<double(double)> easeFunciton)
	{
		m_EaseFunction = easeFunciton;
	}

	std::function<double(double)> Animation::EaseFunction() const
	{
		return m_EaseFunction;
	}

	void Animation::Runtime(double runtime)
	{
		m_dRuntime = runtime;
	}

	double Animation::Runtime() const
	{
		return m_dRuntime;
	}

	unsigned int Animation::TotalFrames()
	{
		double sz = (double)(m_pRootShape->ChildShapes().size());
		return (unsigned int)((((sz - 1.0) * m_dLagtime) + m_dRuntime + m_dStartOffset) * (double)m_nFrameRate);
	}
	
	void Animation::Lagtime(double lagtime)
	{
		m_dLagtime = lagtime;
	}

	double Animation::Lagtime() const
	{
		return m_dLagtime;
	}

	void Animation::FrameRate(unsigned int frameRate)
	{
		m_nFrameRate = frameRate;
	}

	unsigned int Animation::FrameRate() const
	{
		return m_nFrameRate;
	}

	void Animation::StartOffset(double startOffset)
	{
		m_dStartOffset = startOffset;
	}

	double Animation::StartOffset() const
	{
		return m_dStartOffset;
	}
}