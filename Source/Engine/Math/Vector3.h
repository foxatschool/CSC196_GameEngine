#pragma once
#include <cassert>
#include "Math.h"
#include <iostream>

namespace shovel
{
	template<typename T>
	struct Vector3
	{
		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vector3() = default;
		Vector3(T x, T y, T z) :
			x{ x },
			y{ y },
			z{ z }
		{}		

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

	template<typename T>
	inline std::ostream& operator << (std::ostream& stream, const Vector3<T>& v)
	{
		stream << "{" << v.x << " , " << v.y << " , " << v.z << "}";

		return stream;
	}

	template<typename T>
	inline std::istream& operator >> (std::istream& stream,  Vector3<T>& v)
	{
		char ch = '\0';

		// { x , y , z }

		if (!(stream >> std::ws >> ch) || ch != '{')
		{
			stream.setstate(std::ios::failbit);
			return stream; // if the first character is not an opening brace, return the stream
		}// read the opening brace
		if (!(stream >> std::ws >> v.x))
		{
			stream.setstate(std::ios::failbit);
			return stream; // if the first value is not a number, return the stream
		}
		if (!(stream >> std::ws >> ch) || ch != ',')
		{
			stream.setstate(std::ios::failbit);
			return stream; // if the next character is not a comma, return the stream
		}// read the comma
		if (!(stream >> std::ws >> v.y))
		{
			stream.setstate(std::ios::failbit);
			return stream; // if the second value is not a number, return the stream
		}
		if (!(stream >> std::ws >> ch) || ch != ',')
		{
			stream.setstate(std::ios::failbit);
			return stream; // if the next character is not a comma, return the stream
		}// read the comma
		if (!(stream >> std::ws >> v.z))
		{
			stream.setstate(std::ios::failbit);
			return stream; // if the second value is not a number, return the stream
		}
		if (!(stream >> std::ws >> ch))
		{
			stream.setstate(std::ios::failbit);
			return stream; // if there is no closing character, return the stream
		}// read the closing brace


		return stream;
	}

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}
