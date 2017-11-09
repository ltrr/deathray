#ifndef DEATHRAY_DESCRIPTION_SURFACE_H_
#define DEATHRAY_DESCRIPTION_SURFACE_H_

#include <array>
#include "description/transformable.h"
#include "material/material.h"
#include "util/vector.h"

enum class SurfaceKind { UNK, TRIANGLE, SPHERE, MESH, PLANE };


class SurfaceDescription : public TransformableDescription
{
public:
    MaterialPtr material;

    void visit(SceneDescriptionVisitor *);

    virtual SurfaceKind getKind() const { return SurfaceKind::UNK; }
};


typedef std::shared_ptr<SurfaceDescription> SurfaceDescriptionPtr;


class TriangleDescription : public SurfaceDescription
{
public:
    Point3 p0, p1, p2;

    SurfaceKind getKind() const { return SurfaceKind::TRIANGLE; }
};


class SphereDescription : public SurfaceDescription
{
public:
    Point3 center;
    float radius;

    SurfaceKind getKind() const { return SurfaceKind::SPHERE; }
};


class MeshDescription : public SurfaceDescription
{
public:
    std::vector<Point3> vertices;
    std::vector<std::array<int, 3>> faces;

    SurfaceKind getKind() const { return SurfaceKind::MESH; }
};


class PlaneDescription : public SurfaceDescription
{
public:
    Point3 point;
    Vec3 normal;

    SurfaceKind getKind() const { return SurfaceKind::PLANE; }
};


#endif // DEATHRAY_DESCRIPTION_SURFACE_H_
