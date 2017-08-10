#include <cmath>
#include <iostream>

inline Vec3 Vec3::operator+() const {
    return (*this);
}

inline Vec3 Vec3::operator-() const {
    return Vec3(-this->x, -this->y, -this->z);
}

inline void Vec3::operator+=(const Vec3& v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}

inline void Vec3::operator-=(const Vec3& v) {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
}

inline void Vec3::operator*=(float f) {
    this->x *= f;
    this->y *= f;
    this->z *= f;
}

inline void Vec3::operator*=(const Vec3& v) {
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
}

inline void Vec3::operator/=(float f) {
    this->x /= f;
    this->y /= f;
    this->z /= f;
}

inline void Vec3::operator/=(const Vec3& v) {
    this->x /= v.x;
    this->y /= v.y;
    this->z /= v.z;
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vec3 operator*(float f, const Vec3& v) {
    return Vec3(f * v.x, f * v.y, f * v.z);
}

inline Vec3 operator*(const Vec3& v, float f) {
    return Vec3(v.x * f, v.y * f, v.z * f);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vec3 operator/(const Vec3& v, float f) {
    return Vec3(v.x / f, v.y / f, v.z / f);
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline std::istream& operator>>(std::istream& is, Vec3& v) {
    return (is >> v.x >> v.y >> v.z);
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    return (os << v.x << ' ' << v.y << ' ' << v.z);
}

inline Vec3 unit(const Vec3& v) {
    return v / len(v);
}

inline float len2(const Vec3& v) {
    return v.x*v.x + v.y*v.y + v.z*v.z;
}

inline float len(const Vec3& v) {
    return sqrt(len2(v));
}

inline float dot(const Vec3& v1, const Vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

inline float angle(const Vec3& v1, const Vec3& v2) {
    return acos(dot(v1, v2)/(len(v1) * len(v2)));
}
