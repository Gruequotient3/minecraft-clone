#ifndef FACE_HPP
#define FACE_HPP

#include <glm/glm.hpp>

class FaceData{
    private:
        void SetVertices(const glm::vec3* vertices);
        void SetIndices (const unsigned int* indices);
    protected:
    public:
        glm::vec3 vertices[4];
        unsigned int indices[6];
        
        FaceData();
        FaceData(const glm::vec3 vertices[4], const unsigned int indices[6]);
        FaceData(FaceData const& pc);

        FaceData& operator=(const FaceData& pc);
};

#endif