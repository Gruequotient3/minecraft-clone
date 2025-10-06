#ifndef WORLD_GENERATOR_HPP
#define WORLD_GENERATOR_HPP

#include "../utils/noise.hpp"
#include "block.hpp"

class WorldGenerator{
    private:
    protected:
    public:
        WorldGenerator() = default;
        virtual ~WorldGenerator() = default;
        virtual void GetMap(const BlockList& blockData, const glm::vec3& offset, unsigned int* chunkmap, const glm::ivec3& mapSize) = 0;
};

class DefaultGenerator : WorldGenerator{
    private:
    protected:
    public:
        NoiseSettings noise;
        float minValue;
        float maxValue;
        
        DefaultGenerator();
        ~DefaultGenerator() = default;
        void GetMap(const BlockList& blockData, const glm::vec3& offset, unsigned int* chunkmap, const glm::ivec3& mapSize);
};

#endif