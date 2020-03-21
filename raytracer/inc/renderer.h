#ifndef RENDERER_H
#define RENDERER_H

#include <algorithm>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "image.h"
#include "scene.h"
#include "object.h"
#include "ray.h"

class Renderer
{
    glm::uvec2 _size;
    double _fov;
    unsigned _max_recursion;

public:
    Renderer(const glm::uvec2 size, double fov, unsigned max_recursion) :
        _size(size), _fov(fov), _max_recursion(max_recursion) {}

    Image render(const Scene &scene) const;

private:
    Image render_frag(const Scene &scene, const glm::uvec2 &start,
        const glm::uvec2 &size, bool path_tracing) const;
    glm::dvec3 render_pixel(const Scene &scene,
        const glm::uvec2 &position) const;
    glm::dvec3 render_ray(const Scene &scene, const Ray &ray,
        unsigned recursion = 0) const;
    glm::dvec3 render_path(const Scene &scene, const Ray &ray,
        unsigned recursion) const;

    glm::dvec3 reflect(const glm::dvec3 &indice, const glm::dvec3 &normal)
        const;
    glm::dvec3 refract(const glm::dvec3 &indice, const glm::dvec3 &normal,
        double refracive_index) const;
};

#endif // RENDERER_H
