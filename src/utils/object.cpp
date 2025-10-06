#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "../game.hpp"
#include "object.hpp"

Object::Object() : active{true} { }
Object::~Object() { }

void Object::Render(Shader& shader){
    if (!active) return;
    // Apply transform to model matrice
    shader.Use();
    glm::mat4 model = glm::mat4{1.0f};
    model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); 
    model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); 
    model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, transform.position);
    model = glm::scale(model, transform.scale);

    shader.SetMat4("model", false, glm::value_ptr(model));
    shader.SetMat4("view", false, Game::camera.GetViewMatrice()); 
    shader.SetMat4("projection", false, Game::camera.GetPerspectiveMatrice());
    
    mesh.Draw(shader);
}

#endif