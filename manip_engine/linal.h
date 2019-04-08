#pragma once
#include "const_header.h"
#include <iostream>
#include <algorithm>
class vector3
{
public:
	vector3(float v) : x(v), y(v), z(v) {};
	vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	inline vector3 screen_translation()
	{
		return vector3(SCREEN_WIDTH / 2 + x*SCREEN_WIDTH / 2, SCREEN_HEIGTH / 2 - y*SCREEN_HEIGTH / 2, z);
	}

	inline static vector3 unit_x() { return vector3(1, 0, 0); }
	inline static vector3 unit_y() { return vector3(0, 1, 0); }
	inline static vector3 unit_z() { return vector3(0, 0, 1); }

	//Vector algebra
	inline float Dot(const vector3& b) const {
		return x*b.x + y*b.y + z*b.z;
	}
	inline vector3 Cross(const vector3& b) const {
		return vector3(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	}
	inline float MagSq() const {
		return x*x + y*y + z*z;
	}
	inline float Mag() const {
		return std::sqrt(MagSq());
	}
	//Normalization
	inline void normalize() {
		(*this) /= Mag();
	}
	inline void normalize_safe() {
		(*this) /= (Mag() + FLT_EPSILON);
	}
	inline vector3 normalized() const {
		return (*this) / Mag();
	}
	inline vector3 normalized_safe() const {
		return (*this) / (Mag() + FLT_EPSILON);
	}
	inline float angle(const vector3& b) const {
		return acos(normalized().Dot(b.normalized()));
	}
	inline float angle_safe(const vector3& b) const {
		return acos(normalized_safe().Dot(b.normalized_safe()));
	}
	
	// operatios
	inline vector3 operator+(float b) const {
		return vector3(x + b, y + b, z + b);
	}
	inline vector3 operator-(float b) const {
		return vector3(x - b, y - b, z - b);
	}
	inline vector3 operator*(float b) const {
		return vector3(x * b, y * b, z * b);
	}
	inline vector3 operator/(float b) const {
		return vector3(x / b, y / b, z / b);
	}
	inline vector3 operator+(const vector3& b) const {
		return vector3(x + b.x, y + b.y, z + b.z);
	}
	inline vector3 operator-(const vector3& b) const {
		return vector3(x - b.x, y - b.y, z - b.z);
	}
	inline vector3 operator*(const vector3& b) const {
		return vector3(x * b.x, y * b.y, z * b.z);
	}
	inline vector3 operator/(const vector3& b) const {
		return vector3(x / b.x, y / b.y, z / b.z);
	}
	inline void operator+=(float b) {
		x += b; y += b; z += b;
	}
	inline void operator-=(float b) {
		x -= b; y -= b; z -= b;
	}
	inline void operator*=(float b) {
		x *= b; y *= b; z *= b;
	}
	inline void operator/=(float b) {
		x /= b; y /= b; z /= b;
	}
	inline void operator+=(const vector3& b) {
		x += b.x; y += b.y; z += b.z;
	}
	inline void operator-=(const vector3& b) {
		x -= b.x; y -= b.y; z -= b.z;
	}
	inline void operator*=(const vector3& b) {
		x *= b.x; y *= b.y; z *= b.z;
	}
	inline void operator/=(const vector3& b) {
		x /= b.x; y /= b.y; z /= b.z;
	}
	inline vector3 operator-() const {
		return vector3(-x, -y, -z);
	}

	//vector
	float x, y, z;
};
class vector4
{
public:
	vector4() {}
	vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
	vector4(float x, float y, float z) : x(x), y(y), z(z), w(1) {}
	vector4(vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
	~vector4() {}
	inline vector3 homogenized()  { return vector3(x / w, y / w, z / w); }
	float x, y, z, w;
};

class matrix4x4
{
public:
	matrix4x4(){}
	matrix4x4(float b) { std::fill(m, m + 16, b); }
	~matrix4x4() {}

	inline void fill_zeros() {
		std::fill(m, m + 16, 0.0f);
	}

