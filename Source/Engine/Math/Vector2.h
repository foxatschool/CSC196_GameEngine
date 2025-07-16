#pragma once
#include <cassert>
#include "Math.h"

namespace shovel
{
	template<typename T>
	struct Vector2
	{
		union data
		{
			struct { T x, y; };
			struct { T u, v; };
		};

		T x, y;
		Vector2() = default;
		Vector2(T x, T y) :
			x{ x },
			y{ y }
		{}


		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		Vector2& operator += (float s) { x += s.x; y += s.y; }
		Vector2& operator -= (float s) { x -= s.x; y -= s.y; }
		Vector2& operator *= (float s) { x *= s.x; y *= s.y; }
		Vector2& operator /= (float s) { x /= s.x; y /= s.y; }

		// square root  (x^2 + y^2)
		float LengthSqr() { return (x * x) + (y * y); }
		float Length() { return shovel::math::sqrtf(LengthSqr()); }
	
		Vector2 Normalized() const { return *this / Length(); }

		float Angle() const { return math::atan2f(y, x); };

		Vector2 Rotate(float radians) const 
		{
			Vector2 v;

			v.x = x * math::cosf(radians) - y * math::sinf(radians);
			v.y = x * math::sinf(radians) + y * math::cosf(radians);

			return v;
		}
	};

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}
