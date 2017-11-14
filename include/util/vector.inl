#include <cmath>
#include <iostream>


//// class Vec3 ////
inline Vec3 Vec3::operator+() const
{
    return (*this);
}

inline Vec3 Vec3::operator-() const
{
    return Vec3(-this->x(), -this->y(), -this->z());
}

inline void Vec3::operator+=(const Vec3& v)
{
    this->x() += v.x();
    this->y() += v.y();
    this->z() += v.z();
}

inline void Vec3::operator-=(const Vec3& v)
{
    this->x() -= v.x();
    this->y() -= v.y();
    this->z() -= v.z();
}

inline void Vec3::operator*=(float f)
{
    this->x() *= f;
    this->y() *= f;
    this->z() *= f;
}

inline void Vec3::operator*=(const Vec3& v)
{
    this->x() *= v.x();
    this->y() *= v.y();
    this->z() *= v.z();
}

inline void Vec3::operator/=(float f)
{
    this->x() /= f;
    this->y() /= f;
    this->z() /= f;
}

inline void Vec3::operator/=(const Vec3& v)
{
    this->x() /= v.x();
    this->y() /= v.y();
    this->z() /= v.z();
}


inline bool Vec3::operator==(const Vec3& v) const
{
    return (this->x() == v.x()
         && this->y() == v.y()
         && this->z() == v.z());
}


//// vector operations ////
inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}


inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}


inline Vec3 operator*(float f, const Vec3& v)
{
    return Vec3(f * v.x(), f * v.y(), f * v.z());
}


inline Vec3 operator*(const Vec3& v, float f)
{
    return Vec3(v.x() * f, v.y() * f, v.z() * f);
}


inline Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}


inline Vec3 operator/(const Vec3& v, float f)
{
    return Vec3(v.x() / f, v.y() / f, v.z() / f);
}


inline Vec3 operator/(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}


inline std::istream& operator>>(std::istream& is, Vec3& v)
{
    return (is >> v.x() >> v.y() >> v.z());
}


inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    return (os << v.x() << ' ' << v.y() << ' ' << v.z());
}


inline Vec3 unit(const Vec3& v)
{
    return v / len(v);
}


inline float len2(const Vec3& v)
{
    return v.x()*v.x() + v.y()*v.y() + v.z()*v.z();
}


inline float len(const Vec3& v)
{
    return sqrt(len2(v));
}


inline float dot(const Vec3& v1, const Vec3& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}


inline Vec3 cross(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.y() * v2.z() - v1.z() * v2.y(),
                v1.z() * v2.x() - v1.x() * v2.z(),
                v1.x() * v2.y() - v1.y() * v2.x());
}


inline float angle(const Vec3& v1, const Vec3& v2)
{
    return acos(dot(v1, v2)/(len(v1) * len(v2)));
}


inline Vec3 sqrt(const Vec3& v)
{
    return Vec3(sqrt(v.x()), sqrt(v.y()), sqrt(v.z()));
}


inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v - 2 * dot(v, n) * n;
}


inline bool refract(const Vec3& v, const Vec3& n, float ni_nt,
    Vec3& refracted)
{
    float dt = dot(v, n);
    float disc = 1.0f - ni_nt*ni_nt*(1-dt*dt);
    if (disc > 0) {
        refracted = ni_nt*(v - n*dt) - n*sqrt(disc);
        return true;
    }
    return false;
}


inline Vec3 min(const Vec3& v1, const Vec3& v2)
{
    Vec3 ans;
    ans.x() = std::min(v1.x(), v2.x());
    ans.y() = std::min(v1.y(), v2.y());
    ans.z() = std::min(v1.z(), v2.z());
    return ans;
}


inline Vec3 max(const Vec3& v1, const Vec3& v2)
{
    Vec3 ans;
    ans.x() = std::max(v1.x(), v2.x());
    ans.y() = std::max(v1.y(), v2.y());
    ans.z() = std::max(v1.z(), v2.z());
    return ans;
}