	inline void load_identity()
	{
		m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
		m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = 0.0f;
		m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
	}
	inline void make_rot_x(float a)
	{
		m[0] = 1.0f; m[1] = 0.0f;        m[2] = 0.0f;         m[3] = 0.0f;
		m[4] = 0.0f; m[5] = std::cos(a); m[6] = -std::sin(a); m[7] = 0.0f;
		m[8] = 0.0f; m[9] = std::sin(a); m[10] = std::cos(a);  m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f;        m[14] = 0.0f;         m[15] = 1.0f;
	}
	inline void make_rot_y(float a)
	{
		m[0] = std::cos(a);  m[1] = 0.0f; m[2] = std::sin(a); m[3] = 0.0f;
		m[4] = 0.0f;         m[5] = 1.0f; m[6] = 0.0f;        m[7] = 0.0f;
		m[8] = -std::sin(a); m[9] = 0.0f; m[10] = std::cos(a); m[11] = 0.0f;
		m[12] = 0.0f;         m[13] = 0.0f; m[14] = 0.0f;        m[15] = 1.0f;
	}
	inline void make_rot_z(float a)
	{
		m[0] = std::cos(a); m[1] = -std::sin(a); m[2] = 0.0f; m[3] = 0.0f;
		m[4] = std::sin(a); m[5] = std::cos(a);  m[6] = 0.0f; m[7] = 0.0f;
		m[8] = 0.0f;        m[9] = 0.0f;         m[10] = 1.0f; m[11] = 0.0f;
		m[12] = 0.0f;        m[13] = 0.0f;         m[14] = 0.0f; m[15] = 1.0f;
	}
	inline void make_translate(const vector3& t)
	{
		m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = t.x;
		m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = t.y;
		m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = t.z;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
	}
	inline void make_scale(const vector3& s)
	{
		m[0] = s.x;  m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
		m[4] = 0.0f; m[5] = s.y;  m[6] = 0.0f; m[7] = 0.0f;
		m[8] = 0.0f; m[9] = 0.0f; m[10] = s.z;  m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
	}

	inline static matrix4x4 zero() { matrix4x4 m; m.fill_zeros(); return m; }
	inline static matrix4x4 identity() { matrix4x4 m; m.load_identity(); return m; }
	inline static matrix4x4 rot_x(float a) { matrix4x4 m; m.make_rot_x(a); return m; }
	inline static matrix4x4 rot_y(float a) { matrix4x4 m; m.make_rot_y(a); return m; }
	inline static matrix4x4 rot_z(float a) { matrix4x4 m; m.make_rot_z(a); return m; }
	inline static matrix4x4 trans(const vector3& t) { matrix4x4 m; m.make_translate(t); return m; }
	inline static matrix4x4 scale(float s) { matrix4x4 m; m.make_scale(vector3(s)); return m; }
	inline static matrix4x4 scale(const vector3& s) { matrix4x4 m; m.make_scale(s); return m; }
	inline matrix4x4 Transposed() const {
		matrix4x4 out;
		out.m[0] = m[0]; out.m[1] = m[4]; out.m[2] = m[8];  out.m[3] = m[12];
		out.m[4] = m[1]; out.m[5] = m[5]; out.m[6] = m[9];  out.m[7] = m[13];
		out.m[8] = m[2]; out.m[9] = m[6]; out.m[10] = m[10]; out.m[11] = m[14];
		out.m[12] = m[3]; out.m[13] = m[7]; out.m[14] = m[11]; out.m[15] = m[15];
		return out;
	}
	//setters

	inline void SetXAxis(const vector3& t) {
		m[0] = t.x;
		m[4] = t.y;
		m[8] = t.z;
	}
	inline void SetYAxis(const vector3& t) {
		m[1] = t.x;
		m[5] = t.y;
		m[9] = t.z;
	}
	inline void SetZAxis(const vector3& t) {
		m[2] = t.x;
		m[6] = t.y;
		m[10] = t.z;
	}
	
