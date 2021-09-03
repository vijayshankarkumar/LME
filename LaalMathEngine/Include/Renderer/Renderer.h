#ifndef LAAL_RENDERER_HPP
#define LAAL_RENDERER_HPP

#include "Camera/Camera.h"
#include "Animation/Animation.h"
#include "MovieMaker/MovieMaker.h"

namespace laal
{
	//! ============================================
	//! [Renderer]
	//! ============================================
	class Renderer
	{

	protected:

		Camera* m_pCamera;

		Shape* m_pRootShape;

		MovieWriter* m_pWriter;

		unsigned int m_nFrameRate;

		std::vector<Animation*> m_Animations;

	public:

		Renderer();

		~Renderer();

		void Render();

		void RepeatLast(double time);

		unsigned int TotalFrames();

		void RootShape(Shape* root);

		Shape* RootShape() const;

		void AnimationsArray(const std::vector<Animation*>& animations);

		std::vector<Animation*> AnimationsArray() const;

		void SetCamera(Camera* camera);

		Camera* GetCamera() const;

		void SetMovieWriter(MovieWriter* movieWriter);

		MovieWriter* GetMovieWriter() const;

		void FrameRate(unsigned int frameRate);

		unsigned int FrameRate() const;
	};
}
#endif // !LAAL_RENDERER_HPP
