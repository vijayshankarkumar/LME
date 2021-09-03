#ifndef LAAL_SCENE_H
#define LAAL_SCENE_H

#include "Node/Element.h"
#include "Renderer/Renderer.h"

namespace laal
{
	//! ============================================
	//! [Scene]
	//! ============================================
	class Scene
	{

	protected:

		Element* m_pRootElement;

		Shape* m_pRootShape;

		Renderer* m_pRenderer;
		
		Camera* m_pCamera;

		MovieWriter* m_pWriter;

		std::vector<Animation*> m_Animations;

		std::string m_sMovieFile;

		unsigned int m_nResolutionWidth;

		unsigned int m_nResolutionHeight;

		double m_dFrameWidth;

		double m_dFrameHeight;

	public:

		Scene();

		virtual ~Scene();

		virtual void SetUp();

		void Play();

		void Wait(double time);

		void Finish();

		virtual void Construct() = 0;

		Shape* GetRootShape() const;

		Element* GetRootElement() const;

		Renderer* GetRenderer() const;

		Camera* GetCamera() const;

		void ProcessAnimations();

		void Add(Shape* shape);

		void Remove(Shape* shape);

		void Add(Animation* animation);

		void Remove(Animation* animation);

		void MovieFile(const std::string& movieFile);

		std::string MovieFile() const;

		void Resolution(unsigned int width, unsigned int height);

		unsigned int ResolutionWidth() const;

		unsigned int ResolutionHeight() const;

		void FrameWidth(double frameWidth);

		void FrameHeight(double frameHeight);

		double FrameWidth() const;

		double FrameHeight() const;
	};
}

#endif // !LAAL_SCENE_HPP
