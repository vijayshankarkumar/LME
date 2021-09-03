#include "Scene/Scene.h"

namespace laal
{
	Scene::Scene() :
		m_nResolutionWidth(DEFAULT_PIXEL_WIDTH),
		m_nResolutionHeight(DEFAULT_PIXEL_HEIGHT),
		m_sMovieFile("LaalMathEngine")
	{

	}

	Scene::~Scene()
	{
		delete m_pRootElement;
		delete m_pRootShape;
		delete m_pRenderer;
		delete m_pCamera;
		delete m_pWriter;
	}

	void Scene::SetUp()
	{
		m_pRootElement = new Element();
		m_pRootShape = new Shape();

		m_pRootElement->Width(m_dFrameWidth);
		m_pRootElement->Height(m_dFrameHeight);
		m_pRootElement->SetShape(m_pRootShape);

		m_pRenderer = new Renderer();
		m_pRenderer->RootShape(m_pRootShape);
		m_pRenderer->AnimationsArray(m_Animations);

		m_pCamera = new Camera(m_dFrameWidth, m_dFrameHeight, m_nResolutionWidth, m_nResolutionHeight);
		m_pCamera->SetRootShape(m_pRootShape);
		m_pRenderer->SetCamera(m_pCamera);

		m_pWriter = new MovieWriter(m_sMovieFile, m_nResolutionWidth, m_nResolutionHeight);
		m_pRenderer->SetMovieWriter(m_pWriter);
	}

	void Scene::Play()
	{
		ProcessAnimations();
		m_pRenderer->AnimationsArray(m_Animations);
		m_pRenderer->Render();
		m_Animations.clear();
	}

	void Scene::Wait(double time)
	{
		m_pRenderer->RepeatLast(time);
	}

	void Scene::Finish()
	{
		m_Animations.clear();
	}

	Shape* Scene::GetRootShape() const
	{
		return m_pRootShape;
	}

	Element* Scene::GetRootElement() const
	{
		return m_pRootElement;
	}

	Renderer* Scene::GetRenderer() const
	{
		return m_pRenderer;
	}

	Camera* Scene::GetCamera() const
	{
		return m_pCamera;
	}

	void Scene::ProcessAnimations()
	{
		for (unsigned int i = 0; i < m_Animations.size() - 1; i++)
		{
			Animation* firstAnim = m_Animations[i];
			for (unsigned j = i + 1; j < m_Animations.size(); j++)
			{
				Animation* secondAnim = m_Animations[j];
				if (firstAnim->RootShape() == secondAnim->RootShape())
				{
					firstAnim->ApplyChangeAfter(secondAnim->TargetShape(), secondAnim->Runtime());
					secondAnim->ApplyChangeAfter(firstAnim->TargetShape(), firstAnim->Runtime());
				}
			}
		}
	}

	void Scene::Add(Shape* shape)
	{
		m_pRootShape->Add(shape);
	}

	void Scene::Remove(Shape* shape)
	{
		m_pRootShape->Remove(shape);
	}

	void Scene::Add(Animation* animation)
	{
		m_Animations.push_back(animation);
	}

	void Scene::Remove(Animation* animation)
	{
		auto it = std::find(m_Animations.begin(), m_Animations.end(), animation);
		if (it == m_Animations.end())
		{
			return;
		}
		m_Animations.erase(it);
	}

	void Scene::MovieFile(const std::string& movieFile)
	{
		m_sMovieFile = movieFile;
	}

	std::string Scene::MovieFile() const
	{
		return m_sMovieFile;
	}

	void Scene::Resolution(unsigned int width, unsigned int height)
	{
		m_nResolutionWidth = width;
		m_nResolutionHeight = height;
	}

	unsigned int Scene::ResolutionWidth() const
	{
		return m_nResolutionWidth;
	}

	unsigned int Scene::ResolutionHeight() const
	{
		return m_nResolutionHeight;
	}

	void Scene::FrameWidth(double frameWidth)
	{
		m_dFrameWidth = frameWidth;
	}

	void Scene::FrameHeight(double frameHeight)
	{
		m_dFrameHeight = frameHeight;
	}

	double Scene::FrameWidth() const
	{
		return m_dFrameWidth;
	}

	double Scene::FrameHeight() const
	{
		return m_dFrameHeight;
	}
}