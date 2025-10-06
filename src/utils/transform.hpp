#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>


class Transform{
    private:
    protected:
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Transform(glm::vec3 position = glm::vec3{0.0f},
                    glm::vec3 rotation = glm::vec3{0.0f},
                    glm::vec3 scale = glm::vec3{1.0f});
};


#endif