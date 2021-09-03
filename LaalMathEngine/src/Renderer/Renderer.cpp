#include "Renderer/Renderer.h"

namespace laal
{
	Renderer::Renderer() :
		m_nFrameRate(DEFAULT_FRAME_RATE)
	{

	}

	Renderer::~Renderer()
	{
		
	}

	void Renderer::Render()
	{
		//std::cout << "in the render()..." << std::endl;
		for (Animation* animation : m_Animations)
		{
			animation->Begin();
			//std::cout << "in the render() loop..." << std::endl;
		}
		unsigned int totalFrames = TotalFrames();
		for (unsigned int i = 0; i < totalFrames; i++)
		{
			for (Animation* animation : m_Animations)
			{
				animation->Update();
			}
			m_pCamera->Capture();
			m_pWriter->AddFrame(m_pCamera->ImageData());
		}

		for (Animation* animation : m_Animations)
		{
			animation->Finish();
		}
		m_pCamera->Capture();
		m_pWriter->AddFrame(m_pCamera->ImageData());
	}

	void Renderer::RepeatLast(double time)
	{
		for (unsigned int i = 0; i < (unsigned int)(time * (double)m_nFrameRate); i++)
		{
			m_pWriter->AddFrame(m_pCamera->ImageData());
		}
	}

	unsigned int Renderer::TotalFrames()
	{
		unsigned int totalFrames = 0;
		for (Animation* animation : m_Animations)
		{
			totalFrames = std::max(totalFrames, animation->TotalFrames());
		}
		return totalFrames;
	}

	void Renderer::RootShape(Shape* root)
	{
		m_pRootShape = root;
	}

	Shape* Renderer::RootShape() const
	{
		return m_pRootShape;
	}

	void Renderer::AnimationsArray(const std::vector<Animation*>& animations)
	{
		m_Animations = animations;
	}

	std::vector<Animation*> Renderer::AnimationsArray() const
	{
		return m_Animations;
	}

	void Renderer::SetCamera(Camera* camera)
	{
		m_pCamera = camera;
	}

	Camera* Renderer::GetCamera() const
	{
		return m_pCamera;
	}

	void Renderer::SetMovieWriter(MovieWriter* movieWriter)
	{
		m_pWriter = movieWriter;
	}

	MovieWriter* Renderer::GetMovieWriter() const
	{
		return m_pWriter;
	}

	void Renderer::FrameRate(unsigned int frameRate)
	{
		m_nFrameRate = frameRate;
	}

	unsigned int Renderer::FrameRate() const
	{
		return m_nFrameRate;
	}
}