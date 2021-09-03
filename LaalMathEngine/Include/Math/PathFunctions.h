#ifndef LAAL_PATH_FUNCTIONS_HPP
#define LAAL_PATH_FUNCTIONS_HPP

#include <gmtl/gmtl.h>
#include "Math/SimpleFunctions.h"

typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal
{
	void StraightPath(Point& value, const Point& start, const Point& end, double alpha);
}

#endif // !LAAL_PATH_FUNCTIONS_HPP
