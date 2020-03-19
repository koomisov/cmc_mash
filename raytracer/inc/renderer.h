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
    float _fov;
    unsigned _max_recursion;

public:
    Renderer(const glm::uvec2 size, float fov, unsigned max_recursion) :
        _size(size), _fov(fov), _max_recursion(max_recursion) {}

    Image render(const Scene &scene) const;

private:
    Image render_frag(const Scene &scene, const glm::uvec2 &start,
        const glm::uvec2 &size) const;
    glm::vec3 render_pixel(const Scene &scene,
        const glm::uvec2 &position) const;
    glm::vec3 render_ray(const Scene &scene, const Ray &ray,
        unsigned recursion = 0) const;

    static glm::vec3 reflect(const glm::vec3 &indice, const glm::vec3 &normal)
    {
        return indice - 2.0f * normal * glm::dot(indice, normal); 
    }
    
    static glm::vec3 refract(const glm::vec3 &indice, const glm::vec3 &normal,
            float refracive_index)
    {
        float cos_i = -std::max(-1.0f, 
            std::min(1.0f, glm::dot(indice, normal)));
        float eta_i = 1;
        float eta_t = refracive_index;

        glm::vec3 n = normal;

        if (cos_i < 0)
        {
            cos_i = -cos_i;
            std::swap(eta_i, eta_t);
            n = -n;
        }

        float eta = eta_i / eta_t;
        float k = 1 - eta * eta * (1 - cos_i * cos_i);

        return (k < 0) ? glm::vec3(0) :
            indice * eta + n * (eta * cos_i - std::sqrt(k));
    }
};

#endif // RENDERER_H
