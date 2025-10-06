#include "worldgenerator.hpp"
#include "../utils/utilities.hpp"

#include <iostream>

DefaultGenerator::DefaultGenerator() : noise{NoiseSettings{1.0f, 4, 1.0f, 0.3f, 4.0f, 0.4f}}{ 
    minValue = 0;
    maxValue = 0;
    float amplitude = noise.amplitude;
    for (int i = 0; i < noise.octave; ++i){
        maxValue += amplitude;
        minValue += 0.5f * amplitude;
        amplitude *= noise.persistence; 
    }
    maxValue *= noise.strength;
}

void DefaultGenerator::GetMap(const BlockList& blockData, const glm::vec3& offset, unsigned int* map, const glm::ivec3& mapSize){

    for (int x = 0; x < mapSize.x; ++x){
        for (int z = 0; z < mapSize.z; ++z){
            
            // Generate height map value
            float noiseValue = 0.0f;
            float frequency = noise.frequency;
            float amplitude = noise.amplitude;
            for (int i = 0; i < noise.octave; ++i){
                glm::vec2 pf = glm::vec2{x + offset.x * mapSize.x, z + offset.z * mapSize.z} * frequency;
                float v = Noise::LerpNoise2D(pf);
                noiseValue += (v + 1) * 0.5f * amplitude;
                frequency *= noise.lacunarity;
                amplitude *= noise.persistence;
            }
            noiseValue *= noise.strength;
            float heightValue = Utils::InverseLerp(minValue, maxValue, noiseValue);
            int noisey = (int)Utils::Lerp(60, mapSize.y, heightValue);
            int heightStrength = 0, y = 68;
            if (noisey >= 68) y = noisey;
            for (;y >= 0; --y){
                int pos = x + y * mapSize.x * mapSize.z + z * mapSize.x;
                Block* block = nullptr;
                
                if (noisey < y){
                    block = (Block*)blockData["minecraft:water"];
                    map[pos] = block ? block->id : 0;
                    continue;
                }

                if (heightStrength == 0) {
                    if (y <= 70 && y > 62){
                        block = (Block*)blockData["minecraft:sand"];
                        map[pos] = block ? block->id : 0;
                    }

                    else if (y <= 62){
                        block = (Block*)blockData["minecraft:gravel"];
                        map[pos] = block ? block->id : 0;
                    }

                    else {
                        block = (Block*)blockData["minecraft:grass"];
                        map[pos] = block ? block->id : 0;
                    }
                }
                else if (heightStrength < 3) {
                    block = (Block*)blockData["minecraft:dirt"];
                    map[pos] = block ? block->id : 0;
                }
                else {
                    block = (Block*)blockData["minecraft:stone"];
                    map[pos] = block ? block->id : 0;
                }
                ++heightStrength;
            }
        }
    }
}