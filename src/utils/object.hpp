#ifndef OBJECT_HPP
#define OBJECT_HPP


#include "mesh.hpp"
#include "transform.hpp"

class Object{
    private:
    protected:
    public:
        Mesh mesh;
        Transform transform;

        bool active;

        Object();
        virtual ~Object();
        void Render(Shader& shader);
};


#endif