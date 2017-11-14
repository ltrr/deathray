#ifndef DEATHRAY_VECTOR_H_
#define DEATHRAY_VECTOR_H_

#include <iostream>
#include "util/math.h"


class Vec3
{
private:
    float e[3];

public:
    Vec3()
        : e {0.0, 0.0, 0.0} {}

    Vec3(float x, float y, float z)
        : e {x, y, z} {}

    inline float& x() { return e[0]; }
    inline float& y() { return e[1]; }
    inline float& z() { return e[2]; }

    inline const float& x() const { return e[0]; }
    inline const float& y() const { return e[1]; }
    inline const float& z() const { return e[2]; }

    inline float& operator[](int idx) { return e[idx]; }
    inline const float& operator[](int idx) const { return e[idx]; }

    inline Vec3 operator+() const;
    inline Vec3 operator-() const;

    inline void operator+=(const Vec3& v);
    inline void operator-=(const Vec3& v);
    inline void operator*=(float f);
    inline void operator*=(const Vec3& v);
    inline void operator/=(float f);
    inline void operator/=(const Vec3& v);

    inline bool operator==(const Vec3& v) const;
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
inline bool refract(const Vec3& v, const Vec3& n, float ni_nt, Vec3& refracted);
inline Vec3 min(const Vec3& v1, const Vec3& v2);
inline Vec3 max(const Vec3& v1, const Vec3& v2);

typedef Vec3 Point3;


#include "vector.inl"
#endif // DEATHRAY_VECTOR_H_
