#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3
{
public:
	union
	{
		double x;
		double r;
	};
	union 
	{
		double y;
		double g;
	};
	union
	{
		double z;
		double b;
	};
public:
	vec3() :
		x{ 0 }, y{ 0 }, z{ 0 }
	{

	}
	vec3(double x, double y, double z ) :
		x{ x }, y{ y }, z{ z }
	{

	}
	vec3 operator-() const { return vec3(-x, -y, -z); }
	vec3& operator+=(const vec3& v) {
		x += v.x;
		y += v.y;
		y += v.y;
		return *this;
	}

	vec3& operator*=(const double t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}
	vec3& operator/=(const double t) {
		return *this *= 1 / t;
	}
	double length() const {
		return sqrt(length_squared());
	}

	double length_squared() const {
		return x * x + y * y + z * z;
	}

	
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

// vec3 Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.x, t * v.y, t * v.z);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.x * v.x
		+ u.y * v.y
		+ u.z * v.z;
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

#endif