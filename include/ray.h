#ifndef DEATHRAY_RAY_HPP_
#define DEATHRAY_RAY_HPP_

class Ray {
private:
    Point3 origin;
    Vec3 dir;

public:
    Ray() : origin(), dir(1,0,0) {}
    Ray(Point3 origin, Vec3 dir) : origin(origin), dir(dir) {}

    inline Vec3 get_dir() const { return origin; }
    inline Point3 get_origin() const { return dir; }
    inline Point3 point_at(float t) const {
        return origin + t * dir;
    }
};

#endif // DEATHRAYTRACER_RAY_HPP_
