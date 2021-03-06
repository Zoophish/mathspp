/*----	By Sam Warren 2019	----
Use SSE instructions for faster vec3<float> operators:
*/
#define LAMBDA_VEC3_USE_SSE

#pragma once
#include <math.h>
#include <type_traits>
#ifdef LAMBDA_VEC3_USE_SSE
#include <nmmintrin.h>
#endif

template <
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
class vec3 {
public:
	T x, y, z;

	vec3(const T _x = 0, const T _y = 0, const T _z = 0) {
		x = _x;
		y = _y;
		z = _z;
	}

	vec3(const T *_xyz) {
		memcpy(this, _xyz, 3 * sizeof(T));
	}

	inline vec3<T> operator+(const vec3<T> &_rhs) const { return vec3<T>(x + _rhs.x, y + _rhs.y, z + _rhs.z); }
	inline vec3<T> operator-(const vec3<T> &_rhs) const { return vec3<T>(x - _rhs.x, y - _rhs.y, z - _rhs.z); }
	inline vec3<T> operator*(const vec3<T> &_rhs) const { return vec3<T>(x * _rhs.x, y * _rhs.y, z * _rhs.z); }
	inline vec3<T> operator*(const T _rhs) const { return vec3<T>(x * _rhs, y * _rhs, z * _rhs); }
	inline vec3<T> operator/(const vec3<T> &_rhs) const { return vec3<T>(x / _rhs.x, y / _rhs.y, z / _rhs.z); }
	inline vec3<T> operator/(const T _rhs) const { const T inv = (T)1 / _rhs; return vec3<T>(x * inv, y * inv, z * inv); }
	inline vec3<T> operator-() const { return *this * -1; }

	inline vec3<T> &operator+=(const vec3<T> &_rhs) {
		x += _rhs.x;
		y += _rhs.y;
		z += _rhs.z;
		return *this;
	}
	inline vec3<T> &operator-=(const vec3<T> &_rhs) {
		x -= _rhs.x;
		y -= _rhs.y;
		z -= _rhs.z;
		return *this;
	}
	inline vec3<T> &operator*=(const vec3<T> &_rhs) {
		x *= _rhs.x;
		y *= _rhs.y;
		z *= _rhs.z;
		return *this;
	}
	inline vec3<T> &operator*=(const T _rhs) {
		x *= _rhs;
		y *= _rhs;
		z *= _rhs;
		return *this;
	}
	inline vec3<T> &operator/=(const vec3<T> &_rhs) {
		x /= _rhs.x;
		y /= _rhs.y;
		z /= _rhs.z;
		return *this;
	}
	inline vec3<T> &operator/=(const T _rhs) {
		const T inv = (T)1 / _rhs;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}
	
	inline bool operator==(const vec3<T> &_rhs) const { return x == _rhs.x && y == _rhs.y && z == _rhs.z; }
	inline bool operator!=(const vec3<T> &_rhs) const { return x != _rhs.x || y != _rhs.y || z != _rhs.z; }

	inline T operator[](const unsigned _dim) const { return reinterpret_cast<T *>(const_cast<vec3<T> *>(this))[_dim]; }

	inline T &operator[](const unsigned _dim) { return reinterpret_cast<T *>(this)[_dim]; }

	inline T Magnitude() const { return std::sqrt(x * x + y * y + z * z); }

	inline vec3<T> Normalised() const {
		return *this / Magnitude();
	}
};

/*
----	SSE Implementation	----
Since SSE uses 128-bit registers, there is a redundant fourth float 'a' for padding.
*/
#ifdef LAMBDA_VEC3_USE_SSE
template<>
class alignas(16) vec3<float> {
public:
	float x, y, z, a;

	vec3(const float _x = 0, const float _y = 0, const float _z = 0) {
		x = _x;
		y = _y;
		z = _z;
		a = 0;
	}

	vec3(const float *_xyz) {
		memcpy(this, _xyz, 3 * sizeof(float));
	}

	inline vec3<float> operator+(const vec3<float> &_rhs) const {
		return vec3<float>(_mm_add_ps(_mm_load_ps(reinterpret_cast<const float*>(this)), _mm_load_ps(reinterpret_cast<const float*>(&_rhs))));
	}
	inline vec3<float> operator-(const vec3<float> &_rhs) const {
		return vec3<float>(_mm_sub_ps(_mm_load_ps(reinterpret_cast<const float*>(this)), _mm_load_ps(reinterpret_cast<const float*>(&_rhs))));
	}
	inline vec3<float> operator*(const vec3<float> &_rhs) const {
		return vec3<float>(_mm_mul_ps(_mm_load_ps(reinterpret_cast<const float*>(this)), _mm_load_ps(reinterpret_cast<const float*>(&_rhs))));
	}
	inline vec3<float> operator/(const vec3<float> &_rhs) const {
		return vec3<float>(_mm_div_ps(_mm_load_ps(reinterpret_cast<const float*>(this)), _mm_load_ps(reinterpret_cast<const float*>(&_rhs))));
	}
	inline vec3<float> operator*(const float _rhs) const {
		return vec3<float>(_mm_mul_ps(_mm_load_ps(reinterpret_cast<const float*>(this)), _mm_set_ps1(_rhs)));
	}
	inline vec3<float> operator/(const float _rhs) const {
		return vec3<float>(_mm_mul_ps(_mm_load_ps(reinterpret_cast<const float*>(this)), _mm_set_ps1(1.f / _rhs)));
	}
	inline vec3<float> operator-() const { return *this * -1; }

