#pragma once
#include <cassert>
#include "Math.h"

namespace shovel
{
	template<typename T>
	struct Vector3
	{
		T x, y, z;
		Vector3() = default;
		Vector3(T x, T y, T z) :
			x{ x },
			y{ y },
			z{ z }
		{
		}
		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

		Vector3 operator + (const Vector3& v) const { return Vector3{ x + v.x, y + v.y, z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ x - v.x, y - v.y, z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ x * v.x, y * v.y, z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ x / v.x, y / v.y, z / v.z }; }

		Vector3 operator + (float s) const { return Vector3{ x + s, y + s, z + s }; }
		Vector3 operator - (float s) const { return Vector3{ x - s, y - s, z - s }; }
		Vector3 operator * (float s) const { return Vector3{ x * s, y * s, z * s }; }
		Vector3 operator / (float s) const { return Vector3{ x / s, y / s, z / s }; }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		Vector3& operator += (float s) { x += s.x; y += s.y; z += s.z; }
		Vector3& operator -= (float s) { x -= s.x; y -= s.y; z -= s.z; }
		Vector3& operator *= (float s) { x *= s.x; y *= s.y; z *= s.z; }
		Vector3& operator /= (float s) { x /= s.x; y /= s.y; z /= s.z; }

		// square root  (x^2 + y^2 + z^2)
		float LengthSqr() { return (x * x) + (y * y) + (z * z); }
		float Length() { return shovel::math::sqrtf(LengthSqr()); }
	};

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}
