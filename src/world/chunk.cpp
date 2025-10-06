#ifndef CHUNK_CPP
#define CHUNK_CPP

#include "chunk.hpp"
#include "../utils/direction.hpp"
#include "../utils/utilities.hpp"

#include <stdexcept>
#include <iostream>

#define ATLAS_SIZE 128.0f
#define ATLAS_ELEMENT_SIZE 16.0f
#define ATLAS_RESOLUTION (ATLAS_ELEMENT_SIZE / ATLAS_SIZE - 0.00000001f)

#pragma region FaceData

static const glm::vec3 rightFace[] = {
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5, 0.5f, -0.5f),
    glm::vec3(0.5, 0.5f, 0.5f),
    glm::vec3(0.5f, -0.5f, 0.5f),
};

static const unsigned int rightIndices[] = {
    0, 1, 2, 0, 2, 3
};

static const glm::vec3 leftFace[] = {
    glm::vec3(-0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
};

static const unsigned int leftIndices[] = {
    0, 1, 2, 0, 2, 3
};

static const glm::vec3 upFace[] = {
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f)
};

static const unsigned int upIndices[] = {
    0, 1, 2, 0, 2, 3
};

static const glm::vec3 downFace[] = {
    glm::vec3(-0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, 0.5f),
};

static const unsigned int downIndices[] = {
    0, 1, 2, 0, 2, 3
};

static const glm::vec3 forwardFace[] = {
    glm::vec3(-0.5f, -0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    glm::vec3(0.5f, -0.5f, 0.5f)
};

static const unsigned int forwardIndices[] = {
    0, 2, 1, 0, 3, 2
};

static const glm::vec3 backwardFace[] = {
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f)
};

static const unsigned int backwardIndices[] = {
    0, 1, 2, 0, 2, 3
};

#pragma endregion

Chunk::Chunk() : blocks{nullptr} {
    SetPosition(glm::ivec3{0});

    blocks = new unsigned int[chunkSize.x * chunkSize.y * chunkSize.z]();
    for (int i = 0; i < DIRECTION_SIZE; ++i) {
        switch(i){
            case Direction::RIGHT:
                blockFaces[_direction[i]] = FaceData(rightFace, rightIndices);
                break;
            case Direction::LEFT:
                blockFaces[_direction[i]] = FaceData(leftFace, leftIndices);
                break;
            case Direction::UP:
                blockFaces[_direction[i]] = FaceData(upFace, upIndices);
                break;
            case Direction::DOWN:
                blockFaces[_direction[i]] = FaceData(downFace, downIndices);
                break;
            case Direction::FORWARD:
                blockFaces[_direction[i]] = FaceData(forwardFace, forwardIndices);
                break;
            case Direction::BACKWARD:
                blockFaces[_direction[i]] = FaceData(backwardFace, backwardIndices);
                break;
        }
    }
}

Chunk::Chunk(const Chunk& cp){
    position = cp.position;
    
    blocks = new unsigned int[chunkSize.x * chunkSize.y * chunkSize.z]();
    for (int i = 0; i < chunkSize.x * chunkSize.y * chunkSize.z; ++i){
        blocks[i] = cp.blocks[i];
    }
    blockFaces = cp.blockFaces;
}

Chunk::Chunk(Chunk&& cp){
    position = cp.position;
    blocks = cp.blocks;
    blockFaces = cp.blockFaces;

    cp.blocks = nullptr;
}

Chunk::~Chunk(){
    if (blocks) delete[] blocks;
}


Chunk& Chunk::operator=(const Chunk& cp){
    this->position = cp.position;
    if (!blocks) blocks = new unsigned int[chunkSize.x * chunkSize.y * chunkSize.z];
    for (int i = 0; i < chunkSize.x * chunkSize.y * chunkSize.z; ++i){
        this->blocks[i] = cp.blocks[i];
    }
    this->blockFaces = cp.blockFaces;
    return *this;
}


glm::ivec3 Chunk::GetPosition() const{
    return position;
}

void Chunk::SetPosition(glm::ivec3 position){
    this->position = position;
    solid.transform.position = position * chunkSize;
    transparent.transform.position = position * chunkSize;
}