	inline vec3<float> &operator+=(const vec3<float> &_rhs) {
		_mm_store_ps(reinterpret_cast<float*>(this), _mm_add_ps(_mm_load_ps(reinterpret_cast<float*>(this)), _mm_load_ps(reinterpret_cast<const float*>(&_rhs))));
		return *this;
	}
	inline vec3<float> &operator-=(const vec3<float> &_rhs) {
		_mm_store_ps(reinterpret_cast<float*>(this), _mm_sub_ps(_mm_load_ps(reinterpret_cast<float*>(this)), _mm_load_ps(reinterpret_cast<const float*>(&_rhs))));
		return *this;
	}
	inline vec3<float> &operator*=(const vec3<float> &_rhs) {
		_mm_store_ps(reinterpret_cast<float*>(this), _mm_mul_ps(_mm_load_ps(reinterpret_cast<float*>(this)), _mm_load_ps(reinterpret_cast<const float*>(&_rhs))));
		return *this;
	}
	inline vec3<float> &operator/=(const vec3<float> &_rhs) {
		_mm_store_ps(reinterpret_cast<float*>(this), _mm_div_ps(_mm_load_ps(reinterpret_cast<float*>(this)), _mm_load_ps(reinterpret_cast<const float*>(&_rhs))));
		return *this;
	}
	inline vec3<float> &operator*=(const float _rhs) {
		_mm_store_ps(reinterpret_cast<float*>(this), _mm_mul_ps(_mm_load_ps(reinterpret_cast<float*>(this)), _mm_set_ps1(_rhs)));
		return *this;
	}
	inline vec3<float> &operator/=(const float _rhs) {
		_mm_store_ps(reinterpret_cast<float*>(this), _mm_mul_ps(_mm_load_ps(reinterpret_cast<float*>(this)), _mm_set_ps1(1.f / _rhs)));
		return *this;
	}

	inline bool operator==(const vec3<float> &_rhs) const { return x == _rhs.x && y == _rhs.y && z == _rhs.z; }
	inline bool operator!=(const vec3<float> &_rhs) const { return x != _rhs.x || y != _rhs.y || z != _rhs.z; }

	inline float operator[](const unsigned _dim) const { return reinterpret_cast<float *>(const_cast<vec3<float> *>(this))[_dim]; }

	inline float &operator[](const unsigned _dim) { return reinterpret_cast<float *>(this)[_dim]; }

	inline float Magnitude() const {
		const vec3<float> sq = *this * *this;
		return std::sqrt(sq.x + sq.y + sq.z);
	}

	inline vec3<float> Normalised() const {
		return *this / Magnitude();
	}

private:
		vec3(const __m128 &_xyza) {
			_mm_store_ps(reinterpret_cast<float*>(this), _xyza);
		}
};
#endif

namespace maths {

	template<class T>
	inline T Dot(const vec3<T> &_a, const vec3<T> &_b) {
		return _a.x*_b.x + _a.y*_b.y + _a.z*_b.z;
	}

	template<class T>
	inline vec3<T> Cross(const vec3<T> &_a, const vec3<T> &_b) {
		return vec3<T>(_a.y*_b.z - _a.z*_b.y, _a.z*_b.x - _a.x*_b.z, _a.x*_b.y - _a.y*_b.x);
	}

	template<class T>
	inline T DistSq(const vec3<T> &_a, const vec3<T> &_b) {
		const vec3<T> diff = _b - _a;
		return diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
	}

	//Y is up (Normal)
	template<class T>
	inline vec3<T> WorldToLocal(const vec3<T> &_v, const vec3<T> &_t, const vec3<T> &_n, const vec3<T> &_bt) {
		return vec3<T>(maths::Dot(_t, _v), maths::Dot(_n, _v), maths::Dot(_bt, _v));
	}
	template<class T>
	inline vec3<T> LocalToWorld(const vec3<T> &_v, const vec3<T> &_t, const vec3<T> &_n, const vec3<T> &_bt) {
		return vec3<T>(
			_t.x * _v.x + _n.x * _v.y + _bt.x * _v.z,
			_t.y * _v.x + _n.y * _v.y + _bt.y * _v.z,
			_t.z * _v.x + _n.z * _v.y + _bt.z * _v.z
		);
	}
	#ifdef LAMBDA_VEC3_USE_SSE
	template<>
	inline vec3<float> LocalToWorld(const vec3<float> &_v, const vec3<float> &_t, const vec3<float> &_n, const vec3<float> &_bt) {
		return _t * _v.x + _n * _v.y + _bt * _v.z;
	}
	#endif

	template<class T>
	inline vec3<T> SphericalDirection(const T _sinTheta, const T _cosTheta, const T _phi) {
		return vec3<T>(_sinTheta * std::cos(_phi), _cosTheta, _sinTheta * std::sin(_phi));
	}

	template<class T>
	inline T SphericalTheta(const vec3<T> &_v) {
		return std::acos(std::max(std::min(_v.y, (T)1), (T)-1));
	}

	template<class T>
	inline T SphericalPhi(const vec3<T> &_v) {
		const T p = std::atan2(_v.z, _v.x);
		return (p < 0) ? (p + 3.14159265359 * 2.) : p;
	}

	template<class T>
	inline vec3<T> Rotate(const vec3<T> &_v, const vec3<T> &_axis, const T _theta) {
		const T cosTheta = std::cos(_theta);
		const T sinTheta = std::sqrt((T)1 - cosTheta * cosTheta);
		return _v * cosTheta + maths::Cross(_axis, _v) * sinTheta + _axis * maths::Dot(_axis, _v) * ((T)1 - cosTheta);
	}

	#ifdef LAMBDA_VEC3_USE_SSE
	template<>
	inline float Dot(const vec3<float> &_a, const vec3<float> &_b) {
		const vec3<float> sq = _a * _b;
		return sq.x + sq.y + sq.z;
	}
	#endif
}