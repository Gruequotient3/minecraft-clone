#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "imgui.h"

#include "game.hpp"

int main(){
    Game game;
    game.Start();

    return 0;
}
