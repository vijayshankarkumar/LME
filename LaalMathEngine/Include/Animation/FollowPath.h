#ifndef LAAL_FOLLOW_PATH_HPP
#define LAAL_FOLLOW_PATH_HPP

#include <functional>

#include "Animation/Animation.h"

namespace laal
{
	//! ============================================
	//! [FollowPath]
	//! ============================================
	class FollowPath : public Animation
	{
	protected:

		std::function<double(double)> m_PathXt;

		std::function<double(double)> m_PathYt;

		double m_dTMin;

		double m_dTMax;

	public:

		FollowPath(
			Shape* root, 
			std::function<double(double)> pathXt, 
			std::function<double(double)> pathYt, 
			double tMin, 
			double tMax, 
			double runtime, 
			double lagtime
		);

		virtual ~FollowPath();

		double GetT(double alpha);

		Point GetPointAtT(double t);

		void Begin() override;

		void Update(Shape* shape, unsigned int frameCount) override;

		void ApplyChangeAfter(Shape* shape, double time) override;

		void Finish() override;
	};
}

#endif // !LAAL_FOLLOW_PATH_HPP