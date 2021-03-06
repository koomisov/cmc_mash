#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include <memory>
#include <optional>

#include "scene.h"
#include "material.h"

class SceneLoader
{
    Material _ivory = Material(glm::dvec3(0.4, 0.4, 0.3),
        glm::dvec3(0.0), glm::dvec4(0.6, 0.3, 0.1, 0.0),
        50.0d, 1.0d, Material::DIFFUSE);
    Material _green = Material(glm::dvec3(0.21, 0.59, 0.29),
        glm::dvec3(0.0), glm::dvec4(0.6, 0.3, 0.1, 0.0),
        40.0d, 1.0d, Material::DIFFUSE);
    Material _blue = Material(glm::dvec3(0.0, 0.74, 0.99),
        glm::dvec3(30.0), glm::dvec4(0.6, 0.3, 0.1, 0.0),
        20.0d, 1.0d, Material::DIFFUSE);
    Material _white = Material(glm::dvec3(0.99, 0.99, 0.99),
        glm::dvec3(0.0), glm::dvec4(0.6, 0.3, 0.1, 0.0),
        50.0d, 1.0d, Material::DIFFUSE);
    Material _rubber = Material(glm::dvec3(0.3, 0.1, 0.1),
        glm::dvec3(20.0), glm::dvec4(0.9, 0.1, 0.0, 0.0),
        10.0d, 1.0d, Material::DIFFUSE);
    Material _mirror = Material(glm::dvec3(0.99, 0.99, 0.99),
        glm::dvec3(0.0), glm::dvec4(0.0, 10.0, 0.8, 0.0),
        1425.0d, 1.0d, Material::SPECULAR);
    Material _glass = Material(glm::dvec3(0.6, 0.7, 0.8),
        glm::dvec3(0.0), glm::dvec4(0.0, 0.5, 0.1, 0.8),
        125.0d, 1.5d, Material::REFRACTIVE);
    Material _clean = Material(glm::dvec3(0.99, 0.99, 0.99),
        glm::dvec3(0.0), glm::dvec4(0.0, 0.5, 0.1, 0.8),
        125.0d, 1.5d, Material::REFRACTIVE);

public:
    std::unique_ptr<Scene> load_scene(unsigned number)
    {
        switch(number)
        {
            case 1:
                return scene_1();

            case 2:
                return scene_2();

            case 3:
                return scene_3();

            default:
                return nullptr;
        }
    }

private:
    std::unique_ptr<Scene> scene_1();
    std::unique_ptr<Scene> scene_2();
    std::unique_ptr<Scene> scene_3();
};

#endif // SCENE_LOADER_H
