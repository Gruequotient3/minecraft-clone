#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <glm/glm.hpp>

#include <string>

// Constant
const glm::ivec3 chunkSize{16, 128, 16};

namespace Utils{
    // Function
    float Lerp(float a ,float b, float t);
    float ClampedLerp(float a ,float b, float t);
    
    float InverseLerp(float a ,float b, float v);
    float ClampedInverseLerp(float a ,float b, float v);

    glm::ivec3 WorldToChunk(glm::vec3 worldPos);
    glm::vec3 ChunkToWorld(glm::ivec3 chunkPos);

    std::string to_string(glm::vec3 vect);
    std::string to_string(glm::vec2 vect);
    std::string to_string(glm::ivec3 vect);
    std::string to_string(glm::ivec2 vect);

};

#endif