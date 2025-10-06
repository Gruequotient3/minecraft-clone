#ifndef GAME_CPP
#define GAME_CPP

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "game.hpp"

#include "utils/mesh.hpp"
#include "utils/object.hpp"
#include "utils/utilities.hpp"
#include "utils/noise.hpp"
#include "world/chunk.hpp"

GLFWwindow *Game::window = nullptr;
float Game::deltaTime = 0;
Camera Game::camera = Camera{};
bool Game::debug = false;
Game::Game(){
    Init();
}

Game::~Game(){
    // Destroy element before GLFW cleanup
    delete worldGenerator;
    chunks.clear();
    shaders.Destroy();

    // GLFW cleanup
    glfwDestroyWindow(window);
    window = nullptr;
    glfwTerminate();
}

void Game::Init(){
    // Setup GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
#if DEV_MACOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    window = glfwCreateWindow(1920, 1080, "Minecraft Clone", glfwGetPrimaryMonitor(), NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // Setup Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad" << std::endl;
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    SetParameters();
    SetCallbacks();
    
    // Setup DearImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.MouseDrawCursor = false;
    
    //  DearmImGui Style
    ImGui::StyleColorsDark();
    
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    
    shaders.Init();
}

void Game::Start()
{
    camera.SetResolution(1920, 1080);
    camera.SetPosition(glm::vec3(0.0f, 128.0f, -3.0f));
    
    blocksData.Generate();
    texture.Load("res/img/Texture-Atlas.png", GL_RGBA);

    shaders[ShaderName::BLOCK].Use();
    shaders[ShaderName::BLOCK].SetInt("atlas", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    worldGenerator = (WorldGenerator *)new DefaultGenerator;

    renderDistance = 10;

    while (!glfwWindowShouldClose(window))
    {
        Update();
    }
}

void Game::Update()
{
    UpdateDeltaTime();
    UpdateChunk();
    DebugInfo();
    Render();
    ProcessInput();
}

void Game::Render()
{
    // Main Screen
    glClearColor(0.51f, 0.62f, 0.78f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Render Chunk
    std::unordered_map<glm::ivec3, Chunk>::iterator it;
    for (it = chunks.begin(); it != chunks.end(); ++it)
    {
        it->second.Render(shaders);
    }

    // Show DearImGUi window
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Game::UpdateChunk()
{
    // Make new Chunk spawn
    for (int x = -renderDistance; x < renderDistance + 1; ++x)
    {
        for (int z = -renderDistance; z < renderDistance + 1; ++z)
        {
            glm::ivec3 pos = Utils::WorldToChunk(camera.GetPosition()) + glm::ivec3{x, 0, z};
            if (chunks.find(pos) != chunks.end())
                continue;
            chunks.insert({pos, Chunk{}});
            chunks[pos].SetPosition(pos);
            worldGenerator->GetMap(blocksData, pos, chunks[pos].blocks, chunkSize);
            chunks[pos].GenerateChunkMesh(blocksData);
        }
    }

    // Make Chunk too far despawn
    std::unordered_map<glm::ivec3, Chunk>::iterator it;
    std::vector<glm::ivec3> toRemove;
    for (it = chunks.begin(); it != chunks.end(); ++it)
    {
        glm::ivec3 pos = Utils::WorldToChunk(camera.GetPosition());
        glm::ivec3 chunkPos = it->first;
        if (abs(pos.x - chunkPos.x) > renderDistance + 1 || abs(pos.z - chunkPos.z) > renderDistance + 1)
        {
            toRemove.push_back(chunkPos);
        }
    }
    for (glm::ivec3 chunkPos : toRemove)
    {
        chunks.erase(chunkPos);
    }

    return;
}

void Game::DebugInfo()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("Debug Info");
    
    ImGui::Text("Chunk : ");
    ImGui::Text("%s", Utils::to_string(Utils::WorldToChunk(camera.GetPosition())).c_str());
    
    ImGui::Text("Coordonate : ");
    ImGui::Text("%s", Utils::to_string(camera.GetPosition()).c_str());
    
    ImGui::Text("Rotation : ");
    ImGui::NextColumn();
    ImGui::Text("%s", Utils::to_string(glm::vec2(camera.GetYaw(), camera.GetPitch())).c_str());

    ImGui::End();
}

void Game::ProcessInput()
{
    static bool debugPress = false;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
        return;
    }

    if (debugPress && glfwGetKey(window, GLFW_KEY_F3) != GLFW_PRESS){
        debug = !debug;
        if (debug){ 
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        // TODO rehidding cursor not working
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    debugPress = (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS);

    if (debug) return;
    float velocity = 40.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        glm::vec3 position = camera.GetPosition();
        position += camera.up * velocity;
        camera.SetPosition(position);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        glm::vec3 position = camera.GetPosition();
        position -= camera.up * velocity;
        camera.SetPosition(position);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm::vec3 position = camera.GetPosition();
        position += glm::normalize(glm::vec3{camera.front.x, 0.0f, camera.front.z}) * velocity;
        camera.SetPosition(position);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm::vec3 position = camera.GetPosition();
        position -= glm::normalize(glm::vec3{camera.front.x, 0.0f, camera.front.z}) * velocity;
        camera.SetPosition(position);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 position = camera.GetPosition();
        position -= glm::normalize(glm::cross(glm::normalize(glm::vec3{camera.front.x, 0.0f, camera.front.z}), camera.up)) * velocity;
        camera.SetPosition(position);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 position = camera.GetPosition();
        position += glm::normalize(glm::cross(glm::normalize(glm::vec3{camera.front.x, 0.0f, camera.front.z}), camera.up)) * velocity;
        camera.SetPosition(position);
    }
}

void Game::UpdateDeltaTime()
{
    static float lastFrame = 0.0f;
    float currentFrame = glfwGetTime();
    deltaTime = ceilf((currentFrame - lastFrame) * 1000) / 1000;
    lastFrame = currentFrame;
}

void Game::SetParameters()
{
    glfwSwapInterval(0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::SetCallbacks()
{
    glfwSetFramebufferSizeCallback(window, SetFrameBufferSizeCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
}

void Game::SetFrameBufferSizeCallback(GLFWwindow *, int width, int height)
{
    glViewport(0, 0, width, height);
    camera.SetResolution(width, height);
}

void Game::MouseCallback(GLFWwindow *, double xpos, double ypos)
{
    if (debug) return;

    static float lastX = xpos;
    static float lastY = ypos;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 4.0f;

    xoffset *= sensitivity * deltaTime;
    yoffset *= sensitivity * deltaTime;

    camera.SetAngles(camera.GetYaw() + xoffset, camera.GetPitch() + yoffset);
}

#endif
