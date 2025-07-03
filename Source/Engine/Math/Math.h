#pragma once
#include <algorithm>

namespace shovel
{
	namespace math
	{

		constexpr float pi = 3.1415926535897932384626433832795f;
		constexpr float twoPi = 2 * pi;
		constexpr float halfPi = pi / 2;

		constexpr float radToDeg(float rad)
		{
			return rad * (180 / pi);
		}

		constexpr float degTorad(float deg)
		{
			return deg * (pi / 180);
		}

		using std::min;
		using std::max;
		using std::clamp;
	}
}