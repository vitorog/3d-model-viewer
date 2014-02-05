#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm/glm.hpp"

#include "utils.h"


class Material
{
public:
    Material();
    int Load(const std::string &path);
private:
    std::string name_;
    glm::vec3 ka_;
    glm::vec3 kd_;
    glm::vec3 ks_;
    float tr_;
    std::string map_kd_;
};

#endif // MATERIAL_H
