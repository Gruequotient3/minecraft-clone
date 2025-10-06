#ifndef FACE_CPP
#define FACE_CPP

#include "face.hpp"

FaceData::FaceData(){ };

FaceData::FaceData(const glm::vec3 vertices[4], const unsigned int indices[6]){
    SetVertices(vertices);
    SetIndices(indices);
    
}

FaceData::FaceData(FaceData const& pc){
    SetVertices(pc.vertices);
    SetIndices(pc.indices);
}

FaceData& FaceData::operator=(const FaceData& pc){
    this->SetVertices(pc.vertices);
    this->SetIndices(pc.indices);
    return *this;
}

void FaceData::SetVertices(const glm::vec3* vertices){
    for (int i = 0; i < 4; ++i){
        this->vertices[i] = vertices[i];
    }
}

void FaceData::SetIndices(const unsigned int* indices){
    for (int i = 0; i < 6; ++i){
        this->indices[i] = indices[i];
    }
}


#endif