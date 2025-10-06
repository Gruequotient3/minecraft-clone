#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"


#include "../utils/direction.hpp"

enum BlockType {
    SOLID, 
    TRANSPARENT,                
};

class Block{
    private:
    protected:
        glm::ivec2 texCoords;
        std::unordered_map<glm::ivec3, glm::ivec2> texFacesOffsets;

    public:
        unsigned int id;
        std::string name;
        BlockType type;
        std::vector<std::string> tags;

        Block();
        Block(unsigned int id, std::string name, BlockType type, const std::vector<std::string>& tags);
        virtual ~Block() = default;

        glm::ivec2 GetTexCoord() const;
        glm::ivec2 GetTexOffsets(const glm::ivec3& direction) const;
};

#pragma region BlockClasses

class Air : public Block{ public: Air(); };
class Grass : public Block{ public: Grass(); };
class Dirt : public Block{ public: Dirt(); };
class Stone : public Block{ public: Stone(); };
class Sand : public Block{ public: Sand(); };
class Gravel : public Block{ public: Gravel(); };
class Water : public Block{ public: Water(); };

#pragma endregion

class BlockList{
    private:
    protected:
    public:
        std::vector<Block*> blocks;

        virtual ~BlockList();

        const Block* operator[](int pos) const;
        const Block* operator[](const std::string& name) const;
        
        virtual void Generate();
};



#endif