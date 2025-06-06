#ifndef CAMERA_HPP
#define CAMERA_HPP


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
    private:
    protected:
        int width;
        int height;
        float ratio;
            
        float yaw;
        float pitch;
        float fov;
        
        glm::vec3 position;
        
        glm::vec3 up;
        glm::vec3 front;
        
        glm::mat4 view;
        glm::mat4 perspective;
        glm::mat4 orthographic;


        void UpdateFaceDirection();
        void UpdateMatrices();
        void UpdateViewMatrice();
        void UpdatePerspectiveMatrice();
        void UpdateOrthographicMatrice();


    public:
        
        Camera(glm::vec3 position = glm::vec3(0.0f), int width = 1920, int height = 1080, 
               float yaw = 0.0f, float pitch = 0.0f, float fov = 90.0f);
    

        // Get Camera's Information
        int GetWidth();
        int GetHeight();
        float GetRatio();

        float GetYaw();        
        float GetPitch();        
        float GetFov();  
    
        glm::vec3 GetPosition();

        float* GetViewMatrice();
        float* GetPerspectiveMatrice();
        float* GetOrthographicMatrice();

        
        // Set Camera's Informations
        void SetResolution(int width, int height);

        void SetYaw(float yaw);
        void SetPitch(float pitch);
        void SetAngles(float yaw, float pitch);
        void SetFov(float fov);
        
        void SetPosition(glm::vec3 position);


};

#endif
