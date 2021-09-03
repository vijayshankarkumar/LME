#include "Math/PathFunctions.h"

namespace laal
{
	void StraightPath(Point& value, const Point& start, const Point& end, double alpha)
	{
		InterpolatePoint(value, start, end, alpha);
	}
}