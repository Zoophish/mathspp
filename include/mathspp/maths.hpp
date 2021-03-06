/*
----	By Sam Warren	----
	Single include header for some foundational mathematical types, mainly for personal use.

	Types:
		- vec3: 3D vector
		- vec2: 2D vector
		- bounds: 3D axis-aligned bounding box
		- affine3: 3x3 affine transformation matrix & translation
*/

/* ---- General numerical type definition: ---- */
typedef float Real;

/* ---- Enable standard typdefs for mathematical types ---- */
//#define LAMBDA_MATHS_COMMON_TYPES



//----	Don't make changes below here.	----
#pragma once
#include <cmath>
#include <algorithm>
#include "vec3.h"
#include "vec2.h"
#include "bounds.h"
#include "affine3.h"

typedef vec3<Real> Vec3;
typedef vec2<Real> Vec2;
typedef bounds<Real> Bounds;
typedef affine3<Real> Affine3;

template<class T>
constexpr T PI = 3.14159265358979323846264338;

template<class T>
constexpr T PI2 = (T)2 * PI<T>;

template<class T>
constexpr T INV_PI = (T)1 / PI<T>;

template<class T>
constexpr T INV_PI2 = (T)1 / ((T)2 * PI<T>);

template<class T>
constexpr T INV_PI4 = (T)1 / ((T)4 * PI<T>);

template<class T>
constexpr T E_NUM = 2.718281828459045;

template<class T>
constexpr T MAX_REAL = std::numeric_limits<T>::max();

template<class T>
constexpr T MIN_REAL = std::numeric_limits<T>::min();

template<class T>
constexpr T BITFLAG(const T _i) {
	return (T)1 << _i;
}

namespace maths {

	template<class T>
	inline T Lerp(const T &_a, const T &_b, const Real _r) {
		return _a + (_b - _a) * _r;
	}

	template<class T>
	inline T Clamp(const T _value, const T _min, const T _max) {
		return std::max(std::min(_value, _max), _min);
	}

	template<class T>
	inline T BarycentricInterpolation(const T &_t0, const T &_t1, const T &_t2, const Real _u, const Real _v) {
		return _t0 + (_t1 - _t0) * _u + (_t2 - _t0) * _v;
	}

	template<class T>
	inline T Fract(const T _r) {
		return _r - std::floor(_r);
	}

	template<class T>
	inline vec2<T> Fract(const vec2<T> &_v) {
		return vec2<T>(_v.x - std::floor(_v.x), _v.y - std::floor(_v.y));
	}

	template<class T>
	inline vec3<T> Fract(const vec3<T> &_v) {
		return vec3<T>(_v.x - std::floor(_v.x), _v.y - std::floor(_v.y), _v.z - std::floor(_v.z));
	}

	template<class T>
	inline unsigned FindInterval(const int _size, const T &_predicate) {
		int first = 0, len = _size;
		while (len > 0) {
			int half = len >> 1, middle = first + half;
			if (_predicate(middle)) {
				first = middle + 1;
				len -= half + 1;
			}
			else
				len = half;
		}
		return maths::Clamp(first - 1, 0, _size - 2);
	}
}

#ifdef LAMBDA_MATHS_COMMON_TYPES
typedef complex_t<float> complexf;
typedef complex_t<double> complexd;
typedef complex_t<int> complexi;
typedef complex_t<unsigned> complexu;

typedef vec3<float> vec3f;
typedef vec3<double> vec3d;
typedef vec3<int> vec3i;
typedef vec3<unsigned> vec3u;

typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<int> vec2i;
typedef vec2<unsigned> vec2u;

typedef bounds<float> boundsf;
typedef bounds<double> boundsd;
typedef bounds<int> boundsi;
typedef bounds<unsigned> boundsu;

typedef affine3<float> affine3f;
typedef affine3<double> affine3d;
typedef affine3<int> affine3i;
typedef affine3<unsigned> affine3u;
#endif