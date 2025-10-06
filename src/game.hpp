#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gfx/camera.hpp"
#include "gfx/texture.hpp"
#include "world/block.hpp"
#include "world/chunk.hpp"
#include "world/worldgenerator.hpp"

class Game{
    private:
        ShaderList shaders;
        Texture texture;
        BlockList blocksData;
        WorldGenerator* worldGenerator;

        std::unordered_map<glm::ivec3, Chunk> chunks;
        
        int renderDistance;
        
        void SetParameters();
        void SetCallbacks();
        
        // Callback functions
        static void SetFrameBufferSizeCallback(GLFWwindow*, int width, int height);
        static void MouseCallback(GLFWwindow*, double xpos, double ypos);
        
        protected:
        void Init();
        void Update();
        void Render();
        
        void DebugInfo();
        void ProcessInput();
        void UpdateDeltaTime();
        
        void UpdateChunk();
        
        public:
        static GLFWwindow* window;
        static float deltaTime;
        static Camera camera;
        static bool debug;
        
        Game();
        ~Game();
        
        void Start();
};




#endif
