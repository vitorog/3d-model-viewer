#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <glm/glm.hpp>

#include "utils.h"
#include "material.h"

class Model
{
public:
    Model();
    int Load(const std::string &path);
private:
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec2> text_coords_;
    std::vector<int> vertices_index_;
    std::vector<int> normals_index_;
    std::vector<int> text_coords_index_;
    std::map<std::string, int> materials_id_;
};

#endif // MODEL_H
