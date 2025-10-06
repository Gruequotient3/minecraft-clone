#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "../utils/object.hpp"
#include "face.hpp"
#include "block.hpp"

#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

class Chunk{
    private:
        std::unordered_map<glm::ivec3, FaceData> blockFaces;
        glm::ivec3 position;
    protected:
    public:
        Object solid; 
        Object transparent; 
        unsigned int* blocks;

        Chunk();
        Chunk(const Chunk& cp);
        Chunk(Chunk&& cp);
        ~Chunk();

        Chunk& operator=(const Chunk& cp);

        glm::ivec3 GetPosition() const;
        void SetPosition(glm::ivec3 position);

        void GenerateChunkMesh(const BlockList& blocksData);
        void Render(ShaderList& shaders);
};

#endif