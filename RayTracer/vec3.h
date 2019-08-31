#pragma once

#include <cmath>
#include <iostream>

#include "random.h"

class vec3 {
public:
	vec3() : e{0.f,0.f,0.f}  {}
	vec3(float e0, float e1, float e2) : e{ e0, e1, e2 } {}
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }
	
	inline void operator+=(const vec3& v2);
	inline void operator-=(const vec3& v2);
	inline void operator*=(const vec3& v2);
	inline void operator/=(const vec3& v2);
	inline void operator*=(float t);
	inline void operator/=(float t);

	inline float length() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); 
	}
	inline float squared_length() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	inline void make_unit_vector();

	float e[3];
};

inline void vec3::operator+=(const vec3& v2)
{
	e[0] += v2.e[0];
	e[1] += v2.e[1];
	e[2] += v2.e[2];
}

inline void vec3::operator*=(const vec3& v2)
{
	e[0] *= v2.e[0];
	e[1] *= v2.e[1];
	e[2] *= v2.e[2];
}

inline void vec3::operator/=(const vec3& v2)
{
	e[0] /= v2.e[0];
	e[1] /= v2.e[1];
	e[2] /= v2.e[2];
}

inline void vec3::operator-=(const vec3& v2)
{
	e[0] -= v2.e[0];
	e[1] -= v2.e[1];
	e[2] -= v2.e[2];
}

inline void vec3::operator*=(float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
}

inline void vec3::operator/=(float t)
{
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
}

inline void vec3::make_unit_vector()
{
	float s = length();
	e[0] /= s;
	e[1] /= s;
	e[2] /= s;
}

inline std::istream& operator>>(std::istream& is, vec3& t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline vec3 operator+(const vec3& v1, const vec3& v2) 
{
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3& v1, const vec3& v2) 
{
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(const vec3& v1, float t)
{
	return vec3(v1.e[0] / t, v1.e[1] / t, v1.e[2] / t);
}

// dot product of v1 and v2
inline float dot(const vec3& v1, const vec3& v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

// compute the cross product: a vector orthogonal to both v1 and v2, whose magnitude
// is |v1||v2|sin(theta), where theta is the angle between v1 and v2
inline vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3(
        v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
        -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
        v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);	
}

// returns the normalized value of its argument
inline vec3 unit_vector(vec3 v) 
{
    return v / v.length();
}

// returns a random point in the unit sphere surrounding the origin
vec3 random_in_unit_sphere();

// returns a random point in the disk around the origin on the xy axis
vec3 random_in_unit_disk();

vec3 reflect(const vec3& v, const vec3& n);

// see glassner page 575, "Snell's law"
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted);