#ifndef DEATHRAY_VECTOR_H_
#define DEATHRAY_VECTOR_H_

#include <cmath>
#include <limits>
#include <iostream>


const float PI = acos(-1);
const float EPS = std::numeric_limits<float>::epsilon();


class Vec3
{
public:
    float x, y, z;

    Vec3() : x(0.0), y(0.0), z(0.0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    inline Vec3 operator+() const;
    inline Vec3 operator-() const;

    inline void operator+=(const Vec3& v);
    inline void operator-=(const Vec3& v);
    inline void operator*=(float f);
    inline void operator*=(const Vec3& v);
    inline void operator/=(float f);
    inline void operator/=(const Vec3& v);
};


inline Vec3 operator+(const Vec3& v1, const Vec3& v2);
inline Vec3 operator-(const Vec3& v1, const Vec3& v2);
inline Vec3 operator*(float f, const Vec3& v);
inline Vec3 operator*(const Vec3& v, float f);
inline Vec3 operator*(const Vec3& v1, const Vec3& v2);
inline Vec3 operator/(const Vec3& v, float f);
inline Vec3 operator/(const Vec3& v1, const Vec3& v2);


inline std::istream& operator>>(std::istream& is, Vec3& v);
inline std::ostream& operator<<(std::ostream& os, const Vec3& v);


inline Vec3 unit(const Vec3& v);
inline float len2(const Vec3& v);
inline float len(const Vec3& v);
inline float dot(const Vec3& v1, const Vec3& v2);
inline Vec3 cross(const Vec3& v1, const Vec3& v2);
inline float angle(const Vec3& v1, const Vec3& v2);
inline Vec3 sqrt(const Vec3& v);
inline Vec3 reflect(const Vec3& v, const Vec3& n);

typedef Vec3 Point3;


#include "vector.inl"
#endif // DEATHRAY_VECTOR_H_
