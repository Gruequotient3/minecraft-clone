#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "../gfx/shader.hpp"


struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class Mesh{
    private:
    protected:
        unsigned int vao, vbo, ebo;
        
        void DestroyBuffers();
    
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        
        Mesh();
        ~Mesh();

        void GenerateMesh();
        void RecalculateNormal();
        void Draw(Shader &shader);

        void Clear();

        static Mesh GetQuadMesh();

}; 

#endif
