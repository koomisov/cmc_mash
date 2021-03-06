#ifndef OBJECT_H
#define OBJECT_H

#include <optional>
#include <memory>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ray.h"
#include "material.h"
#include "bvh.h"

class Intersection
{
    glm::dvec3 _point;
    glm::dvec3 _normal;
    double _distance;
    
    const Material *_material;

public:
    Intersection(const glm::dvec3 &point, const glm::dvec3 &normal,
            double distance, const Material *material) :
        _point(point), _normal(normal), _distance(distance),
        _material(material) {}

    const glm::dvec3 &point() const { return _point; }
    const glm::dvec3 &normal() const { return _normal; }
    double distance() const { return _distance; }
    const Material *material() const { return _material; }
};

class Object
{
    const Material *_material;

public:
    Object(const Material *material) :
        _material(material) {}

    virtual std::optional<Intersection> find_intersection(const Ray &r)
        const = 0;
    const Material *material() const { return _material; }
};

class Sphere : public Object
{
    glm::dvec3 _center;
    double _radius;

public:
    Sphere(const glm::dvec3 &center, double radius,
            const Material *material) :
        Object(material), _center(center), _radius(radius) {}

    std::optional<Intersection> find_intersection(const Ray &r) const;
};

class Plane : public Object
{
    glm::dvec3 _normal;
    glm::dvec3 _point;

public:
    Plane(const glm::dvec3 &normal, const glm::dvec3 &point,
            const Material *material) :
        Object(material), _normal(normal), _point(point) {}

    std::optional<Intersection> find_intersection(const Ray &r) const;
};

struct Vertex
{
    glm::dvec3 position;
    glm::dvec3 normal;
};

struct Triangle
{
    unsigned a;
    unsigned b;
    unsigned c;
};

class Mesh : public Object
{
    std::vector<Vertex> _vertices;
    std::vector<Triangle> _triangles;
    BVH<Triangle> _bvh;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<Triangle> triangles,
            const Material *material) :
        Object(material), _vertices(std::move(vertices)),
        _triangles(triangles) { regen_bvh(100); }

    std::optional<Intersection> find_intersection(const Ray &r) const;
    std::optional<Intersection> find_intersection(const Ray &r,
        const Triangle &t) const;

private:
    BoundingBox calculate_box(const Triangle &t) const;
    void regen_bvh(size_t delta);
};

class Cylinder : public Object
{
    glm::dvec3 _bottom_center;
    glm::dvec3 _axis;
    double _radius;
    double _height;

public:
    Cylinder(const glm::dvec3 &bottom_center, const glm::dvec3 &axis,
            double radius, double height, const Material *material) :
        Object(material), _bottom_center(bottom_center), _axis(axis),
        _radius(radius), _height(height) {}

    std::optional<Intersection> find_intersection(const Ray &r) const;
};

#endif // OBJECT_H
