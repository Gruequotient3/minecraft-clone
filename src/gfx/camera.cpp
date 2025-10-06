#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "camera.hpp"

#include <cmath>

Camera::Camera(glm::vec3 position, int width, int height,
            float yaw, float pitch, float fov){
    this->position = position;
    
    this->width = width;
    this->height = height;
    this->ratio = width / (float) height;
    
    this->yaw = yaw;
    this->pitch = pitch;
    this->fov = fov;

    up = glm::vec3(0.0f, 1.0f, 0.0f);
    UpdateFaceDirection(); 
}


void Camera::UpdateFaceDirection(){
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    front = glm::normalize(front);
    UpdateViewMatrice();
}

void Camera::UpdateMatrices(){
    UpdateViewMatrice();
    UpdatePerspectiveMatrice();
    UpdateOrthographicMatrice();
}

void Camera::UpdateViewMatrice(){
    view = glm::lookAt(position, position + front, up);
}

void Camera::UpdatePerspectiveMatrice(){
    perspective = glm::perspective(fov, ratio, 0.1f, 10000.0f);
}

void Camera::UpdateOrthographicMatrice(){
    orthographic = glm::ortho(-width / 2.0f, width/ 2.0f, 
                            -height / 2.0f, height / 2.0f,
                            -1000.0f, 1000.0f);
}

int Camera::GetWidth() { return width; }
int Camera::GetHeight() { return height; }
float Camera::GetRatio() { return ratio; }

float Camera::GetYaw() { return yaw; }       
float Camera::GetPitch() { return pitch; }
float Camera::GetFov() { return fov; }

glm::vec3 Camera::GetPosition() { return position; }

float* Camera::GetViewMatrice() { return glm::value_ptr(view); }
float* Camera::GetPerspectiveMatrice() { return glm::value_ptr(perspective); }
float* Camera::GetOrthographicMatrice() { return glm::value_ptr(orthographic); }

void Camera::SetResolution(int width, int height){
    this->width = width;
    this->height = height;
    this->ratio = width / (float) height;
    UpdateMatrices();
}

void Camera::SetYaw(float yaw){
    if (yaw < -180.0f) yaw = yaw + 360;
    else if (yaw > 180.0f) yaw = yaw - 360; 

    this->yaw = yaw;
    UpdateFaceDirection();
}

void Camera::SetPitch(float pitch){
    if (pitch < -90.0f) pitch = -89.9f;
    else if (pitch > 90.0f) pitch = 89.9f; 

    this->pitch = pitch;
    UpdateFaceDirection();
}

void Camera::SetAngles(float yaw, float pitch){
    SetYaw(yaw);
    SetPitch(pitch);

    UpdateFaceDirection();
}

void Camera::SetFov(float fov){
    if (fov < 1.0) fov = 1.0f;
    else if (fov > 90.0f) fov = 90.0f;

    this->fov = fov;
    UpdatePerspectiveMatrice();
}

void Camera::SetPosition(glm::vec3 position){
    this->position = position;
    UpdateViewMatrice();
}

#endif
