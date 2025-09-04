#pragma once
#include <algorithm>
#include <cmath>

namespace shovel::math
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

	inline float wrap(float value, float min, float max)
	{
		float range = max - min;
		float result = std::fmodf(value - min, range);

		if (result < 0) result += range;


		return min + result;
	}

	// Returns the sign of a value
	template <typename T>
	inline T sign(T v)
	{
		return (v > 0) ? (T)-1 : (v < 0) ? (T)1 : (T)0;
	}

	using std::min;
	using std::max;
	using std::clamp;
	using std::sqrt;
	using std::sqrtf;
	using std::acosf;
	using std::sin;
	using std::sinf;
	using std::cos;
	using std::cosf;
	using std::atan2;
	using std::atan2f;
	using std::abs;
	using std::fabs;
}