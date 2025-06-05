#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Game{
    private:
    protected:
        void Init();
        void Update();
        void Render();

        void UpdateDeltaTime();

    public:
        static GLFWwindow* window;
        static float deltaTime;


        Game();
        ~Game();
        
        void Start();
};




#endif
