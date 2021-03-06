#pragma once
#include "vec3.h"

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
class bounds {
public:
	vec3<T> min, max;

	bounds() {
		min = { 0,0,0 };
		max = { 0,0,0 };
	}

	bounds(const vec3<T> &_min, const vec3<T> &_max) {
		min = _min;
		max = _max;
	}

	bounds(const vec3<T> &_p) {
		min = _p;
		max = _p;
	}

	inline T SurfaceArea() const {
		const vec3<T> s = max - min;
		return (s.x * s.y + s.y * s.z + s.x * s.z) * (T)2;
	}

	inline T MaxLength() const {
		const vec3<T> box = max - min;
		return std::max(std::max(box.x, box.y), box.z);
	}

	inline vec3<T> Center() const {
		return min + (max - min) * (T).5;
	}

	inline T DiagonalLength() const {
		return (max - min).Magnitude();
	}

	inline vec3<T> Offset(const vec3<T> &_p) const {
		const vec3<T> o = _p - min;
		const vec3<T> d = max - min;
		return o / d;
	}

	inline bool Contains(const vec3<T> &_p) const {
		return _p.x > min.x && _p.x < max.x &&_p.y > min.y && _p.y < max.y &&_p.z > min.z && _p.z < max.z;
	}
};

template<>
class alignas(16) bounds<float> {
public:
	vec3<float> min, max;

	bounds() {
		min = { 0,0,0 };
		max = { 0,0,0 };
	}

	bounds(const vec3<float> &_min, const vec3<float> &_max) {
		min = _min;
		max = _max;
	}

	bounds(const vec3<float> &_p) {
		min = _p;
		max = _p;
	}

	inline float SurfaceArea() const {
		const vec3<float> s = max - min;
		return (s.x * s.y + s.y * s.z + s.x * s.z) * 2.f;
	}

	inline float MaxLength() const {
		const vec3<float> box = max - min;
		return std::max(std::max(box.x, box.y), box.z);
	}

	inline vec3<float> Center() const {
		return min + (max - min) * .5f;
	}

	inline float DiagonalLength() const {
		return (max - min).Magnitude();
	}

	inline vec3<float> Offset(const vec3<float> &_p) const {
		const vec3<float> o = _p - min;
		const vec3<float> d = max - min;
		return o / d;
	}

	inline bool Contains(const vec3<float> &_p) const {
		return _p.x > min.x && _p.x < max.x &&_p.y > min.y && _p.y < max.y &&_p.z > min.z && _p.z < max.z;
	}
};

namespace maths {

	template<class T>
	inline bounds<T> Union(const bounds<T> &_a, const bounds<T> &_b) {
		return bounds<T>(
			{ std::min(_a.min.x, _b.min.x), std::min(_a.min.y, _b.min.y), std::min(_a.min.z, _b.min.z) },
			{ std::max(_a.max.x, _b.max.x), std::max(_a.max.y, _b.max.y), std::max(_a.max.z, _b.max.z) }
		);
	}

	template<class T>
	inline bounds<T> Union(const bounds<T> &_b, const vec3<T> &_p) {
		return bounds<T>(
			{ std::min(_p.x, _b.min.x), std::min(_p.y, _b.min.y), std::min(_p.z, _b.min.z) },
			{ std::max(_p.x, _b.max.x), std::max(_p.y, _b.max.y), std::max(_p.z, _b.max.z) }
		);
	}

}