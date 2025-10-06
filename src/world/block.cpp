#ifndef BLOCK_CPP
#define BLOCK_CPP

#include "block.hpp"

Block::Block(){
    id = 0;
    name = "minecraft:air";
    type = BlockType::SOLID;
    tags = {};
    texCoords = glm::ivec2{0, 0};
}

Block::Block(unsigned int id, std::string name, BlockType type, const std::vector<std::string>& tags) 
    : id{id}, name{name}, type{type}, tags{tags} { 
        texCoords = glm::ivec2{0, 0};    
}

glm::ivec2 Block::GetTexCoord() const { return texCoords; }
glm::ivec2 Block::GetTexOffsets(const glm::ivec3& direction) const{
    if (texFacesOffsets.find(direction) != texFacesOffsets.end()) return texFacesOffsets.at(direction);
    return glm::ivec2{0, 0};
}


#pragma region BlockClasses

Air::Air() : Block() { }
Grass::Grass() : Block(1, "minecraft:grass", BlockType::SOLID, {}) {
    texCoords = glm::ivec2(1, 0);
    texFacesOffsets[_direction[Direction::UP]] = glm::ivec2(-1, 0);
    texFacesOffsets[_direction[Direction::DOWN]] = glm::ivec2(1, 0);
}

Dirt::Dirt() : Block(2, "minecraft:dirt", BlockType::SOLID, {}) { 
    texCoords = glm::ivec2{2, 0};
}

Stone::Stone() : Block(3, "minecraft:stone", BlockType::SOLID, {}) { 
    texCoords = glm::ivec2{3, 0};
}

Sand::Sand() : Block(4, "minecraft:sand", BlockType::SOLID, {}) { 
    texCoords = glm::ivec2{4, 0};
}

Gravel::Gravel() : Block(5, "minecraft:gravel", BlockType::SOLID, {}) { 
    texCoords = glm::ivec2{5, 0};
}

Water::Water() : Block(6, "minecraft:water", BlockType::TRANSPARENT, {}) { 
    texCoords = glm::ivec2{6, 0};
}



#pragma endregion


BlockList::~BlockList(){
    for (Block* block : blocks){
        delete block;
    }
}

const Block* BlockList::operator[](int pos) const{
    return (long unsigned int)pos < blocks.size() && pos >= 0 ? blocks[pos] : nullptr; 
}

const Block* BlockList::operator[](const std::string& name) const{
    for (long unsigned int pos = 0; pos < blocks.size(); ++pos){
        if (blocks[pos]->name == name) return blocks[pos];
    }
    return nullptr;
}

void BlockList::Generate(){
    blocks.push_back(new Air);
    blocks.push_back(new Grass);
    blocks.push_back(new Dirt);
    blocks.push_back(new Stone);
    blocks.push_back(new Sand);
    blocks.push_back(new Gravel);
    blocks.push_back(new Water);
}

#endif