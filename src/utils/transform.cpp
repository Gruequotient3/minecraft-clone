#ifndef TRANSFORM_CPP
#define TRANSFORM_CPP

#include "transform.hpp"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale){
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}


#endif