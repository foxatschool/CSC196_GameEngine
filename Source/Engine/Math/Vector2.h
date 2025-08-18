#pragma once
#include <cassert>
#include "Math.h"
#include <iostream>

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

		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

		// square root  (x^2 + y^2)
		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return shovel::math::sqrtf(LengthSqr()); }
	
		Vector2 Normalized() const { return *this / Length(); }

		float Angle() const { return math::atan2f(y, x); };

		Vector2 Rotate(float radians) const 
		{
			Vector2 v;

			v.x = x * math::cosf(radians) - y * math::sinf(radians);
			v.y = x * math::sinf(radians) + y * math::cosf(radians);

			return v;
		}

		// Returns the dot product of two vectors
		static float Dot(const Vector2 a, const Vector2 b)
		{
			return (a.x * b.x) + (a.y * b.y);
		}

		// Returns the cross product of two vectors
		static float Cross(const Vector2& a, const Vector2& b)
		{
			return (a.x * b.y) - (b.x * a.y);
		}

		// Returns the angle between two vectors in radians
		static float AngleBetween(const Vector2& a, const Vector2& b)
		{
			return math::acosf(Dot(a, b));
		}

		// Returns the signed angle between two vectors in radians
		static float SignedAngleBetween(const Vector2& a, const Vector2& b)
		{
			float x = Dot(a, b);
			float y = Cross(a, b);

			return math::atan2f(y, x);
		}

	};

	template<typename T>
	std::ostream& operator << (std::ostream& stream, const Vector2<T>& v)
	{
		stream << "{" << v.x << " , " << v.y << "}";

		return stream;
	}

	template<typename T>
	std::istream& operator >> (std::istream& stream, Vector2<T>& v)
	{
		char ch = '\0';

		// { x, y }

		if (!(stream >> std::ws >> ch) || ch != '{')
		{
			stream.setstate(std::ios::failbit);
			return stream; // if the first character is not an opening brace, return the stream
		}// read the opening brace
		if(!(stream >> std::ws >> v.x))
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
		if (!(stream >> std::ws >> ch))
		{
			stream.setstate(std::ios::failbit);
			return stream; // if there is no closing character, return the stream
		}// read the closing brace


		return stream;
	}

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}
