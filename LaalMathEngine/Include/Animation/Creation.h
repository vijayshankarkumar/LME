#ifndef LAAL_CREATION_HPP
#define LAAL_CREATION_HPP

#include "Animation/Animation.h"

namespace laal
{
	//! ============================================
	//! [Creation]
	//! ============================================
	class Create : public Animation
	{

	protected:

		std::map<Shape*, STYLE_TYPE> m_FillTypesMap;

		std::map<Shape*, std::vector<bool>> m_ClosedMap;

		std::map<Shape*, double> m_OpacitiesMap;

	public:

		Create(Shape* root, double runtime, double lagtime);

		virtual ~Create();

		void Begin() override;

		void SetMap(Shape* root);

		void Update(Shape* root, unsigned int frameCount);
	};
}

#endif // !LAAL_CREATION_HPP
