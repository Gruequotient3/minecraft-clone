#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

enum class ShaderName{
    NONE = 0, 
    BLOCK,
};

class Shader{
    private:
        void CheckCompileErrors(unsigned int shader, std::string type);
    public:
        unsigned int id;

        Shader();
        Shader(const char *vertexPath, const char *fragmentPath);

        void Destroy();

        void Load(const char *vertexPath, const char *fragmentPath);
        void Use() const;

        void SetBool(const std::string &name, bool value) const;
        void SetFloat(const std::string &name, float value) const;
        void SetFloatp(const std::string &name, int count, float* value) const;
        void SetInt(const std::string &name, int value) const;
        void SetIvec2(const std::string &name, glm::ivec2 value) const;
        void SetVec3(const std::string &name, glm::vec3 value) const;
        void SetVec3p(const std::string &name, int count, const float* value) const;
        void SetMat4(const std::string &name, GLboolean transpose, const GLfloat *value) const;
};

class ShaderList{
    private:
        std::vector<Shader> shaders;
    protected:
    public:
        ShaderList();
        
        Shader& operator[](long unsigned int pos);
        Shader& operator[](ShaderName pos);

        void Init();
        void Destroy();
};

#endif
