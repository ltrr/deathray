#ifndef DEATHRAY_UTIL_TRANSFORM_H_
#define DEATHRAY_UTIL_TRANSFORM_H_

#include "util/vector.h"

struct Mat44
{
    float values[4][4];

    Mat44()
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                values[i][j] = 0;
            }
        }
    }

    Mat44(float m00, float m01, float m02, float m03,
          float m10, float m11, float m12, float m13,
          float m20, float m21, float m22, float m23,
          float m30, float m31, float m32, float m33)
    {
        values[0][0] = m00;
        values[0][1] = m01;
        values[0][2] = m02;
        values[0][3] = m03;
        values[1][0] = m10;
        values[1][1] = m11;
        values[1][2] = m12;
        values[1][3] = m13;
        values[2][0] = m20;
        values[2][1] = m21;
        values[2][2] = m22;
        values[2][3] = m23;
        values[3][0] = m30;
        values[3][1] = m31;
        values[3][2] = m32;
        values[3][3] = m33;
    }

    inline float operator()(size_t i, size_t j) const
    {
        return values[i][j];
    }

    inline float& operator()(size_t i, size_t j)
    {
        return values[i][j];
    }

    Mat44 operator*(const Mat44& m) const
    {
        Mat44 ans;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ans.values[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    ans.values[i][j] += values[i][k] * m.values[k][j];
                }
            }
        }
        return ans;
    }
};


class Transform
{
private:
    Mat44 A, A_inv;

public:
    Transform(const Mat44& A, const Mat44& A_inv)
        : A(A), A_inv(A_inv) { }

    Vec3 applyV(const Vec3& v) const
    {
        float x = v.x(), y = v.y(), z = v.z();
        return Vec3(
            A(0,0)*x + A(0,1)*y + A(0,2)*z,
            A(1,0)*x + A(1,1)*y + A(1,2)*z,
            A(2,0)*x + A(2,1)*y + A(2,2)*z
        );
    }

    Point3 applyP(const Point3& p) const
    {
        float x = p.x(), y = p.y(), z = p.z();
        return Point3(
            A(0,0)*x + A(0,1)*y + A(0,2)*z + A(0,3),
            A(1,0)*x + A(1,1)*y + A(1,2)*z + A(1,3),
            A(2,0)*x + A(2,1)*y + A(2,2)*z + A(2,3)
        );
    }

    Vec3 applyInvV(const Vec3& v) const
    {
        float x = v.x(), y = v.y(), z = v.z();
        return Vec3(
            A_inv(0,0)*x + A_inv(0,1)*y + A_inv(0,2)*z,
            A_inv(1,0)*x + A_inv(1,1)*y + A_inv(1,2)*z,
            A_inv(2,0)*x + A_inv(2,1)*y + A_inv(2,2)*z
        );
    }

    Point3 applyInvP(const Point3& p) const
    {
        float x = p.x(), y = p.y(), z = p.z();
        return Point3(
            A_inv(0,0)*x + A_inv(0,1)*y + A_inv(0,2)*z + A_inv(0,3),
            A_inv(1,0)*x + A_inv(1,1)*y + A_inv(1,2)*z + A_inv(1,3),
            A_inv(2,0)*x + A_inv(2,1)*y + A_inv(2,2)*z + A_inv(2,3)
        );
    }

    Transform operator*(const Transform& tr) const
    {
        return Transform(A * tr.A, tr.A_inv * A_inv);
    }

    static Transform eye()
    {
        return Transform(
            Mat44(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1),
            Mat44(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1)
        );
    }

    static Transform translate(const Vec3& delta)
    {
        return Transform(
            Mat44(1,0,0,delta.x(),
                  0,1,0,delta.y(),
                  0,0,1,delta.z(),
                  0,0,0,1),
            Mat44(1,0,0,-delta.x(),
                  0,1,0,-delta.y(),
                  0,0,1,-delta.z(),
                  0,0,0,1)
        );
    }

    static Transform rotate(const Vec3& axis, float angle)
    {
        Vec3 u = unit(axis);
        float x = u.x(), y = u.y(), z = u.z();
        float sin_ = sin(angle);
        float cos_ = cos(angle);
        float ncos = 1 - cos_;

        return Transform(
            Mat44(cos_ + x*x*ncos, x*y*ncos - z*sin_, x*z*ncos+y*sin_, 0,
                  y*x*ncos + z*sin_, cos_ + y*y*ncos, y*z*ncos-x*sin_, 0,
                  z*x*ncos-y*sin_, z*y*ncos + x*sin_, cos_ + z*z*ncos, 0,
                  0,0,0,1),
            Mat44(cos_ + x*x*ncos, x*y*ncos + z*sin_, x*z*ncos - y*sin_, 0,
                  y*x*ncos - z*sin_, cos_ + y*y*ncos, y*z*ncos + x*sin_, 0,
                  z*x*ncos + y*sin_, z*y*ncos - x*sin_, cos_ + z*z*ncos, 0,
                  0,0,0,1)
        );
    }

    static Transform scale(const Vec3& scale)
    {
        return Transform(
            Mat44(scale.x(),0,0,0,
                  0,scale.y(),0,0,
                  0,0,scale.z(),0,
                  0,0,0,1),
            Mat44(1/scale.x(),0,0,0,
                  0,1/scale.y(),0,0,
                  0,0,1/scale.z(),0,
                  0,0,0,1)
        );
    }
};


#endif // DEATHRAY_UTIL_TRANSFORM_H_
