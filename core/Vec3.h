#pragma once

#include <cmath>
#include <iostream>

namespace ch
{

template <typename T = float>
class Vec3
{
  public:
	T x, y, z;

	Vec3(T x, T y, T z) noexcept : x{x}, y{y}, z{z} {}
	Vec3() noexcept : x{0}, y{0}, z{0} {}

	T &operator[](int i)
	{
		return ((&x)[i]);
	}

	const T &operator[](int i) const
	{
		return ((&x)[i]);
	}

	Vec3<T> &operator*=(T s)
	{
		x *= s;
		y *= s;
		z *= s;
		return (*this);
	}

	Vec3<T> &operator/=(T s)
	{
		s = 1.0f / s;
		x *= s;
		y *= s;
		z *= s;
		return (*this);
	}

	Vec3<T> &operator+=(const Vec3<T> &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	Vec3<T> &operator-=(const Vec3<T> &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}
};

template <typename T>
inline bool operator==(const Vec3<T> &v1, const Vec3<T> &v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

template <typename T>
inline Vec3<T> operator+(const Vec3<T> &v1, const Vec3<T> &v2)
{
	return Vec3<T>{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T> &v1, const Vec3<T> &v2)
{
	return Vec3<T>{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T> &v)
{
	return Vec3<T>{-v.x, -v.y, -v.z};
}

template <typename T>
inline T operator*(const Vec3<T> &v1, const Vec3<T> &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T> &v, const T &s)
{
	return Vec3<T>{v.x * s, v.y * s, v.z * s};
}

template <typename T>
inline Vec3<T> operator*(const T &s, const Vec3<T> &v)
{
	return Vec3<T>{v.x * s, v.y * s, v.z * s};
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T> &v, T s)
{
	s = 1.0f / s;
	return Vec3<T>{v.x * s, v.y * s, v.z * s};
}

template <typename T>
inline T dot(const Vec3<T> &v1, const Vec3<T> &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2)
{
	return Vec3<T>{v1.y * v2.z - v1.z * v2.y,
				   -(v1.x * v2.z + v1.z * v2.x),
				   v1.x * v2.y - v1.y * v2.x};
}

template <typename T>
inline Vec3<T> element_wise_multiply(const Vec3<T> &v1, const Vec3<T> &v2)
{
	return Vec3<T>{v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

template <typename T>
inline T magnitude(const Vec3<T> &v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

template <typename T>
inline Vec3<T> normalize(const Vec3<T> &v)
{
	auto m = magnitude(v);
	return Vec3<T>{v.x / m, v.y / m, v.z / m};
}

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Vec3<T> &v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

} // namespace ch