void Chunk::GenerateChunkMesh(const BlockList& blocksData){
    Mesh& solidMesh = solid.mesh;
    Mesh& transMesh = transparent.mesh;

    solidMesh.Clear();
    transMesh.Clear();
    
    Mesh* current = &solidMesh;

    for (int x = 0; x < chunkSize.x; ++x){
        for (int y = 0; y < chunkSize.y; ++y){
            for (int z = 0; z < chunkSize.z; ++z){
                glm::ivec3 blockPos = {x, y, z};
                for (int i = 0; i < DIRECTION_SIZE; ++i){
                    glm::ivec3 blockToCheck = {blockPos + _direction[i]};
                    unsigned int iBlockPos = 
                        blockPos.x + blockPos.y * chunkSize.x * chunkSize.z + blockPos.z * chunkSize.x;
                    unsigned int iBlockToCheck = 
                        blockToCheck.x + blockToCheck.y * chunkSize.x * chunkSize.z + blockToCheck.z * chunkSize.x;
                    
                    int blockId = blocks[iBlockPos];
                    float atlasResolution = ATLAS_RESOLUTION;
                    BlockType blockType =  blocksData[blockId]->type;
                
                    if (blockType == BlockType::TRANSPARENT) current = &transMesh;
                    else current = &solidMesh;
                                        
                    if (
                        blockToCheck.x >= 0 && blockToCheck.x < chunkSize.x &&
                        blockToCheck.y >= 0 && blockToCheck.y < chunkSize.y && 
                        blockToCheck.z >= 0 && blockToCheck.z < chunkSize.z 
                        ) {
                        int blockCheckId = blocks[iBlockToCheck];
                        BlockType blockCheckType =  blocksData[blockCheckId]->type;
                        if (blockCheckId == 0 || (blockType == BlockType::SOLID && blockCheckType == BlockType::TRANSPARENT) || (blockType == BlockType::TRANSPARENT && blockCheckType == BlockType::SOLID)){
                            if (blockId != 0){
                                FaceData& faceToApply = blockFaces[_direction[i]];
                                glm::ivec2 texOffset = blocksData[blocks[iBlockPos]] ? 
                                    blocksData[blockId]->GetTexCoord() + blocksData[blockId]->GetTexOffsets(_direction[i]) : glm::ivec2{0};
                                glm::vec2 texCoord = (glm::vec2)texOffset * atlasResolution;
                                glm::vec2 offset[] {
                                    {0.0f, atlasResolution},
                                    {0.0f, 0.0f},
                                    {atlasResolution, 0.0f},
                                    {atlasResolution, atlasResolution},
                                };
                                for (int j = 0; j < 4; ++j){
                                    current->vertices.push_back(Vertex{glm::vec3(x, y, z) + faceToApply.vertices[j], glm::vec3(0.0f), texCoord + offset[j]});
                                }

                                for (int j = 0; j < 6; ++j){
                                    current->indices.push_back(current->vertices.size() - 4 + faceToApply.indices[j]);
                                }
                            }
                        }
                    }                    
                    else{
                        if (blockId != 0){
                            FaceData& faceToApply = blockFaces[_direction[i]];
                            glm::ivec2 texOffset = blocksData[blocks[iBlockPos]] ? 
                                blocksData[blockId]->GetTexCoord() + blocksData[blockId]->GetTexOffsets(_direction[i]) : glm::ivec2{0};
                            glm::vec2 texCoord = (glm::vec2)texOffset * atlasResolution;
                            glm::vec2 offset[] {
                                {0.0f, atlasResolution},
                                {0.0f, 0.0f},
                                {atlasResolution, 0.0f},
                                {atlasResolution, atlasResolution},
                            };
                            for (int j = 0; j < 4; ++j){
                                current->vertices.push_back(Vertex{glm::vec3(x, y, z) + faceToApply.vertices[j], glm::vec3(0.0f), texCoord + offset[j]});
                            }

                            for (int j = 0; j < 6; ++j){
                                current->indices.push_back(current->vertices.size() - 4 + faceToApply.indices[j]);
                            }
                        }
                    }
                }
            }
        }
    }
    
    solidMesh.RecalculateNormal();
    solidMesh.GenerateMesh();
    
    transMesh.RecalculateNormal();
    transMesh.GenerateMesh();
}

void Chunk::Render(ShaderList &shaders){
    solid.Render(shaders[ShaderName::BLOCK]);
    transparent.Render(shaders[ShaderName::BLOCK]);
}

#endif