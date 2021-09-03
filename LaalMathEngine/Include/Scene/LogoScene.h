#ifndef LAAL_LOGO_SCENE_HPP
#define LAAL_LOGO_SCENE_HPP

#include "Scene/Scene.h"
#include "Shape/ShapeGroup.h"
#include "Shape/Text.h"
#include "Geometry/Polygon.h"
#include "Animation/Transform.h"
#include "Animation/Fading.h"

namespace laal
{
	//! ============================================
	//! [LogoScene]
	//! ============================================
	class LogoScene : public Scene
	{
	public:

		void Construct() override;

		void AnimateLogo();
	};
}
#endif // !LAAL_LOGO_SCENE_HPP