	//operators
	matrix4x4 operator*(const matrix4x4& b) const {
		matrix4x4 out;
		out.m[0] = b.m[0] * m[0] + b.m[4] * m[1] + b.m[8] * m[2] + b.m[12] * m[3];
		out.m[1] = b.m[1] * m[0] + b.m[5] * m[1] + b.m[9] * m[2] + b.m[13] * m[3];
		out.m[2] = b.m[2] * m[0] + b.m[6] * m[1] + b.m[10] * m[2] + b.m[14] * m[3];
		out.m[3] = b.m[3] * m[0] + b.m[7] * m[1] + b.m[11] * m[2] + b.m[15] * m[3];

		out.m[4] = b.m[0] * m[4] + b.m[4] * m[5] + b.m[8] * m[6] + b.m[12] * m[7];
		out.m[5] = b.m[1] * m[4] + b.m[5] * m[5] + b.m[9] * m[6] + b.m[13] * m[7];
		out.m[6] = b.m[2] * m[4] + b.m[6] * m[5] + b.m[10] * m[6] + b.m[14] * m[7];
		out.m[7] = b.m[3] * m[4] + b.m[7] * m[5] + b.m[11] * m[6] + b.m[15] * m[7];

		out.m[8] = b.m[0] * m[8] + b.m[4] * m[9] + b.m[8] * m[10] + b.m[12] * m[11];
		out.m[9] = b.m[1] * m[8] + b.m[5] * m[9] + b.m[9] * m[10] + b.m[13] * m[11];
		out.m[10] = b.m[2] * m[8] + b.m[6] * m[9] + b.m[10] * m[10] + b.m[14] * m[11];
		out.m[11] = b.m[3] * m[8] + b.m[7] * m[9] + b.m[11] * m[10] + b.m[15] * m[11];

		out.m[12] = b.m[0] * m[12] + b.m[4] * m[13] + b.m[8] * m[14] + b.m[12] * m[15];
		out.m[13] = b.m[1] * m[12] + b.m[5] * m[13] + b.m[9] * m[14] + b.m[13] * m[15];
		out.m[14] = b.m[2] * m[12] + b.m[6] * m[13] + b.m[10] * m[14] + b.m[14] * m[15];
		out.m[15] = b.m[3] * m[12] + b.m[7] * m[13] + b.m[11] * m[14] + b.m[15] * m[15];
		return out;
	}
	vector4 operator*(const vector4& b) const {
		return vector4(
			m[0] * b.x + m[1] * b.y + m[2] * b.z + m[3] * b.w,
			m[4] * b.x + m[5] * b.y + m[6] * b.z + m[7] * b.w,
			m[8] * b.x + m[9] * b.y + m[10] * b.z + m[11] * b.w,
			m[12] * b.x + m[13] * b.y + m[14] * b.z + m[15] * b.w
		);
	}
	inline void operator*=(float b) {
		for (int i = 0; i < 16; ++i) { m[i] *= b; }
	}
	inline void operator/=(float b) {
		operator*=(1.0f / b);
	}
	//matrix inverse
	matrix4x4 inverse() const {
		matrix4x4 inv;

		inv.m[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv.m[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv.m[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv.m[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv.m[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv.m[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv.m[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv.m[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv.m[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv.m[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv.m[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv.m[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv.m[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv.m[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv.m[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv.m[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		const float det = m[0] * inv.m[0] + m[1] * inv.m[4] + m[2] * inv.m[8] + m[3] * inv.m[12];
		inv /= det;
		return inv;
	}
	
	//matrix
	float m[16];
};

//Debug 
inline std::ostream& operator<<(std::ostream& out, const vector3& v) {
	out << v.x << ", " << v.y << ", " << v.z;
	return out;
}
inline std::ostream& operator<<(std::ostream& out, const vector4& v) {
	out << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
	return out;
}
inline std::ostream& operator<<(std::ostream& out, const matrix4x4& m) {
	out << m.m[0] << ", " << m.m[1] << ", " << m.m[2] << ", " << m.m[3] << "\n";
	out << m.m[4] << ", " << m.m[5] << ", " << m.m[6] << ", " << m.m[7] << "\n";
	out << m.m[8] << ", " << m.m[9] << ", " << m.m[10] << ", " << m.m[11] << "\n";
	out << m.m[12] << ", " << m.m[13] << ", " << m.m[14] << ", " << m.m[15] << "\n";
	return out;
}


