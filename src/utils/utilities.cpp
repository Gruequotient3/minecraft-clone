
#include "utilities.hpp"

float Utils::Lerp(float a, float b, float t){
    return a + t * (b - a);
}

float Utils::ClampedLerp(float a, float b, float t){
    float v = a + t * (b - a);
    return v >= 1.0f ? 1.0f : v <= 0.0f ? 0.0f : v; 
}

float Utils::InverseLerp(float a, float b, float v){
    return (v - a) / (b - a);
}

float Utils::ClampedInverseLerp(float a, float b, float v){
    float t =  (v - a) / (b - a);
    return t >= b ? b : t <= a ? a : t; 
}

glm::ivec3 Utils::WorldToChunk(glm::vec3 worldPos){
    glm::ivec3 chunkPos = worldPos / (glm::vec3)chunkSize; 
    return {chunkPos.x - (worldPos.x < 0.0f ? 1 : 0), 0, chunkPos.z - (worldPos.z < 0.0f ? 1 : 0)};
}

glm::vec3 Utils::ChunkToWorld(glm::ivec3 chunkPos){
    return chunkPos * chunkSize;
}


std::string Utils::to_string(glm::vec3 vect){
    return std::to_string(vect.x) + " " + std::to_string(vect.y) + " "  + std::to_string(vect.z);
}

std::string Utils::to_string(glm::vec2 vect){
    return std::to_string(vect.x) + " " + std::to_string(vect.y);

}

std::string Utils::to_string(glm::ivec3 vect){
    return std::to_string(vect.x) + " " + std::to_string(vect.y) + " "  + std::to_string(vect.z);

}
std::string Utils::to_string(glm::ivec2 vect) {
    return std::to_string(vect.x) + " " + std::to_string(vect.y);
}