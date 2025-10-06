#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

#include <vector>

class Texture{
    public:
        unsigned int id;
        GLenum type;
        int width;
        int height;
    
        Texture();
        Texture(const char *imagePath, GLenum format);
        
        void Destroy();
        void Load(const char *imagePath, GLenum format);
};

#endif
