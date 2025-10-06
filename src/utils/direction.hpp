#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <glm/glm.hpp>

#define DIRECTION_SIZE 6

enum Direction {RIGHT, LEFT, UP, DOWN, FORWARD, BACKWARD};

const glm::ivec3 _direction[] = {
    glm::ivec3{1, 0, 0},    // right
    glm::ivec3{-1, 0, 0},   // left
    glm::ivec3{0, 1, 0},    // up
    glm::ivec3{0, -1, 0},   // down
    glm::ivec3{0, 0, 1},    // forward
    glm::ivec3{0, 0, -1},   // backward
};


#endif