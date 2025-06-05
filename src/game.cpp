#ifndef GAME_CPP
#define GAME_CPP

#include <iostream>
#include <cstdlib>


#include "game.hpp"

GLFWwindow* Game::window = nullptr;
float Game::deltaTime = 0;
Game::Game(){
    Init();
}

Game::~Game(){
    // Destroy element before GLFW cleanup

    glfwDestroyWindow(window); window = nullptr;
    
    // GLFW cleanup
    glfwTerminate();
}


void Game::Init(){
    // Setup GLFW
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #if DEV_MACOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif


    // Create window
    window = glfwCreateWindow(1920, 1080, "Minecraft Clone", NULL, NULL);
    if (!window){
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // Setup Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize glad" << std::endl;
        glfwDestroyWindow(window); window = nullptr;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void Game::Start(){
    while (!glfwWindowShouldClose(window)){
        Update();
    }
}


void Game::Update(){
    Render();
}

void Game::Render(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
        

    glfwSwapBuffers(window);
}

#endif
